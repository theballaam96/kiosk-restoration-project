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
    "CRYSTAL CAVES - LANKY CABIN", // 5E
    "CRYSTAL CAVES IGLOO - CHUNKY", // 5F
    "SPLISH-SPLASH SALVAGE JUNGLE", // 60
    "K. LUMSY'S PRISON", // 61
    "CRYSTAL CAVES - ICE TOMATO PALACE", // 62
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
    "DONKEY KONG 64K", // A5 - CUSTOM ENTRY POINT
};

static char* kong_names[] = {
    "DK",
    "DIDDY",
    "LANKY",
    "TINY",
    "CHUNKY",
};

static char* dktv_demo_names[] = {
    "JAPES MOUNTAIN",
    "ANGRY AZTEC",
    "SEASICK SHIP",
    "GLOOMY GALLEON",
    "FUNGI FOREST",
    "SEAL RACE",
};

static char* level_subsets[] = {
    "JAPES",
    "AZTEC",
    "FACTORY",
    "GALLEON",
    "FUNGI",
    "CAVES",
    "CASTLE",
    "BONUS",
    "ARENAS",
    "DKTV DEMOS",
    "OTHER",
};

typedef enum option_sets {
    /* 0x000 */ OPTIONSET_LEVEL,
    /* 0x001 */ OPTIONSET_MAP,
    /* 0x002 */ OPTIONSET_KONG,
} option_sets;

typedef enum level_set {
    /* 0x000 */ LEVELSET_JAPES,
    /* 0x001 */ LEVELSET_AZTEC,
    /* 0x002 */ LEVELSET_FACTORY,
    /* 0x003 */ LEVELSET_GALLEON,
    /* 0x004 */ LEVELSET_FUNGI,
    /* 0x005 */ LEVELSET_CAVES,
    /* 0x006 */ LEVELSET_CASTLE,
    /* 0x007 */ LEVELSET_BONUS,
    /* 0x008 */ LEVELSET_ARENAS,
    /* 0x009 */ LEVELSET_DKTV,
    /* 0x00A */ LEVELSET_OTHER,
} level_set;

static unsigned char japes_maps[] = {
    0x04, // "JUNGLE JAPES - MINING HILL"
    0x06, // "JUNGLE JAPES MINECART RIDE"
    0x07, // "JUNGLE JAPES"
    0x08, // "ARMY DILLO"
    0x0C, // "JUNGLE JAPES - SHELLHIVE"
    0x0D, // "JUNGLE JAPES - PORTRAIT ROOM"
    0x21, // "JUNGLE JAPES - UNDERGROUND"
    0x22, // "JAPES ENTRANCE WITH PUFFTOSS"
    0x25, // "JUNGLE JAPES BLAST COURSE"
};

static unsigned char aztec_maps[] = {
    0x0B, // "EARLY ANGRY AZTEC"
    0x0E, // "ANGRY AZTEC SLIDE RACE"
    0x10, // "ANGRY AZTEC - DOME TEMPLE"
    0x13, // "ANGRY AZTEC 5-DOOR TEMPLE - DK"
    0x14, // "ANGRY AZTEC - LLAMA TEMPLE"
    0x15, // "ANGRY AZTEC 5-DOOR TEMPLE - DIDDY"
    0x16, // "ANGRY AZTEC 5-DOOR TEMPLE - TINY"
    0x17, // "ANGRY AZTEC 5-DOOR TEMPLE - LANKY"
    0x18, // "ANGRY AZTEC 5-DOOR TEMPLE - CHUNKY"
    0x26, // "ANGRY AZTEC"
    0x29, // "ANGRY AZTEC BLAST COURSE"
};

static unsigned char factory_maps[] = {
    0x1A, // "FRANTIC FACTORY"
    0x1B, // "FRANTIC FACTORY CAR RACE"
    0x1C, // "OLD FRANTIC FACTORY BOSS ARENA"
    0x1D, // "FRANTIC FACTORY - POWER SHED"
    0x24, // "FRANTIC FACTORY - CRUSHER ROOM"
    0x6E, // "FACTORY BLAST COURSE"
    0x9A, // "MAD JACK"
};

static unsigned char galleon_maps[] = {
    0x1E, // "GLOOMY GALLEON"
    0x1F, // "GLOOMY GALLEON - K. ROOL'S SHIP"
    0x27, // "GLOOMY GALLEON SEAL RACE"
    0x2B, // "GALLEON BIG SHIPWRECK DIDDY/CHUNKY"
    0x2C, // "GALLEON TREASURE CHEST"
    0x2D, // "GALLEON MERMAID PALACE"
    0x2E, // "GALLEON BIG SHIPWRECK DK/TINY"
    0x2F, // "GALLEON SMALL SHIPWRECK"
    0x31, // "GLOOMY GALLEON - LIGHTHOUSE"
    0x33, // "GLOOMY GALLEON - ROBOT FISH"
    0x36, // "GLOOMY GALLEON BLAST COURSE"
    0x6F, // "PUFTOSS"
};

static unsigned char fungi_maps[] = {
    0x30, // "FUNGI FOREST"
    0x34, // "FUNGI FOREST - ANTHILL"
    0x37, // "FUNGI FOREST MINECART RIDE"
    0x38, // "FUNGI FOREST - DIDDY'S RAFTERS"
    0x39, // "FUNGI FOREST MILL - WINCH ROOM"
    0x3A, // "FUNGI FOREST MILL - LANKY'S ATTIC"
    0x3B, // "FUNGI FOREST - THORNVINE BARN"
    0x3C, // "FUNGI FOREST MILL - SPIDER ROOM"
    0x3D, // "FUNGI FOREST MILL - 21132 ROOM"
    0x3E, // "FUNGI FOREST MILL - LOCKED ROOM"
    0x3F, // "FUNGI FOREST SLAM SHROOMS"
    0x40, // "FUNGI FOREST - GIANT MUSHROOM"
    0x46, // "FUNGI FOREST MUSHROOM BOUNCE"
    0x47, // "FUNGI FOREST FACE PUZZLE"
    0x53, // "DOGADON 2"
};

static unsigned char caves_maps[] = {
    0x48, // "CRYSTAL CAVES"
    0x52, // "CRYSTAL CAVES SLIDE RACE"
    0x54, // "CRYSTAL CAVES IGLOO - TINY"
    0x55, // "CRYSTAL CAVES IGLOO - LANKY"
    0x56, // "CRYSTAL CAVES IGLOO - DK"
    0x59, // "CRYSTAL CAVES - ROTATING SWITCH CABIN"
    0x5A, // "CRYSTAL CAVES - TALL CABIN CHUNKY"
    0x5B, // "CRYSTAL CAVES - TALL CABIN DK"
    0x5C, // "CRYSTAL CAVES - TALL CABIN DIDDY (ENEMIES)"
    0x5D, // "CRYSTAL CAVES - TALL CABIN TINY"
    0x5E, // "CRYSTAL CAVES - LANKY CABIN"
    0x5F, // "CRYSTAL CAVES IGLOO - CHUNKY"
    0x62, // "CRYSTAL CAVES - ICE TOMATO PALACE"
    0x64, // "CRYSTAL CAVES IGLOO - DIDDY"
};

static unsigned char castle_maps[] = {
    0x57, // "CREEPY CASTLE"
    0x58, // "CREEPY CASTLE - BALLROOM"
    0x69, // "CREEPY CASTLE - VENT TOWER"
    0x6A, // "CREEPY CASTLE MINECART RIDE"
    0x6C, // "CREEPY CASTLE - LANKY/TINY'S CRYPT"
    0x70, // "CREEPY CASTLE - SKULL CRYPT"
    0x71, // "CREEPY CASTLE - MUSEUM"
    0x72, // "CREEPY CASTLE - LIBRARY"
    0x97, // "CREEPY CASTLE - CANDY'S CATACOMBS"
    0xA3, // "CREEPY CASTLE - DUNGEONS"
    0xA4, // "CREEPY CASTLE - TREE"
};

static unsigned char bonus_maps[] = {
    0x0A, // "KREMLING KOSH AZTEC"
    0x12, // "TEETERING TURTLE TROUBLE AZTEC"
    0x20, // "BATTY BARREL BANDIT FACTORY"
    0x23, // "HELM TARGET MINIGAME"
    0x41, // "STEALTHY SNOOP GALLEON"
    0x42, // "UNUSED MAD MAZE MAUL 1"
    0x43, // "UNUSED STASH SNATCH 1"
    0x44, // "MAD MAZE MAUL JUNGLE"
    0x45, // "MAD MAZE MAUL CAVES"
    0x4A, // "STASH SNATCH"
    0x4B, // "UNUSED STASH SNATCH 2"
    0x4D, // "MINECART MAYHEM JUNGLE"
    0x4E, // "BUSY BARREL BARRAGE AZTEC"
    0x4F, // "BUSY BARREL BARRAGE FOREST"
    0x60, // "SPLISH-SPLASH SALVAGE JUNGLE"
    0x63, // "SPEEDY SWING SORTIE JUNGLE"
    0x65, // "KRAZY KONG KLAMOUR FACTORY"
    0x66, // "BIG BUG BASH AZTEC"
    0x67, // "SEARCHLIGHT SEEK GALLEON"
    0x68, // "BEAVER BOTHER FACTORY"
    0x73, // "KREMLING KOSH GALLEON"
    0x74, // "KREMLING KOSH CASTLE"
    0x75, // "KREMLING KOSH ISLES/SNIDE'S"
    0x76, // "TEETERING TURTLE TROUBLE FOREST"
    0x77, // "TEETERING TURTLE TROUBLE CASTLE"
    0x78, // "TEETERING TURTLE TROUBLE SNIDE'S"
    0x79, // "BATTY BARREL BANDIT GALLEON"
    0x7A, // "BATTY BARREL BANDIT ISLES"
    0x7B, // "BATTY BARREL BANDIT SNIDE'S"
    0x7C, // "UNUSED MAD MAZE MAUL 2"
    0x7D, // "UNUSED STASH SNATCH 3"
    0x7E, // "STEALTHY SNOOP AZTEC"
    0x7F, // "UNUSED STEALTHY SNOOP 2"
    0x80, // "UNUSED STEALTHY SNOOP 3"
    0x81, // "MINECART MAYHEM FOREST"
    0x82, // "MINECART MAYHEM CASTLE"
    0x83, // "BUSY BARREL BARRAGE CAVES"
    0x84, // "UNUSED SPLISH-SPLASH SALVAGE"
    0x85, // "SPLISH-SPLASH SALVAGE GALLEON"
    0x86, // "SPEEDY SWING SORTIE FOREST"
    0x87, // "UNUSED SPEEDY SWING SORTIE"
    0x88, // "BEAVER BOTHER CASTLE"
    0x89, // "BEAVER BOTHER SNIDE'S"
    0x8A, // "SEARCHLIGHT SEEK SNIDE'S"
    0x8B, // "SEARCHLIGHT SEEK CAVES"
    0x8C, // "SEARCHLIGHT SEEK CASTLE/ISLES"
    0x8D, // "KRAZY KONG KLAMOUR GALLEON"
    0x8E, // "KRAZY KONG KLAMOUR FOREST/CAVES"
    0x8F, // "KRAZY KONG KLAMOUR SNIDE'S"
    0x90, // "PERIL PATH PANIC FACTORY"
    0x91, // "PERIL PATH PANIC FOREST"
    0x92, // "PERIL PATH PANIC ISLES/SNIDE'S"
    0x93, // "UNUSED PERIL PATH PANIC"
    0x94, // "BIG BUG BASH GALLEON"
    0x95, // "BIG BUG BASH ISLES"
    0x96, // "BIG BUG BASH CASTLE/SNIDE'S"
};

static unsigned char arenas_maps[] = {
    0x35, // "BEAVER BRAWL"
    0x49, // "KRITTER KARNAGE"
    0x9B, // "ARENA AMBUSH"
    0x9C, // "MORE KRITTER KARNAGE"
    0x9D, // "FOREST FRACAS"
    0x9E, // "BISH BASH BRAWL"
    0x9F, // "KAMIKAZE KREMLINGS"
    0xA0, // "PLINTH PANIC"
    0xA1, // "PINNACLE PALAVER"
    0xA2, // "SHOCKWAVE SHOWDOWN"
};

static unsigned char other_maps[] = {
    0x00, // "TEST MAP"
    0x01, // "FUNKY'S STORE"
    //0x02, // "DK ARCADE"
    0x03, // "TINY TEST MAP"
    0x05, // "CRANKY'S LAB"
    // 0x09, // "JETPAC"
    0x0F, // "SNIDE'S HQ"
    0x11, // "TORCH ROOM"
    0x19, // "CANDY'S SHOP"
    // 0x28, // "OPENING LOGOS"
    0x2A, // "TROFF 'N' SCOFF"
    0x32, // "E3 DEMO ROOM"
    0x4C, // "DK RAP"
    // 0x50, // "TITLE SCREEN"
    // 0x51, // "THANKS FOR PLAYING SCREEN"
    0x61, // "K. LUMSY'S PRISON"
    0x6B, // "MULTIPLAYER BATTLE ARENA"
    0x6D, // "NOTHING? (MONKEY SMASH ARENA 1)"
    0x98, // "HIDEOUT HELM (INTRO STORY VERSION)"
    0x99, // "DK ISLES (INTRO STORY VERSION)"
    0xA5, // "DONKEY KONG 64K" // Custom Entry Point
};

typedef struct level_data {
    /* 0x000 */ unsigned char* map_list;
    /* 0x004 */ unsigned char cap;
    /* 0x005 */ unsigned char selected;
    /* 0x006 */ unsigned char pad[2];
} level_data;

static unsigned char selected_map = 0;
static unsigned char selected_map_local = 0;
static unsigned char selected_kong = 0;
static unsigned char selected_level = 0;
static option_sets selected_option = OPTIONSET_LEVEL;
static level_data levels[] = {
    {.map_list=&japes_maps, .cap=sizeof(japes_maps), .selected=0},
    {.map_list=&aztec_maps, .cap=sizeof(aztec_maps), .selected=0},
    {.map_list=&factory_maps, .cap=sizeof(factory_maps), .selected=0},
    {.map_list=&galleon_maps, .cap=sizeof(galleon_maps), .selected=0},
    {.map_list=&fungi_maps, .cap=sizeof(fungi_maps), .selected=0},
    {.map_list=&caves_maps, .cap=sizeof(caves_maps), .selected=0},
    {.map_list=&castle_maps, .cap=sizeof(castle_maps), .selected=0},
    {.map_list=&bonus_maps, .cap=sizeof(bonus_maps), .selected=0},
    {.map_list=&arenas_maps, .cap=sizeof(arenas_maps), .selected=0},
    {.map_list=0, .cap=6, .selected=0},
    {.map_list=&other_maps, .cap=sizeof(other_maps), .selected=0},
};

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

void handleShift(int stickX, unsigned char* option, unsigned char cap) {
    if (stickX < -0x28) {
        if (*option == 0) {
            *option = cap;
        } else {
            *option -= 1;
        }
    } else if (stickX > 0x28) {
        if (*option == cap) {
            *option = 0;
        } else {
            *option += 1;
        }
    }
}

static unsigned char shifting_y = 0;

int* displayMapName(int* dl) {
    selected_map_local = levels[selected_level].selected;
    int stick_y = ControllerInput.stickY;
    if ((stick_y > -0x28) && (stick_y < 0x28)) {
        shifting_y = 0;
    }
    if ((ObjectTimer & 3) == 0) {
        if (selected_option == OPTIONSET_LEVEL) {
            if ((stick_y < -0x28) && (!shifting_y)) {
                selected_option += 1;
                shifting_y = 1;
            } else {
                handleShift(ControllerInput.stickX, &selected_level, 0xA);
            }
        } else if (selected_option == OPTIONSET_MAP) {
            if ((stick_y > 0x28) && (!shifting_y)) {
                selected_option -= 1;
                shifting_y = 1;
            } else if ((stick_y < -0x28) && (!shifting_y)) {
                selected_option += 1;
                shifting_y = 1;
            } else {
                handleShift(ControllerInput.stickX, &selected_map_local, levels[selected_level].cap - 1);
                levels[selected_level].selected = selected_map_local;
            }
        } else if (selected_option == OPTIONSET_KONG) {
            if ((stick_y > 0x28) && (!shifting_y)) {
                selected_option -= 1;
                shifting_y = 1;
            } else {
                handleShift(ControllerInput.stickX, &selected_kong, 4);
            }
        }
    }
    char* mapname = 0;
    if (selected_level != LEVELSET_DKTV) {
        selected_map = levels[selected_level].map_list[selected_map_local];
        mapname = map_names[selected_map];
    } else {
        mapname = dktv_demo_names[selected_map_local];
    }
    // Clamp
    if (selected_map > 0xA5) {
        selected_map = 0;
    }
    if (selected_kong > 4) {
        selected_kong = 0;
    }
    if (selected_level != LEVELSET_DKTV) {
        for (int i = 0; i < 3; i++) {
            DemoMaps[i].map = selected_map;
            DemoMaps[i].kong = selected_kong;
        }
    }
    int center = 0x280;
    char* names[3] = {
        level_subsets[selected_level],
        mapname,
        kong_names[selected_kong],
    };
    int y_pos = *(char*)(0x806F1CE8) * 0x278;
    int light_color = 0xFFFFFFFF;
    int fade_color = 0x808080FF;
    *(int*)(dl++) = 0xDA380007;
    *(int*)(dl++) = 0x020000C0;
    *(int*)(dl++) = 0xFC119623;
    *(int*)(dl++) = 0xFF2FFFFF;
    for (int i = 0; i < 3; i++) {
        int local_color = fade_color;
        if (selected_option == i) {
            local_color = light_color;
        }
        *(int*)(dl++) = 0xFA000000;
        *(int*)(dl++) = local_color;
        dl = displayText(dl, 7, center - (getStringWidth(7, names[i]) << 1), y_pos + (60.0f * i), names[i], 4);
    }
    return dl;
}

void warpHandler(void) {
    if (selected_level == LEVELSET_DKTV) {
        warpToDKTV(levels[selected_level].selected);
    } else {
        setNextDemoMap(0);
    }
}

void warpToDK64K(void) {
    if (NextMap == 0xA5) {
        CutsceneActive = 2;
        NextMap = 2;
    }
    prepareHeap(1);
}

void handleDK64KOverlay(int unk0, int unk1, int unk2) {
    if (CutsceneActive == 2) {
        unk1 = 11;
    }
    heap_init(unk0, unk1, unk2);
}