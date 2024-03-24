#include "../include/common.h"

static char debug_enabled = 0;
static char debug_shown = 0;

static unsigned char selected_cutscene = 0;
static unsigned char selected_bank = 0;
static unsigned char selected_option = 0;

int* drawPixelText(int* dl, int x, int y, char* str, int red, int green, int blue, int alpha) {
	*(unsigned int*)(dl++) = 0xE7000000;
    *(unsigned int*)(dl++) = 0x00000000;
    *(unsigned int*)(dl++) = 0xE3000A01;
    *(unsigned int*)(dl++) = 0x00000000;
    *(unsigned int*)(dl++) = 0xD9000000;
    *(unsigned int*)(dl++) = 0x00000000;
    *(unsigned int*)(dl++) = 0xD9FFFFFF;
    *(unsigned int*)(dl++) = 0x00200004;
    gDPSetPrimColor(dl, 0, 0, red, green, blue, alpha);
    dl += 2;
    *(unsigned int*)(dl++) = 0xFC119623;
    *(unsigned int*)(dl++) = 0xFF2FFFFF;
    *(unsigned int*)(dl++) = 0xE200001C;
    *(unsigned int*)(dl++) = 0x00504240;
    dl = drawText(dl, 3, x, y, str);
	return dl;
};

int* drawPixelTextContainer(int* dl, int x, int y, char* str, int red, int green, int blue, int alpha, int offset) {
	if (offset) {
		dl = drawPixelText(dl,x-offset,y+offset,str,0,0,0,alpha);
	}
	dl = drawPixelText(dl,x,y,str,red,green,blue,alpha);
	return dl;
}

void changeOption(unsigned char* value, int cap) {
    if (NewlyPressedInput.d_left) {
        if (*value == 0) {
            *value = cap;
        }
        *value -= 1;
    } else if (NewlyPressedInput.d_right) {
        if (*value == (cap - 1)) {
            *value = 0;
        } else {
            *value += 1;
        }
    }
}

#define OPTION_CAP 2

void toggleDebugShown(void) {
    if (debug_shown) {
        if (selected_option == 0) {
            changeOption(&selected_cutscene, CutsceneBanks[selected_bank].count);
        } else if (selected_option == 1) {
            changeOption(&selected_bank, 2);
        }
        if (NewlyPressedInput.d_down) {
            selected_option += 1;
            if (selected_option > (OPTION_CAP - 1)) {
                selected_option = 0;
            }
        } else if (NewlyPressedInput.d_up) {
            if (selected_option == 0) {
                selected_option = OPTION_CAP - 1;
            } else {
                selected_option -= 1;
            }
        }
        if (selected_cutscene >= CutsceneBanks[selected_bank].count) {
            selected_cutscene = CutsceneBanks[selected_bank].count - 1; // Clamp
        }
        if ((NewlyPressedInput.l) && (!ControllerInput.Buttons.r)) {
            if (CutsceneBanks[selected_bank].count > 0) {
                int bitfield = 1;
                if (selected_bank == 1) {
                    bitfield = 5;
                }
                playCutscene((void*)0, selected_cutscene, bitfield);
            }
        }
    }
    if ((ControllerInput.Buttons.r) && (NewlyPressedInput.l)) {
        debug_shown = 1 ^ debug_shown;
    }
}

static const char displayed_text[0x20];

int* displayOptionHandler(int* dl, int option_index, char* str) {
    int red = 0xFF;
    int green = 0xFF;
    int blue = 0xFF;
    if (option_index == selected_option) {
        red = 0xFF;
        green = 0xD7;
        blue = 0;
    }
    return drawPixelTextContainer(dl, 25, 25 + (option_index * 13), str, red, green, blue, 0xFF, 2);
}

int* displayListWrapper(int* dl) {
    dl = SecuritySomething(dl);
    // Handle Debug Shown
    toggleDebugShown();
    if ((!debug_enabled) || (!debug_shown) || (Gamemode != 6) || (CutsceneActive == 1)) {
        if (Gamemode != 6) {
            debug_shown = 0;
        }
        return dl;
    }
    int start_x = 25;
    int start_y = 25;
    int y_delta = 13;
    // Render Stuff
    if (CutsceneBanks[selected_bank].count == 0) {
        dl = displayOptionHandler(dl, 0, "NO CUTSCENES IN BANK");
    } else {
        dk_strFormat(displayed_text, "PLAY CUTSCENE %d OF %d", selected_cutscene, CutsceneBanks[selected_bank].count);
        dl = displayOptionHandler(dl, 0, (char*)displayed_text);
    }
    if (selected_bank == 0) {
        dl = displayOptionHandler(dl, 1, "BANK: MAP");
    } else {
        dl = displayOptionHandler(dl, 1, "BANK: GLOBAL");
    }
    return dl;
}

static char z_pressed = 0;

void toggleDebugEnabled(void) {
    if (ControllerInput.Buttons.z) {
        if (!z_pressed) {
            debug_enabled = 1 ^ debug_enabled;
        }
        z_pressed = 1;
    } else {
        z_pressed = 0;
    }
}

int debugEnabled(void) {
    return debug_enabled;
}

int debugOpen(void) {
    return debug_shown;
}