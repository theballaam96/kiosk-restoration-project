table_offset = 0x1A7C20

with open("dk64-kioskrestoration-dev.z64", "rb") as fh:
    for table in range(3):
        fh.seek(table_offset + (table * 4))
        table_start = table_offset + int.from_bytes(fh.read(4), "big")
        for file in range(0xA5):
            fh.seek(table_start + (file << 2))
            file_start = table_offset + (int.from_bytes(fh.read(4), "big") & 0x7FFFFFFF)
            file_end = table_offset + (int.from_bytes(fh.read(4), "big") & 0x7FFFFFFF)
            file_size = file_end - file_start
            print(f"Table {table} File {file}: {hex(file_size)}")