import json
import zlib

def fast_similarity_score(byte_array1, byte_array2):
    if len(byte_array1) != len(byte_array2):
        return 0

    length = len(byte_array1)
    if length == 0:
        return 1.0

    matching_bytes = sum(1 for b1, b2 in zip(byte_array1, byte_array2) if b1 == b2)
    return matching_bytes / length

data = [
    {"name": "kiosk", "sha": [], "offset": 0x1A7C20, "table": 24},
    {"name": "us", "sha": [], "offset": 0x101C50, "table": 25},
]

mapping = {}

for item in data:
    with open(f"../rom/dk64_{item['name']}.z64", "rb") as fh:
        fh.seek(item["offset"] + (item["table"] << 2) + (32 << 2))
        count = int.from_bytes(fh.read(4), "big")
        fh.seek(item["offset"] + (item["table"] << 2))
        table_start = item["offset"] + int.from_bytes(fh.read(4), "big")
        for x in range(count):
            fh.seek(table_start + (x << 2))
            file_start = item["offset"] + (int.from_bytes(fh.read(4), "big") & 0x7FFFFFFF)
            file_end = item["offset"] + (int.from_bytes(fh.read(4), "big") & 0x7FFFFFFF)
            file_size = file_end - file_start
            if file_size <= 0:
                continue
            fh.seek(file_start)
            compressed_data = zlib.decompress(fh.read(file_size), (15 + 32))
            item["sha"].append(compressed_data)

SIMILARITY_THRESHOLD = 0.9

unmatched = []

for xi, x in enumerate(data[1]["sha"]):
    index = 0
    set_match = False
    max_mapping_score = 0
    max_mapping_item = 0
    while True:
        score = fast_similarity_score(bytearray(x), bytearray(data[0]["sha"][index]))
        if score == 1:
            mapping[xi] = index
            break
        elif score > max_mapping_score:
            if score >= SIMILARITY_THRESHOLD:
                mapping[xi] = index
                set_match = True
            max_mapping_score = score
            max_mapping_item = index
        index += 1
        if index >= len(data[0]["sha"]):
            if not set_match:
                unmatched.append({
                    "us_texture": xi,
                    "kiosk_closest": max_mapping_item,
                    "confidence": max_mapping_score
                })
                print("Unmatched", xi, "Max Score:", max_mapping_score,"(",max_mapping_item,")")
            break

with open("tex_mapping_calculated.json", "w") as fh:
    fh.write(json.dumps(mapping, indent=4))
with open("unmatched_textures.json", "w") as fh:
    fh.write(json.dumps(unmatched, indent=4))


