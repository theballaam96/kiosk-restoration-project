#include "../include/common.h"

static char* map_names[] = {
    "TEST MAP", // 00
    "FUNKY'S STORE", // 01
    "DK ARCADE", // 02
    "TINY TEST MAP", // 03
    "JUNGLE JAPES - MINING HILL", // 04
    "CRANKY'S LAB", // 05
    "JUNGLE JAPES MINECART RIDE", // 06
    "JUNGLE JAPES", // 07
    "ARMY DILLO", // 08
    "JETPAC", // 09
    "KREMLING KOSH AZTEC", // 0A
    "EARLY ANGRY AZTEC", // 0B
    "JUNGLE JAPES - SHELLHIVE", // 0C
    "JUNGLE JAPES - PORTRAIT ROOM", // 0D
    "ANGRY AZTEC SLIDE RACE", // 0E
    "SNIDE'S HQ", // 0F
    "ANGRY AZTEC - DOME TEMPLE", // 10
    "TORCH ROOM", // 11
    "TEETERING TURTLE TROUBLE AZTEC", // 12
    "ANGRY AZTEC 5-DOOR TEMPLE - DK", // 13
    "ANGRY AZTEC - LLAMA TEMPLE", // 14
    "ANGRY AZTEC 5-DOOR TEMPLE - DIDDY", // 15
    "ANGRY AZTEC 5-DOOR TEMPLE - TINY", // 16
    "ANGRY AZTEC 5-DOOR TEMPLE - LANKY", // 17
    "ANGRY AZTEC 5-DOOR TEMPLE - CHUNKY", // 18
    "CANDY'S SHOP", // 19
    "FRANTIC FACTORY", // 1A // (CRASHES UNLESS CUTSCENE TIMER CODE IS ON)
    "FRANTIC FACTORY CAR RACE", // 1B
    "OLD FRANTIC FACTORY BOSS ARENA", // 1C
    "FRANTIC FACTORY - POWER SHED", // 1D
    "GLOOMY GALLEON", // 1E
    "GLOOMY GALLEON - K. ROOL'S SHIP", // 1F
    "BATTY BARREL BANDIT FACTORY", // 20
    "JUNGLE JAPES - UNDERGROUND", // 21
    "JAPES ENTRANCE WITH PUFFTOSS", // 22
    "HELM TARGET MINIGAME", // 23
    "FRANTIC FACTORY - CRUSHER ROOM", // 24
    "JUNGLE JAPES BLAST COURSE", // 25
    "ANGRY AZTEC", // 26
    "GLOOMY GALLEON SEAL RACE", // 27
    "OPENING LOGOS", // 28
    "ANGRY AZTEC BLAST COURSE", // 29
    "TROFF 'N' SCOFF", // 2A
    "GALLEON BIG SHIPWRECK DIDDY/CHUNKY", // 2B
    "GALLEON TREASURE CHEST", // 2C
    "GALLEON MERMAID PALACE", // 2D
    "GALLEON BIG SHIPWRECK DK/TINY", // 2E
    "GALLEON SMALL SHIPWRECK", // 2F
    "FUNGI FOREST", // 30
    "GLOOMY GALLEON - LIGHTHOUSE", // 31
    "E3 DEMO ROOM", // 32
    "GLOOMY GALLEON - ROBOT FISH", // 33
    "FUNGI FOREST - ANTHILL", // 34
    "BEAVER BRAWL", // 35
    "GLOOMY GALLEON BLAST COURSE", // 36
    "FUNGI FOREST MINECART RIDE", // 37
    "FUNGI FOREST - DIDDY'S RAFTERS", // 38
    "FUNGI FOREST MILL - WINCH ROOM", // 39
    "FUNGI FOREST MILL - LANKY'S ATTIC", // 3A
    "FUNGI FOREST - THORNVINE BARN", // 3B
    "FUNGI FOREST MILL - SPIDER ROOM", // 3C
    "FUNGI FOREST MILL - 21132 ROOM", // 3D
    "FUNGI FOREST MILL - LOCKED ROOM", // 3E
    "FUNGI FOREST SLAM SHROOMS", // 3F
    "FUNGI FOREST - GIANT MUSHROOM", // 40
    "STEALTHY SNOOP GALLEON", // 41
    "UNUSED MAD MAZE MAUL 1", // 42
    "UNUSED STASH SNATCH 1", // 43
    "MAD MAZE MAUL JUNGLE", // 44
    "MAD MAZE MAUL CAVES", // 45
    "FUNGI FOREST MUSHROOM BOUNCE", // 46
    "FUNGI FOREST FACE PUZZLE", // 47
    "CRYSTAL CAVES", // 48
    "KRITTER KARNAGE", // 49
    "STASH SNATCH", // 4A
    "UNUSED STASH SNATCH 2", // 4B
    "DK RAP", // 4C
    "MINECART MAYHEM JUNGLE", // 4D // Doesn't load properly
    "BUSY BARREL BARRAGE AZTEC", // 4E
    "BUSY BARREL BARRAGE FOREST", // 4F
    "TITLE SCREEN", // 50
    "THANKS FOR PLAYING SCREEN", // 51
    "CRYSTAL CAVES SLIDE RACE", // 52
    "DOGADON 2", // 53
    "CRYSTAL CAVES IGLOO - TINY", // 54
    "CRYSTAL CAVES IGLOO - LANKY", // 55
    "CRYSTAL CAVES IGLOO - DK", // 56
    "CREEPY CASTLE", // 57
    "CREEPY CASTLE - BALLROOM", // 58
    "CRYSTAL CAVES - ROTATING SWITCH CABIN", // 59
    "CRYSTAL CAVES - TALL CABIN CHUNKY", // 5A
    "CRYSTAL CAVES - TALL CABIN DK", // 5B
    "CRYSTAL CAVES - TALL CABIN DIDDY (ENEMIES)", // 5C
    "CRYSTAL CAVES - TALL CABIN TINY", // 5D
    "SWINGING LIGHTS AND A GNAWTY", // 5E
    "CRYSTAL CAVES IGLOO - CHUNKY", // 5F
    "SPLISH-SPLASH SALVAGE JUNGLE", // 60
    "K. LUMSY'S PRISON", // 61
    "ICE TOMATO PALACE", // 62
    "SPEEDY SWING SORTIE JUNGLE", // 63
    "CRYSTAL CAVES IGLOO - DIDDY", // 64
    "KRAZY KONG KLAMOUR FACTORY", // 65
    "BIG BUG BASH AZTEC", // 66
    "SEARCHLIGHT SEEK GALLEON", // 67
    "BEAVER BOTHER FACTORY", // 68
    "CREEPY CASTLE - VENT TOWER", // 69
    "CREEPY CASTLE MINECART RIDE", // 6A
    "MULTIPLAYER BATTLE ARENA", // 6B
    "CREEPY CASTLE - LANKY/TINY'S CRYPT", // 6C
    "NOTHING? (MONKEY SMASH ARENA 1)", // 6D
    "FACTORY BLAST COURSE", // 6E
    "PUFTOSS", // 6F
    "CREEPY CASTLE - SKULL CRYPT", // 70
    "CREEPY CASTLE - MUSEUM", // 71
    "CREEPY CASTLE - LIBRARY", // 72
    "KREMLING KOSH GALLEON", // 73
    "KREMLING KOSH CASTLE", // 74
    "KREMLING KOSH ISLES/SNIDE'S", // 75
    "TEETERING TURTLE TROUBLE FOREST", // 76
    "TEETERING TURTLE TROUBLE CASTLE", // 77
    "TEETERING TURTLE TROUBLE SNIDE'S", // 78
    "BATTY BARREL BANDIT GALLEON", // 79
    "BATTY BARREL BANDIT ISLES", // 7A
    "BATTY BARREL BANDIT SNIDE'S", // 7B
    "UNUSED MAD MAZE MAUL 2", // 7C
    "UNUSED STASH SNATCH 3", // 7D
    "STEALTHY SNOOP AZTEC", // 7E
    "UNUSED STEALTHY SNOOP 2", // 7F
    "UNUSED STEALTHY SNOOP 3", // 80
    "MINECART MAYHEM FOREST", // 81
    "MINECART MAYHEM CASTLE", // 82
    "BUSY BARREL BARRAGE CAVES", // 83
    "UNUSED SPLISH-SPLASH SALVAGE", // 84
    "SPLISH-SPLASH SALVAGE GALLEON", // 85
    "SPEEDY SWING SORTIE FOREST", // 86
    "UNUSED SPEEDY SWING SORTIE", // 87
    "BEAVER BOTHER CASTLE", // 88
    "BEAVER BOTHER SNIDE'S", // 89
    "SEARCHLIGHT SEEK SNIDE'S", // 8A
    "SEARCHLIGHT SEEK CAVES", // 8B
    "SEARCHLIGHT SEEK CASTLE/ISLES", // 8C
    "KRAZY KONG KLAMOUR GALLEON", // 8D
    "KRAZY KONG KLAMOUR FOREST/CAVES", // 8E
    "KRAZY KONG KLAMOUR SNIDE'S", // 8F
    "PERIL PATH PANIC FACTORY", // 90
    "PERIL PATH PANIC FOREST", // 91
    "PERIL PATH PANIC ISLES/SNIDE'S", // 92
    "UNUSED PERIL PATH PANIC", // 93
    "BIG BUG BASH GALLEON", // 94
    "BIG BUG BASH ISLES", // 95
    "BIG BUG BASH CASTLE/SNIDE'S", // 96
    "CREEPY CASTLE - CANDY'S CATACOMBS", // 97
    "HIDEOUT HELM (INTRO STORY VERSION)", // 98
    "DK ISLES (INTRO STORY VERSION)", // 99
    "MAD JACK", // 9A
    "ARENA AMBUSH", // 9B
    "MORE KRITTER KARNAGE", // 9C
    "FOREST FRACAS", // 9D
    "BISH BASH BRAWL", // 9E
    "KAMIKAZE KREMLINGS", // 9F
    "PLINTH PANIC", // A0
    "PINNACLE PALAVER", // A1
    "SHOCKWAVE SHOWDOWN", // A2
    "CREEPY CASTLE - DUNGEONS", // A3
    "CREEPY CASTLE - TREE", // A4
};

static unsigned char selected_map = 0;

/*
    FONT DOCUMENTATION
    0 - Groovy font
    1 - Yellow font
    2 - Game over big font
    3 - Arcade font
    4 - ?
    5 - Jetpac
    6 - Smaller jetpac
    7 - White font
    8 - Crash
    9/A - ?
*/

int* displayMapName(int* dl) {
    if ((ObjectTimer & 3) == 0) {
        if (ControllerInput.stickX < -0x28) {
            // Left
            if (selected_map == 0) {
                selected_map = 0xA4;
            } else {
                selected_map -= 1;
            }
        } else if (ControllerInput.stickX > 0x28) {
            // Right
            if (selected_map == 0xA4) {
                selected_map = 0;
            } else {
                selected_map += 1;
            }
        }
    }
    // Clamp
    if (selected_map > 0xA4) {
        selected_map = 0;
    }
    for (int i = 0; i < 3; i++) {
        DemoMaps[i].map = selected_map;
    }
    int center = 0x280;
    int width = getStringWidth(7, map_names[selected_map]);
    int x_pos = center - (width << 1);
    int y_pos = *(char*)(0x806F1CE8) * 0x2A8;
    // *(int*)(dl++) = 0xE7000000;
    // *(int*)(dl++) = 0x00000000;
    // *(int*)(dl++) = 0xDE000000;
    // *(int*)(dl++) = 0x01000118;
    // *(int*)(dl++) = 0xE3000A01;
    // *(int*)(dl++) = 0x00000000;
    // *(int*)(dl++) = 0xE200001C;
    // *(int*)(dl++) = 0x00504240;
    *(int*)(dl++) = 0xFA000000;
    *(int*)(dl++) = 0xFFFFFFFF;
    *(int*)(dl++) = 0xDA380007;
    *(int*)(dl++) = 0x020000C0;
    *(int*)(dl++) = 0xFC119623;
    *(int*)(dl++) = 0xFF2FFFFF;
    return displayText(dl, 7, x_pos, y_pos, map_names[selected_map], 4);
}