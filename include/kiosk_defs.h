extern void wipeMemory(void* start, int size);
extern void tagKong(int kong);
extern void cancelMusic(int song, int unk0);
extern void clearTagSlide(void* actor);
extern void playAnimation(void* actor, int local_animation);
extern void handleAnimation(void* actor);
extern int getWorld(int map);
extern int* displayText(int* dl, int style, int x, int y, char* str, int params);
extern int getStringWidth(int style, char* str);

extern void __osSetEventMesg(int id, void* tail, int unk0);
extern int __osRecvMesg(void* tail, void* unk0, int unk1);
extern void __osViBlack(int unk0);
extern int __osGetFpcCsr(void);
extern int __osSetFpcCsr(int val);
extern void __osCreateMesgQueue(void* unk0, void* unk1, int unk2);
extern void __osCreateThread(void* unk0, int id, void* function, int unk1, void* unk2, int priority);
extern void __osStartThread(void* unk0);
extern void* getRegData(void);
extern void prepareHeap(int unk0);
extern void heap_init(int unk0, int unk1, int unk2);

extern PlayerInventory PlayerItems[4];
extern PlayerData* Player;
extern SwapStruct* SwapObject;
extern float LZFadeoutProgress;
extern unsigned char CutsceneActive;
extern unsigned char ModelTwoTouchCount;
extern int CurrentMap;
extern unsigned char MapState;
extern short LoadedActorCount;
extern LoadedActor LoadedActorArray[64];
extern unsigned char TBVoidByte;
extern unsigned char Character;
extern hudData* HUD;
extern Controller ControllerInput;
extern int ObjectTimer;
extern short DKTVTimer;
extern DemoStruct DemoMaps[3];
extern short* FramebufferPointer[2];
extern char_spawner_flag_mapping CharSpawnerFlagMapping[11];
extern spawner_master_data* CharSpawnerMasterData;
extern char Gamemode;
extern unsigned char BannerTextEnabled[28];
extern char* BannerStrings[200];
extern int NextMap;