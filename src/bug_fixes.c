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