ROMName = "./rom/dk64-kioskrestoration-dev.z64"

TESTING = True

def kiosk_ram_to_rom(address: int):
    return (0x101000 - 0x80690000) + address

def code_modifications():
    with open(ROMName, "r+b") as fh:
        # Cancel overwrite of map index
        fh.seek(kiosk_ram_to_rom(0x80592EC0))
        fh.write((0x03E00008).to_bytes(4, "big"))
        fh.write((0x24020001).to_bytes(4, "big"))
        # Cancel Kickout Timer
        fh.seek(kiosk_ram_to_rom(0x806B5E90)) # Gameplay
        fh.write((0).to_bytes(4, "big"))
        fh.seek(kiosk_ram_to_rom(0x806B4F5C)) # Title Screen
        fh.write((0).to_bytes(4, "big"))
        fh.seek(kiosk_ram_to_rom(0x806B4F1C)) # Title Screen
        fh.write((0).to_bytes(4, "big"))
        # Speed boot
        if TESTING:
            # Immediate pull out of Nin Logo
            fh.seek(kiosk_ram_to_rom(0x806B515C))
            fh.write((0x1000).to_bytes(2, "big"))
            # Change dest map
            fh.seek(kiosk_ram_to_rom(0x806B5192))
            fh.write((0x3).to_bytes(2, "big"))
            fh.seek(kiosk_ram_to_rom(0x806B519E))
            fh.write((0x50).to_bytes(2, "big"))
        # Cancel move wipe
        fh.seek(kiosk_ram_to_rom(0x806b5fdc))
        fh.write((0).to_bytes(4, "big"))
        # Copyright Message
        fh.seek(kiosk_ram_to_rom(0x80709DA8))
        bottom_text = "HACK BY BALLAAM\0"
        fh.write(bottom_text.encode("ascii"))
