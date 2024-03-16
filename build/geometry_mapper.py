import json

def geo_us_to_kiosk(file_name: str):
    start_data = None
    end_data = None
    with open(file_name, "rb") as fh:
        start_data = fh.read(0x26)
        fh.seek(0x2E)
        end_data = fh.read()
    with open(file_name, "wb") as fh:
        fh.write(start_data)
        fh.write(end_data)
    with open(file_name, "r+b") as fh:
        for x in range(0x11):
            fh.seek(0x28 + (4 * x))
            old = int.from_bytes(fh.read(4), "big")
            if old == 0:
                continue
            fh.seek(0x28 + (4 * x))
            new = old - 0x8
            fh.write(new.to_bytes(4, "big"))
        # Texture re-mapping
        fh.seek(0x2C)
        start_pointer = int.from_bytes(fh.read(4), "big")
        end_pointer = int.from_bytes(fh.read(4), "big")
        dl_count = int((end_pointer - start_pointer) / 8)
        f = open("./build/texture_mapping.json")
        mapping_data = json.load(f)
        for x in range(dl_count):
            fh.seek(start_pointer + (x * 8))
            command = int.from_bytes(fh.read(1), "big")
            if command != 0xFD:
                continue
            fh.seek(start_pointer + (x * 8) + 4)
            tex_idx = int.from_bytes(fh.read(4), "big")
            if str(tex_idx) in mapping_data:
                fh.seek(start_pointer + (x * 8) + 4)
                fh.write((mapping_data[str(tex_idx)]).to_bytes(4, "big"))