#include "../include/common.h"

// JAPES DIDDY CRASH
/*
- Game doesn't write the index of the found item anywhere, so it's left uninitialized causing invalid memory reads
- Whilst this was originally intended as a fix for Japes Diddy, this also applies to other things, like the caged Llama or Chunky.
- Fixing it to be like the final fixes this and makes Japes/Aztec/Factory fully traversable
*/

int getSpawnerFlag_fixed(int target_map, int target_id, int* counter_write) {
    *counter_write = 0;
    for (int i = 0; i < 11; i++) {
        *counter_write = i;
        if (target_map == CharSpawnerFlagMapping[i].map) {
            if (target_id == CharSpawnerFlagMapping[i].spawner_id) {
                return CharSpawnerFlagMapping[i].flag;
            }
        }
    }
    return -1;
}

// FACTORY CAR RACE
/*
- Enemy car deloads if the player goes too fast
- TNT Minecart needs to find the enemy car to help with pathing, but if the enemy car is deloaded, it won't find anything
- It then references a null pointer which means crash
- To fix, set the enemy car prop bitfield to 0x402C
*/

void fixEnemyCarProperties(void) {
    if (!CharSpawnerMasterData) {
        return;
    }
    if (!CharSpawnerMasterData->spawners) {
        return;
    }
    for (int i = 0; i < CharSpawnerMasterData->count; i++) {
        if (CharSpawnerMasterData->spawners[i].trigger == 1) {
            CharSpawnerMasterData->spawners[i].properties = 0x402C;
        }
    }
}

// Pause
/*
- The game has junked the init pause function
- Adding this back in for ease of use
*/

void initPause(void) {
    int input_bitfield = *(short*)(0x807B6DCA);
    if ((input_bitfield & 0x1000) == 0) {
        return;
    }
    if (CutsceneActive == 1) {
        return;
    }
    if (LZFadeoutProgress != 0.0f) {
        return;
    }
    if (Gamemode != 6) {
        return;
    }
    TBVoidByte |= 1;
}

// Map Banner Text
/*
- Various bits of banner text is present in the E3 demo, and some remain in Kiosk
- They've mostly been stripped out
*/
void addBannerText(int map_id, char* str) {
    int offset = map_id >> 3;
    int shift = map_id & 7;
    BannerTextEnabled[offset] |= (1 << shift);
    BannerStrings[map_id] = str;
}

// Load in DKTV
/*
- DKTV Content is still present in Kiosk, but remains uncalled.
- All the following functions allows it to be loaded back up again, but will only be called when the user defines they want DKTV in
*/

int warped_dktv = 0;

void initDKTV(void) {
    if (Gamemode == 4) {
        int timer = loadDKTVContainer(Player);
        int fadeout_timer = 0xFFF;
        if (timer < fadeout_timer) {
            fadeout_timer = timer;
        }
        buttonsRequired = 0x1000;
    }
    showerWithCoins();
}

void GetNextDKTVMap(void) {
    InitMapChange(DKTVData.map, DKTVData.exit);
}

void loadDKTVData(void) {
    if (NextGamemode == 4) {
        loadDKTVFromROM(warped_dktv);
        Character = DKTVData.kong;
    }
}

void warpToDKTV(int index) {
    NextGamemode = 4;
    warped_dktv = index;
    loadDKTVData();
    GetNextDKTVMap();
}