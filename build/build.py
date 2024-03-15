import os
import shutil
import gzip
import zlib
import subprocess
import hashlib
import requests
import zipfile
from geometry_mapper import geo_us_to_kiosk

# DONKEY KONG 64 BUILDER
# AKA "CRANKY'S LAB"
# Built by Isotarge
# https://twitter.com/isotarge

# Measure how long this takes
import time
start_time = time.time()

COMPILE_C = False

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
	with open('./asm/objects.asm', 'w') as obj_asm:
		for root, dirs, files in os.walk(r'src'):
			for file in files:
				if file.endswith('.c'):
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

map_replacements = [
	# {
	# 	"name": "Fairy Island Exit Test",
	# 	"map_index": 189,
	# 	"map_folder": "maps/exit_test/"
	# },
	# {
	# 	"name": "Japes Exit Test",
	# 	"map_index": 7,
	# 	"map_folder": "maps/exit_test/"
	# },
]

# Test all map replacements at once
# from map_names import maps
# for mapIndex, mapName in enumerate(maps):
# 	mapPath = "maps/" + str(mapIndex) + " - " + make_safe_filename(mapName) + "/"
# 	map_replacements.append({
# 		"name": mapName,
# 		"map_index": mapIndex,
# 		"map_folder": mapPath,
# 	})

##############################################################################
#Generate map files created using Fast64 - https://github.com/Fast-64/fast64 #
##############################################################################
from map_generator import generateMap
generate_maps = False #Set to True to generate map files (advanced)

map_replacement_models = [
	# {
		# "map_name": "spiral mountain",
		# "map_index": 175,
		# "path_to_model": "blender/spiral mountain/",
		# "output_path": "maps/spiral_mountain",
		# "mesh_name": "spiral_mountain",
		# "water_exists": "true",
		# "water_planes": [
			# {
				# "x1": 994,
				# "z1": 823,
				# "x2": 1615,
				# "z2": 1503,
				# "water_height": 60,
				# "red": 255,
				# "green": 255,
				# "blue": 250,
				# "alpha": 230,
				# "material_type": "water",
			# },
		# ]
	# },
	# {
		# "map_name": "banjo's house",
		# "map_index": 169,
		# "path_to_model": "blender/banjos_house/",
		# "output_path": "maps/banjos_house",
		# "mesh_name": "banjos_house",
		# "water_exists": "false",
		# "water_planes": []
	# },
	# {
		# "map_name": "lair entrance",
		# "map_index": 173,
		# "path_to_model": "blender/lair entrance/",
		# "output_path": "maps/lair_entrance",
		# "mesh_name": "lair_entrance",
		# "water_exists": "false",
		# "water_planes": []
	# },
]
print("[1 / 9] - Extracting map files")

us_tables = [1, 2, 3] # [1, 2, 3]
in_kiosk = [6, 8, 0x28, 0x4C, 0x50, 0x51, 0x53]
other_exclusions = []
excluded_maps = in_kiosk + other_exclusions
with open("./rom/dk64_us.z64", "rb") as fq:
	us_pointer = 0x101C50
	limit = 0xC8 # Should be 221, testing early limits for now
	valid_maps = [x for x in list(range(limit)) if x not in excluded_maps]
	for table in us_tables:
		fq.seek(us_pointer + (table << 2))
		table_start = us_pointer + int.from_bytes(fq.read(4), "big")
		print(table)
		for map_id in valid_maps:
			print("-",map_id)
			fq.seek(table_start + (map_id << 2))
			file_start = us_pointer + (int.from_bytes(fq.read(4), "big") & 0x7FFFFFFF)
			file_end = us_pointer + (int.from_bytes(fq.read(4), "big") & 0x7FFFFFFF)
			file_compressed_size = file_end - file_start
			fq.seek(file_start)
			print(hex(file_start), hex(file_compressed_size))
			file_data = fq.read(file_compressed_size)
			fq.seek(file_start)
			indic = int.from_bytes(fq.read(2), "big")
			is_gzip = indic == 0x1F8B
			if file_compressed_size == 8:
				if not is_gzip:
					fq.seek(file_start + 4)
					referenced_file = int.from_bytes(fq.read(4), "big")
					added_name = f"./bin/t{table}_f{referenced_file}.bin"
					file_dict.append({
						"name": f"Table {table - 1} File {referenced_file}",
						"pointer_table_index": table - 1,
						"file_index": referenced_file,
						"source_file": added_name,
						"do_not_extract": True,
					})
					continue
			if is_gzip:
				file_data = zlib.decompress(file_data, (15 + 32))
			file_name = f"./bin/t{table}_f{map_id}.bin"
			with open(file_name, "wb") as fk:
				fk.write(file_data)
			if table == 1:
				geo_us_to_kiosk(file_name)
			file_dict.append({
				"name": f"Table {table - 1} File {map_id}",
				"pointer_table_index": table - 1,
				"file_index": map_id,
				"source_file": file_name,
				"do_not_extract": True,
			})


print("[2 / 9] - Generating map files")
index = 6013 #first unused texture index
if generate_maps:
	for map in map_replacement_models:
		print(" - Generating map file for " + map["map_name"] + ".")
		if(os.path.exists(map["path_to_model"])):
			if(os.path.isfile(map["path_to_model"] + "/model.c")):
				index = generateMap(os.path.abspath(map["path_to_model"]),os.path.abspath(map["output_path"]),map["mesh_name"],map["water_exists"],map["water_planes"],index)
			else:
				print(" - Could not find model.c in specified path: "+map["path_to_model"])
		else:
			print(" - Could not access specified path: " + map["path_to_model"])
	
		#process model and add entry to map_replacements dict
		replacement = [
			{
				"name": map["map_name"],
				"map_index": map["map_index"],
				"map_folder": map["output_path"]
			}
		]
		map_replacements += replacement
	
	#process all main pointer table asset replacements and put them in file_dict
	for root, dirs, files in os.walk(r'bin/build_imports'):
		for file in files:
			if file.endswith('.txt'):
				imports = open("bin/build_imports/"+file,"r").read()
				import_list = eval(imports)
				file_dict += import_list #merge import txt with file_dict
else:
	print(" - Map generation disabled. Set generate_maps to True in build.py to generate map files.")

with open(ROMName, "rb") as fh:
	print("[3 / 9] - Parsing pointer tables")
	parsePointerTables(fh)
	readOverlayOriginalData(fh)

	for x in map_replacements:
		print(" - Processing map replacement " + x["name"])
		if os.path.exists(x["map_folder"]):
			found_geometry = False
			found_floors = False
			found_walls = False
			should_compress_walls = True
			should_compress_floors = True
			for y in pointer_tables:
				if not "encoded_filename" in y:
					continue

				# Convert decoded_filename to encoded_filename using the encoder function
				# Eg. exits.json to exits.bin
				if "encoder" in y and callable(y["encoder"]):
					if "decoded_filename" in y and os.path.exists(x["map_folder"] + y["decoded_filename"]):
						y["encoder"](x["map_folder"] + y["decoded_filename"], x["map_folder"] + y["encoded_filename"])
				
				if os.path.exists(x["map_folder"] + y["encoded_filename"]):
					if y["index"] == 1:
						with open(x["map_folder"] + y["encoded_filename"], "rb") as fg:
							byte_read = fg.read(10)
							should_compress_walls = (byte_read[9] & 0x1) != 0
							should_compress_floors = (byte_read[9] & 0x2) != 0
						found_geometry = True
					elif y["index"] == 2:
						found_walls = True
					elif y["index"] == 3:
						found_floors = True

			# Check that all walls|floors|geometry files exist on disk, or that none of them do
			walls_floors_geometry_valid = (found_geometry == found_walls) and (found_geometry == found_floors)

			if not walls_floors_geometry_valid:
				print("  - WARNING: In map replacement: " + x["name"])
				print("    - Need all 3 files present to replace walls, floors, and geometry.")
				print("    - Only found 1 or 2 of them out of 3. Make sure all 3 exist on disk.")
				print("    - Will skip replacing walls, floors, and geometry to prevent crashes.")

			for y in pointer_tables:
				if not "encoded_filename" in y:
					continue

				if os.path.exists(x["map_folder"] + y["encoded_filename"]):
					# Special case to prevent crashes with custom level geometry, walls, and floors
					# Some of the files are compressed in ROM, some are not
					if y["index"] in [1, 2, 3] and not walls_floors_geometry_valid:
						continue

					do_not_compress = "do_not_compress" in y and y["do_not_compress"]
					if y["index"] == 2:
						do_not_compress = not should_compress_walls
					elif y["index"] == 3:
						do_not_compress = not should_compress_floors

					print("  - Found " + x["map_folder"] + y["encoded_filename"])
					file_dict.append({
						"name": x["name"] + y["name"],
						"pointer_table_index": y["index"],
						"file_index": x["map_index"],
						"source_file": x["map_folder"] + y["encoded_filename"],
						"do_not_extract": True,
						"do_not_compress": do_not_compress,
						"use_external_gzip": "use_external_gzip" in y and y["use_external_gzip"],
					})

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

end_time = time.time()
with open(newROMName, "rb") as fh:
	print()
	print("Built " + newROMName + " in " + str(round(end_time - start_time, 3)) + " seconds")
	print("SHA1: " + hashlib.sha1(fh.read()).hexdigest().upper())