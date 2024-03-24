#include "../include/common.h"

static s8 initialized = 0;

void giveAllMoves(void) {
    wipeMemory(&PlayerItems->kongs[0].moves, sizeof(PlayerInventory));
    for (int i = 0; i < 5; i++) {
        PlayerItems->kongs[i].moves = 3;
        PlayerItems->kongs[i].slam = 3;
        PlayerItems->kongs[i].weapon_bitfield = 7;
        PlayerItems->kongs[i].ammo_belt = 2;
        PlayerItems->kongs[i].instrument_bitfield = 15;
        PlayerItems->kongs[i].coins = 50;
    }
    PlayerItems->silver_balloons = 9;
    PlayerItems->normal_ammo = 100;
    PlayerItems->oranges = 20;
    PlayerItems->film = 10;
    PlayerItems->crystal_frames = 30000;
    PlayerItems->melons = 12;
    PlayerItems->health_0 = 3;
    PlayerItems->unk_1D0 = 0;
}

void initHack(void) {
    /**
     * @brief Everything you expect to run upon booting your hack up, and nowhere else.
     */
    if (!initialized) {
        // Give all moves
        giveAllMoves();
        writeFunction(0x80590A08, &giveAllMoves);
        writeFunction(0x806B5FD4, &giveAllMoves);
        writeFunction(0x806B6070, &giveAllMoves);
        writeFunction(0x806B5A0C, &displayMapName);
        writeFunction(0x806B5A74, &displayMapName);
        writeFunction(0x805930B8, &warpToDK64K);
        writeFunction(0x80590650, &handleDK64KOverlay);
        writeFunction(0x805933BC, &initDKTV);
        writeFunction(0x80593248, &loadDKTVData);
        writeFunction(0x806B4F3C, &warpHandler);
        // Bug fixes
        loadSingularHook(0x806D4DD8, &fix_diddy_japes_crash);
        loadSingularHook(0x805942EC, &fix_crossmap_crash);
        for (int i = 0; i < 139; i++) {
            int address = 0x806FC41C + (i * 0x44);
            int func = *(int*)(address);
            if (func == 0x80684004) {
                *(int*)(address) = (int)&initPause;
            }
        }
        // Debug
        writeFunction(0x80592A3C, &displayListWrapper);
        // Banner Text
        // addBannerText(0x2A, "LEVEL GUARDIAN");
        
        // Enable stack trace upon crash
        // *(s8 *)(0x807563B4) = 1;
        // *(s32 *)(0x80731F78) = 0;
        //initStackTrace();
        // // TAG ANYWHERE STUFF
        // // START
        // *(int*)(0x806F6D94) = 0; // Prevent delayed collection
        // // Standard Ammo
        // *(short*)(0x806F5B68) = 0x1000;
        // *(int*)(0x806F5BE8) = 0x0C000000 | (((int)&tagAnywhereAmmo & 0xFFFFFF) >> 2);
        // // Bunch
        // *(short*)(0x806F59A8) = 0x1000;
        // *(int*)(0x806F5A08) = 0x0C000000 | (((int)&tagAnywhereBunch & 0xFFFFFF) >> 2);
        // *(int*)(0x806F6CAC) = 0x9204001A; // LBU $a0, 0x1A ($s0)
        // *(int*)(0x806F6CB0) = 0x86060002; // LH $a2, 0x2 ($s0)
        // *(int*)(0x806F6CB4) = 0x0C000000 | (((int)&tagAnywhereInit & 0xFFFFFF) >> 2);
        // *(int*)(0x806F53AC) = 0; // Prevent LZ case
        // // Minor Bug Fixes
        // grab_lock_timer = -1;
        // tag_locked = 0;
        // writeFunction(0x8072F1E8, &handleGrabbingLock);
        // writeFunction(0x8072F458, &handleActionSet); // Actor grabbables
        // writeFunction(0x8072F46C, &handleActionSet); // Model 2 grabbables
        // writeFunction(0x806CFC64, &handleActionSet); // Ledge Grabbing
        // FINISH
        initialized = 1;
    }
}