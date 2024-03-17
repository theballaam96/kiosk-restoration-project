#include "../include/common.h"

void cFuncLoop(void) {
	/*
		This function is run every frame. Place c code which you are wanting to be run every frame
	*/
	initHack(); // Initialize hack
	tagAnywhere(); // Tag Anywhere every frame functions
	if (ObjectTimer < 5) {
		if (CurrentMap == 0x1B) {
			fixEnemyCarProperties();
		}
	}



	// if (grab_lock_timer >= 0) {
	// 	grab_lock_timer += 1;
	// 	if (grab_lock_timer > 10) {
	// 		grab_lock_timer = -1;
	// 	}
	// }
	// if (tag_locked) {
	// 	tag_locked = 0;
	// }
}
