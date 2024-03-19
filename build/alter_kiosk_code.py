from enum import IntEnum, auto

ROMName = "./rom/dk64-kioskrestoration-dev.z64"

TESTING = True

class Level(IntEnum):
    Japes = 0
    Aztec = auto()
    Factory = auto()
    Galleon = auto()
    Fungi = auto()
    Caves = auto()
    Castle = auto()
    Other = auto()

level_indexes = [
    Level.Other, # "TEST MAP", // 00
    Level.Other, # "FUNKY'S STORE", // 01
    Level.Other, # "DK ARCADE", // 02 - Overlay Crash
    Level.Other, # "TINY TEST MAP", // 03
    Level.Japes, # "JUNGLE JAPES - MINING HILL", // 04
    Level.Other, # "CRANKY'S LAB", // 05
    Level.Japes, # "JUNGLE JAPES MINECART RIDE", // 06 - Overlay crash
    Level.Japes, # "JUNGLE JAPES", // 07
    Level.Japes, # "ARMY DILLO", // 08
    Level.Other, # "JETPAC", // 09 - Overlay Crash
    Level.Other, # "KREMLING KOSH AZTEC", // 0A - Overlay Crash
    Level.Aztec, # "EARLY ANGRY AZTEC", // 0B
    Level.Japes, # "JUNGLE JAPES - SHELLHIVE", // 0C
    Level.Japes, # "JUNGLE JAPES - PORTRAIT ROOM", // 0D
    Level.Aztec, # "ANGRY AZTEC SLIDE RACE", // 0E
    Level.Other, # "SNIDE'S HQ", // 0F
    Level.Aztec, # "ANGRY AZTEC - DOME TEMPLE", // 10
    Level.Other, # "TORCH ROOM", // 11
    Level.Other, # "TEETERING TURTLE TROUBLE AZTEC", // 12
    Level.Aztec, # "ANGRY AZTEC 5-DOOR TEMPLE - DK", // 13
    Level.Aztec, # "ANGRY AZTEC - LLAMA TEMPLE", // 14
    Level.Aztec, # "ANGRY AZTEC 5-DOOR TEMPLE - DIDDY", // 15
    Level.Aztec, # "ANGRY AZTEC 5-DOOR TEMPLE - TINY", // 16
    Level.Aztec, # "ANGRY AZTEC 5-DOOR TEMPLE - LANKY", // 17
    Level.Aztec, # "ANGRY AZTEC 5-DOOR TEMPLE - CHUNKY", // 18
    Level.Other, # "CANDY'S SHOP", // 19
    Level.Factory, # "FRANTIC FACTORY", // 1A // (CRASHES UNLESS CUTSCENE TIMER CODE IS ON)
    Level.Factory, # "FRANTIC FACTORY CAR RACE", // 1B
    Level.Factory, # "OLD FRANTIC FACTORY BOSS ARENA", // 1C
    Level.Factory, # "FRANTIC FACTORY - POWER SHED", // 1D
    Level.Galleon, # "GLOOMY GALLEON", // 1E
    Level.Galleon, # "GLOOMY GALLEON - K. ROOL'S SHIP", // 1F
    Level.Other, # "BATTY BARREL BANDIT FACTORY", // 20
    Level.Japes, # "JUNGLE JAPES - UNDERGROUND", // 21
    Level.Japes, # "JAPES ENTRANCE WITH PUFFTOSS", // 22
    Level.Other, # "HELM TARGET MINIGAME", // 23
    Level.Factory, # "FRANTIC FACTORY - CRUSHER ROOM", // 24
    Level.Japes, # "JUNGLE JAPES BLAST COURSE", // 25
    Level.Aztec, # "ANGRY AZTEC", // 26
    Level.Galleon, # "GLOOMY GALLEON SEAL RACE", // 27
    Level.Other, # "OPENING LOGOS", // 28
    Level.Aztec, # "ANGRY AZTEC BLAST COURSE", // 29
    Level.Other, # "TROFF 'N' SCOFF", // 2A
    Level.Galleon, # "GALLEON BIG SHIPWRECK DIDDY/CHUNKY", // 2B
    Level.Galleon, # "GALLEON TREASURE CHEST", // 2C
    Level.Galleon, # "GALLEON MERMAID PALACE", // 2D
    Level.Galleon, # "GALLEON BIG SHIPWRECK DK/TINY", // 2E
    Level.Galleon, # "GALLEON SMALL SHIPWRECK", // 2F
    Level.Fungi, # "FUNGI FOREST", // 30
    Level.Galleon, # "GLOOMY GALLEON - LIGHTHOUSE", // 31
    Level.Other, # "E3 DEMO ROOM", // 32
    Level.Galleon, # "GLOOMY GALLEON - ROBOT FISH", // 33
    Level.Fungi, # "FUNGI FOREST - ANTHILL", // 34
    Level.Other, # "BEAVER BRAWL", // 35
    Level.Galleon, # "GLOOMY GALLEON BLAST COURSE", // 36
    Level.Fungi, # "FUNGI FOREST MINECART RIDE", // 37
    Level.Fungi, # "FUNGI FOREST - DIDDY'S RAFTERS", // 38
    Level.Fungi, # "FUNGI FOREST MILL - WINCH ROOM", // 39
    Level.Fungi, # "FUNGI FOREST MILL - LANKY'S ATTIC", // 3A
    Level.Fungi, # "FUNGI FOREST - THORNVINE BARN", // 3B
    Level.Fungi, # "FUNGI FOREST MILL - SPIDER ROOM", // 3C
    Level.Fungi, # "FUNGI FOREST MILL - 21132 ROOM", // 3D
    Level.Fungi, # "FUNGI FOREST MILL - LOCKED ROOM", // 3E
    Level.Fungi, # "FUNGI FOREST SLAM SHROOMS", // 3F
    Level.Fungi, # "FUNGI FOREST - GIANT MUSHROOM", // 40
    Level.Other, # "STEALTHY SNOOP GALLEON", // 41
    Level.Other, # "UNUSED MAD MAZE MAUL 1", // 42
    Level.Other, # "UNUSED STASH SNATCH 1", // 43
    Level.Other, # "MAD MAZE MAUL JUNGLE", // 44
    Level.Other, # "MAD MAZE MAUL CAVES", // 45
    Level.Fungi, # "FUNGI FOREST MUSHROOM BOUNCE", // 46
    Level.Fungi, # "FUNGI FOREST FACE PUZZLE", // 47
    Level.Other, # "CRYSTAL CAVES", // 48
    Level.Other, # "KRITTER KARNAGE", // 49
    Level.Other, # "STASH SNATCH", // 4A
    Level.Other, # "UNUSED STASH SNATCH 2", // 4B
    Level.Other, # "DK RAP", // 4C
    Level.Other, # "MINECART MAYHEM JUNGLE", // 4D // Doesn't load properly
    Level.Other, # "BUSY BARREL BARRAGE AZTEC", // 4E
    Level.Other, # "BUSY BARREL BARRAGE FOREST", // 4F
    Level.Other, # "TITLE SCREEN", // 50
    Level.Other, # "THANKS FOR PLAYING SCREEN", // 51
    Level.Caves, # "CRYSTAL CAVES SLIDE RACE", // 52
    Level.Other, # "DOGADON 2", // 53
    Level.Caves, # "CRYSTAL CAVES IGLOO - TINY", // 54
    Level.Caves, # "CRYSTAL CAVES IGLOO - LANKY", // 55
    Level.Caves, # "CRYSTAL CAVES IGLOO - DK", // 56
    Level.Castle, # "CREEPY CASTLE", // 57
    Level.Castle, # "CREEPY CASTLE - BALLROOM", // 58
    Level.Caves, # "CRYSTAL CAVES - ROTATING SWITCH CABIN", // 59
    Level.Caves, # "CRYSTAL CAVES - TALL CABIN CHUNKY", // 5A
    Level.Caves, # "CRYSTAL CAVES - TALL CABIN DK", // 5B
    Level.Caves, # "CRYSTAL CAVES - TALL CABIN DIDDY (ENEMIES)", // 5C
    Level.Caves, # "CRYSTAL CAVES - TALL CABIN TINY", // 5D
    Level.Other, # "SWINGING LIGHTS AND A GNAWTY", // 5E
    Level.Caves, # "CRYSTAL CAVES IGLOO - CHUNKY", // 5F
    Level.Other, # "SPLISH-SPLASH SALVAGE JUNGLE", // 60
    Level.Other, # "K. LUMSY'S PRISON", // 61
    Level.Other, # "ICE TOMATO PALACE", // 62
    Level.Other, # "SPEEDY SWING SORTIE JUNGLE", // 63
    Level.Caves, # "CRYSTAL CAVES IGLOO - DIDDY", // 64
    Level.Other, # "KRAZY KONG KLAMOUR FACTORY", // 65
    Level.Other, # "BIG BUG BASH AZTEC", // 66
    Level.Other, # "SEARCHLIGHT SEEK GALLEON", // 67
    Level.Other, # "BEAVER BOTHER FACTORY", // 68
    Level.Castle, # "CREEPY CASTLE - VENT TOWER", // 69
    Level.Castle, # "CREEPY CASTLE MINECART RIDE", // 6A
    Level.Other, # "MULTIPLAYER BATTLE ARENA", // 6B
    Level.Castle, # "CREEPY CASTLE - LANKY/TINY'S CRYPT", // 6C
    Level.Other, # "NOTHING? (MONKEY SMASH ARENA 1)", // 6D
    Level.Factory, # "FACTORY BLAST COURSE", // 6E
    Level.Galleon, # "PUFTOSS", // 6F
    Level.Castle, # "CREEPY CASTLE - SKULL CRYPT", // 70
    Level.Castle, # "CREEPY CASTLE - MUSEUM", // 71
    Level.Castle, # "CREEPY CASTLE - LIBRARY", // 72
    Level.Other, # "KREMLING KOSH GALLEON", // 73
    Level.Other, # "KREMLING KOSH CASTLE", // 74
    Level.Other, # "KREMLING KOSH ISLES/SNIDE'S", // 75
    Level.Other, # "TEETERING TURTLE TROUBLE FOREST", // 76
    Level.Other, # "TEETERING TURTLE TROUBLE CASTLE", // 77
    Level.Other, # "TEETERING TURTLE TROUBLE SNIDE'S", // 78
    Level.Other, # "BATTY BARREL BANDIT GALLEON", // 79
    Level.Other, # "BATTY BARREL BANDIT ISLES", // 7A
    Level.Other, # "BATTY BARREL BANDIT SNIDE'S", // 7B
    Level.Other, # "UNUSED MAD MAZE MAUL 2", // 7C
    Level.Other, # "UNUSED STASH SNATCH 3", // 7D
    Level.Other, # "STEALTHY SNOOP AZTEC", // 7E
    Level.Other, # "UNUSED STEALTHY SNOOP 2", // 7F
    Level.Other, # "UNUSED STEALTHY SNOOP 3", // 80
    Level.Other, # "MINECART MAYHEM FOREST", // 81
    Level.Other, # "MINECART MAYHEM CASTLE", // 82
    Level.Other, # "BUSY BARREL BARRAGE CAVES", // 83
    Level.Other, # "UNUSED SPLISH-SPLASH SALVAGE", // 84
    Level.Other, # "SPLISH-SPLASH SALVAGE GALLEON", // 85
    Level.Other, # "SPEEDY SWING SORTIE FOREST", // 86
    Level.Other, # "UNUSED SPEEDY SWING SORTIE", // 87
    Level.Other, # "BEAVER BOTHER CASTLE", // 88
    Level.Other, # "BEAVER BOTHER SNIDE'S", // 89
    Level.Other, # "SEARCHLIGHT SEEK SNIDE'S", // 8A
    Level.Other, # "SEARCHLIGHT SEEK CAVES", // 8B
    Level.Other, # "SEARCHLIGHT SEEK CASTLE/ISLES", // 8C
    Level.Other, # "KRAZY KONG KLAMOUR GALLEON", // 8D
    Level.Other, # "KRAZY KONG KLAMOUR FOREST/CAVES", // 8E
    Level.Other, # "KRAZY KONG KLAMOUR SNIDE'S", // 8F
    Level.Other, # "PERIL PATH PANIC FACTORY", // 90
    Level.Other, # "PERIL PATH PANIC FOREST", // 91
    Level.Other, # "PERIL PATH PANIC ISLES/SNIDE'S", // 92
    Level.Other, # "UNUSED PERIL PATH PANIC", // 93
    Level.Other, # "BIG BUG BASH GALLEON", // 94
    Level.Other, # "BIG BUG BASH ISLES", // 95
    Level.Other, # "BIG BUG BASH CASTLE/SNIDE'S", // 96
    Level.Castle, # "CREEPY CASTLE - CANDY'S CATACOMBS", // 97
    Level.Other, # "HIDEOUT HELM (INTRO STORY VERSION)", // 98
    Level.Other, # "DK ISLES (INTRO STORY VERSION)", // 99
    Level.Factory, # "MAD JACK", // 9A
    Level.Other, # "ARENA AMBUSH", // 9B
    Level.Other, # "MORE KRITTER KARNAGE", // 9C
    Level.Other, # "FOREST FRACAS", // 9D
    Level.Other, # "BISH BASH BRAWL", // 9E
    Level.Other, # "KAMIKAZE KREMLINGS", // 9F
    Level.Other, # "PLINTH PANIC", // A0
    Level.Other, # "PINNACLE PALAVER", // A1
    Level.Other, # "SHOCKWAVE SHOWDOWN", // A2
    Level.Castle, # "CREEPY CASTLE - DUNGEONS", // A3
    Level.Castle, # "CREEPY CASTLE - TREE", // A4
]


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
        fh.seek(kiosk_ram_to_rom(0x806B5A6C)) # Title Screen
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
        # Cancel map entry cancel
        fh.seek(kiosk_ram_to_rom(0x806b5ddc))
        fh.write((0).to_bytes(4, "big"))
        # Copyright Message
        fh.seek(kiosk_ram_to_rom(0x80709DA8))
        bottom_text = "HACK BY BALLAAM\0"
        fh.write(bottom_text.encode("ascii"))
        # Level Indexes
        fh.seek(kiosk_ram_to_rom(0x806F1D10))
        for lvl in level_indexes:
            fh.write(int(lvl).to_bytes(1, "big"))
        # Thread priorities
        # fh.seek(kiosk_ram_to_rom(0x805903AE))
        # fh.write((0).to_bytes(2, "big"))
        # fh.seek(kiosk_ram_to_rom(0x80594D5E))
        # fh.write((0x14).to_bytes(2, "big"))
        # fh.seek(kiosk_ram_to_rom(0x80590816))
        # fh.write((0x19).to_bytes(2, "big"))
