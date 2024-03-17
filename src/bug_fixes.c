#include "../include/common.h"

// JAPES DIDDY CRASH

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