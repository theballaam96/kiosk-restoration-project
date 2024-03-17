import os
import shutil
import gzip
import zlib
import subprocess
import hashlib
import requests
import zipfile
from geometry_mapper import geo_us_to_kiosk
from alter_kiosk_code import code_modifications
from restore_music import pullSongsFromROM

# DONKEY KONG 64 BUILDER
# AKA "CRANKY'S LAB"
# Built by Isotarge
# https://twitter.com/isotarge

# Measure how long this takes
import time
start_time = time.time()

COMPILE_C = True
CLEANUP = True

if COMPILE_C:
	print("Cranky's Lab Build System")
	print()

	if not os.path.exists("build/n64chain"):
		print("Downloading N64Chain from GitHub. This may take a while...")
		url = "https://github.com/tj90241/n64chain/releases/download/9.1.0/n64chain-windows.zip"
		r = requests.get(url, allow_redirects=True)
		open("n64chain.zip", "wb").write(r.content)
		with zipfile.ZipFile("n64chain.zip", "r") as zip_ref:
			zip_ref.extractall("build/n64chain/")
	cwd = os.path.dirname(os.path.abspath(__file__))

	print("[1 / 9] - Compiling C Code")
	if os.path.exists("obj"):
		shutil.rmtree('obj')
	os.mkdir("obj")
	exclusions = ["stack_trace.c"]
	with open('./asm/objects.asm', 'w') as obj_asm:
		for root, dirs, files in os.walk(r'src'):
			for file in files:
				if file.endswith('.c'):
					excluded = len([x for x in exclusions if x in file]) > 0
					if excluded:
						continue
					_o = os.path.join(root, file).replace("/", "_").replace("\\", "_").replace(".c", ".o")
					print(os.path.join(root, file))
					obj_asm.write(".importobj \"obj/" + _o + "\"\n")
					subprocess.run([f"{cwd}\\n64chain\\tools\\bin\\mips64-elf-gcc", "-w", "-Wall", "-O1", "-mtune=vr4300", "-march=vr4300", "-mabi=32", "-fomit-frame-pointer", "-fno-toplevel-reorder", "-G0", "-c", "-nostdinc", "-I.", "-Iinclude2", "-Iinclude2/libc", "-DTARGET_N64", "-DF3DEX2_GBI", os.path.join(root, file)])
					shutil.move("./" + file.replace(".c", ".o"), "obj/" + _o)
	print()

# Infrastructure for recomputing DK64 global pointer tables
from recompute_pointer_table import pointer_tables, dumpPointerTableDetails, replaceROMFile, writeModifiedPointerTablesToROM, parsePointerTables, getFileInfo, make_safe_filename
from recompute_overlays import isROMAddressOverlay, readOverlayOriginalData, replaceOverlayData, writeModifiedOverlaysToROM

# Patcher functions for the extracted files
from staticcode import patchStaticCode

ROMName = "./rom/dk64_kiosk.z64"
newROMName = "./rom/dk64-kioskrestoration-dev.z64"

if os.path.exists(newROMName):
	os.remove(newROMName)
shutil.copyfile(ROMName, newROMName)
if not os.path.exists("./bin/"):
	os.mkdir("./bin/")

file_dict = [
	# {
	# 	"name": "Static ASM Code",
	# 	"start": 0x113F0,
	# 	"compressed_size": 0xB15E4,
	# 	"source_file": "bin/StaticCode.bin",
	# 	"use_external_gzip": True,
	# 	"patcher": patchStaticCode,
	# }
]

print("[1 / 9] - Extracting map files")

us_tables = [1, 2, 3] # [1, 2, 3]
in_kiosk = [6, 8, 0x28, 0x4C, 0x50, 0x51, 0x53]
other_exclusions = []
excluded_maps = in_kiosk + other_exclusions
with open("./rom/dk64_us.z64", "rb") as fq:
	us_pointer = 0x101C50
	limit = 0xC8 # Should be 221, testing early limits for now
	floors_compressed = [False] * limit
	walls_compressed = [False] * limit
	valid_maps = [x for x in list(range(limit)) if x not in excluded_maps]
	# Initial pass of geofor compression data
	fq.seek(us_pointer + (1 << 2))
	table_start = us_pointer + int.from_bytes(fq.read(4), "big")
	for map_id in valid_maps:
		fq.seek(table_start + (map_id << 2))
		file_start = us_pointer + (int.from_bytes(fq.read(4), "big") & 0x7FFFFFFF)
		file_end = us_pointer + (int.from_bytes(fq.read(4), "big") & 0x7FFFFFFF)
		file_compressed_size = file_end - file_start
		fq.seek(file_start)
		file_data = fq.read(file_compressed_size)
		fq.seek(file_start)
		indic = int.from_bytes(fq.read(2), "big")
		if file_compressed_size > 8:
			if indic == 0x1F8B:
				file_data = zlib.decompress(file_data, (15 + 32))
			compression_byte = file_data[9]
			if (compression_byte & 1) != 0:
				walls_compressed[map_id] = True
			if (compression_byte & 2) != 0:
				floors_compressed[map_id] = True
	# Parse Tables
	for table in us_tables:
		fq.seek(us_pointer + (table << 2))
		table_start = us_pointer + int.from_bytes(fq.read(4), "big")
		for map_id in valid_maps:
			fq.seek(table_start + (map_id << 2))
			file_start = us_pointer + (int.from_bytes(fq.read(4), "big") & 0x7FFFFFFF)
			file_end = us_pointer + (int.from_bytes(fq.read(4), "big") & 0x7FFFFFFF)
			file_compressed_size = file_end - file_start
			fq.seek(file_start)
			file_data = fq.read(file_compressed_size)
			fq.seek(file_start)
			indic = int.from_bytes(fq.read(2), "big")
			is_gzip = indic == 0x1F8B
			if (file_compressed_size == 8 and not is_gzip) or map_id in (0xB, 50):
				if map_id == 50:
					indic = 0xAD
				elif map_id == 0xB:
					indic = 0x26
				elif indic >= limit:
					indic = 0
				added_name = f"./bin/t{table}_f{indic}.bin"
				append_data = {
					"name": f"Table {table - 1} File {indic}",
					"pointer_table_index": table - 1,
					"file_index": indic,
					"source_file": added_name,
					"do_not_extract": True,
				}
				if table == 2 and not walls_compressed[indic]:
					append_data["do_not_compress"] = True
				if table == 3 and not floors_compressed[indic]:
					append_data["do_not_compress"] = True
				if map_id < 0xA5:
					file_dict.append(append_data)
				continue
			if is_gzip:
				file_data = zlib.decompress(file_data, (15 + 32))
			file_name = f"./bin/t{table}_f{map_id}.bin"
			with open(file_name, "wb") as fk:
				fk.write(file_data)
			if table == 1:
				geo_us_to_kiosk(file_name)
			append_data = {
				"name": f"Table {table - 1} File {map_id}",
				"pointer_table_index": table - 1,
				"file_index": map_id,
				"source_file": file_name,
				"do_not_extract": True,
			}
			if table == 2 and not walls_compressed[map_id]:
				append_data["do_not_compress"] = True
			if table == 3 and not floors_compressed[map_id]:
				append_data["do_not_compress"] = True
			if map_id < 0xA5:
				file_dict.append(append_data)


with open(ROMName, "rb") as fh:
	print("[3 / 9] - Parsing pointer tables")
	parsePointerTables(fh)
	readOverlayOriginalData(fh)

	print("[4 / 9] - Extracting files from ROM")
	for x in file_dict:
		# N64Tex conversions do not need to be extracted to disk from ROM
		if "texture_format" in x:
			x["do_not_extract"] = True
			x["output_file"] = x["source_file"].replace(".png", "." + x["texture_format"])

		if not "output_file" in x:
			x["output_file"] = x["source_file"]

		# gzip.exe appends .gz to the filename, we'll do the same
		if "use_external_gzip" in x and x["use_external_gzip"]:
			x["output_file"] = x["output_file"] + ".gz"

		# If we're not extracting the file to disk, we're using a custom .bin that shoudn't be deleted
		if "do_not_extract" in x and x["do_not_extract"]:
			x["do_not_delete_source"] = True

		# Extract the compressed file from ROM
		if not ("do_not_extract" in x and x["do_not_extract"]):
			byte_read = bytes()
			if "pointer_table_index" in x and "file_index" in x:
				file_info = getFileInfo(x["pointer_table_index"], x["file_index"])
				if file_info:
					x["start"] = file_info["new_absolute_address"]
					x["compressed_size"] = len(file_info["data"])

			fh.seek(x["start"])
			byte_read = fh.read(x["compressed_size"])

			if not ("do_not_delete_source" in x and x["do_not_delete_source"]):
				if os.path.exists(x["source_file"]):
					os.remove(x["source_file"])

				with open(x["source_file"], "wb") as fg:
					dec = zlib.decompress(byte_read, 15 + 32)
					fg.write(dec)

print("[5 / 9] - Patching Extracted Files")
for x in file_dict:
	if "patcher" in x and callable(x["patcher"]):
		print(" - Running patcher for " + x["source_file"])
		x["patcher"](x["source_file"])

with open(newROMName, "r+b") as fh:
	print("[6 / 9] - Writing patched files to ROM")
	for x in file_dict:
		if "texture_format" in x:
			if x["texture_format"] in ["rgba5551", "i4", "ia4", "i8", "ia8"]:
				subprocess.run(["./build/n64tex.exe", x["texture_format"], x["source_file"]])
			else:
				print(" - ERROR: Unsupported texture format " + x["texture_format"])

		if "use_external_gzip" in x and x["use_external_gzip"]:
			if os.path.exists(x["source_file"]):
				subprocess.run(["./build/gzip.exe", "-f", "-n", "-k", "-q", "-9", x["output_file"].replace(".gz", "")])
				if os.path.exists(x["output_file"]):
					with open(x["output_file"], "r+b") as outputFile:
						# Chop off gzip footer
						outputFile.truncate(len(outputFile.read()) - 8)

		if os.path.exists(x["output_file"]):
			byte_read = bytes()
			uncompressed_size = 0
			with open(x["output_file"], "rb") as fg:
				byte_read = fg.read()
				uncompressed_size = len(byte_read)

			if "do_not_compress" in x and x["do_not_compress"]:
				compress = bytearray(byte_read)
			elif "use_external_gzip" in x and x["use_external_gzip"]:
				compress = bytearray(byte_read)
			elif "use_zlib" in x and x["use_zlib"]:
				compressor = zlib.compressobj(zlib.Z_BEST_COMPRESSION, zlib.DEFLATED, 25)
				compress = compressor.compress(byte_read)
				compress += compressor.flush()
				compress = bytearray(compress)
				# Zero out timestamp in gzip header to make builds deterministic
				compress[4] = 0
				compress[5] = 0
				compress[6] = 0
				compress[7] = 0
				# They used "Unix" as their Operating System ID, let's do the same
				compress[9] = 3
			else:
				compress = bytearray(gzip.compress(byte_read, compresslevel=9))
				# Zero out timestamp in gzip header to make builds deterministic
				compress[4] = 0
				compress[5] = 0
				compress[6] = 0
				compress[7] = 0
				# They used "Unix" as their Operating System ID, let's do the same
				compress[9] = 3

			print(" - Writing " + x["output_file"] + " (" + hex(len(compress)) + ") to ROM")
			if "pointer_table_index" in x and "file_index" in x:
				# More complicated write, update the pointer tables to point to the new data
				replaceROMFile(x["pointer_table_index"], x["file_index"], compress, uncompressed_size, x["output_file"])
			elif "start" in x:
				if isROMAddressOverlay(x["start"]):
					replaceOverlayData(x["start"], compress)
				else:
					# Simply write the bytes at the absolute address in ROM specified by x["start"]
					fh.seek(x["start"])
					fh.write(compress)
			else:
				print("  - WARNING: Can't find address information in file_dict entry to write " + x["output_file"] + " (" + hex(len(compress)) + ") to ROM")
		else:
			print(x["output_file"] + " does not exist")

		# Cleanup temporary files
		if not ("do_not_delete" in x and x["do_not_delete"]):
			if not ("do_not_delete_output" in x and x["do_not_delete_output"]):
				if os.path.exists(x["output_file"]) and x["output_file"] != x["source_file"]:
					os.remove(x["output_file"])
			if not ("do_not_delete_source" in x and x["do_not_delete_source"]):
				if os.path.exists(x["source_file"]):
					os.remove(x["source_file"])

	print("[7 / 9] - Writing recomputed pointer tables to ROM")
	writeModifiedPointerTablesToROM(fh)
	#writeModifiedOverlaysToROM(fh)

	print("[8 / 9] - Dumping details of all pointer tables to rom/pointer_tables_modified.log")
	dumpPointerTableDetails("rom/pointer_tables_modified.log", fh)

code_modifications() # Modify the code in ways we deem necessary
print(hex(pullSongsFromROM()))
# For compatibility with real hardware, the ROM size needs to be aligned to 0x10 bytes
with open(newROMName, "r+b") as fh:
    to_add = len(fh.read()) % 0x10
    if to_add > 0:
        to_add = 0x10 - to_add
        for x in range(to_add):
            fh.write(bytes([0]))

print("[9 / 9] - Generating BizHawk RAM watch")
import generate_watch_file

# Write custom ASM code to ROM
if COMPILE_C:
	subprocess.run(["build/armips.exe", "asm\main.asm", "-sym", "rom\dk64-kioskrestoration-dev.sym"])

# Fix CRC
from n64crc import fixCRC
fixCRC(newROMName)

# Remove temporary .o files
# shutil.rmtree('obj')

if CLEANUP:
	shutil.rmtree("./bin")

end_time = time.time()
with open(newROMName, "rb") as fh:
	print()
	print("Built " + newROMName + " in " + str(round(end_time - start_time, 3)) + " seconds")
	print("SHA1: " + hashlib.sha1(fh.read()).hexdigest().upper())