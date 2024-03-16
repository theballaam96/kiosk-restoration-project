import zlib
from alter_kiosk_code import kiosk_ram_to_rom

USROM = "./rom/dk64_us.z64"
newROMName = "./rom/dk64-kioskrestoration-dev.z64"

def getLo(val: int) -> int:
    return val & 0xFFFF

def getHi(val: int) -> int:
    raw = (val >> 16) & 0xFFFF
    lo = getLo(val)
    if lo & 0x8000:
        return raw + 1
    return raw

def pullSongsFromROM() -> int:
    song_cap = 0x7A
    us_offset = 0x101C50
    midi_data = []
    with open(USROM, "rb") as fh:
        fh.seek(us_offset)
        midi_table = us_offset + int.from_bytes(fh.read(4), "big")
        for x in range(song_cap):
            fh.seek(midi_table + (x << 2))
            file_start = us_offset + (int.from_bytes(fh.read(4), "big") & 0x7FFFFFFF)
            file_end = us_offset + (int.from_bytes(fh.read(4), "big") & 0x7FFFFFFF)
            file_size = file_end - file_start
            if file_size == 0:
                midi_data.append(b"")
                continue
            fh.seek(file_start)
            file_data = zlib.decompress(fh.read(file_size), (15 + 32))
            midi_data.append(file_data)
    total_size = 4 + (song_cap << 3)
    write_start = 0x2000000
    with open(newROMName, "r+b") as fh:
        fh.seek(write_start)
        fh.write(song_cap.to_bytes(4, "big"))
        for x in midi_data:
            fh.write(total_size.to_bytes(4, "big"))
            fh.write(len(x).to_bytes(4, "big"))
            total_size += len(x)
            if (total_size & 3) != 0: # Ensure 4 byte alignment
                total_size += (4 - (total_size & 3))
        for x in midi_data:
            fh.write(x)
            position = fh.tell()
            if (position & 3) != 0: # Ensure 4 byte alignment
                add = 4 - (position & 3)
                fh.write((0).to_bytes(add, "big"))
        # Code Modifications
        start_hi = getHi(write_start)
        start_lo = getLo(write_start)
        # 
        fh.seek(kiosk_ram_to_rom(0x80594EF2))
        fh.write(start_hi.to_bytes(2, "big"))
        fh.seek(kiosk_ram_to_rom(0x80594F02))
        fh.write(start_lo.to_bytes(2, "big"))
        # 
        fh.seek(kiosk_ram_to_rom(0x80594F62))
        fh.write(start_hi.to_bytes(2, "big"))
        fh.seek(kiosk_ram_to_rom(0x80594F6E))
        fh.write(start_lo.to_bytes(2, "big"))
        # 
        fh.seek(kiosk_ram_to_rom(0x80594F8A))
        fh.write(start_hi.to_bytes(2, "big"))
        fh.seek(kiosk_ram_to_rom(0x80594F8E))
        fh.write(start_lo.to_bytes(2, "big"))
    return total_size
    