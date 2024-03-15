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