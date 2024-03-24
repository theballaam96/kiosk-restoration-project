#include "vars.h"

extern void setPermanentFlag(s16 flagIndex);
extern void setGlobalFlag(s16 flagIndex);
extern void setTemporaryFlag(s16 flagIndex);
extern void* findActorWithType(s32 search_actor_type);

// Stuff to do with Tag Anywhere and the stack trace
extern void tagAnywhereBunch(int player, int obj, int player_index);
extern void tagAnywhereAmmo(int player, int obj, int is_homing);
extern void tagAnywhereInit(int is_homing, int model2_id, int obj);
extern void initHack(void);
extern void tagAnywhere(void);
extern void initStackTrace(void);
extern void handleGrabbingLock(void* player, int player_index, int allow_vines);
extern void handleActionSet(int action, void* actor, int player_index);

// Misc
extern int* displayMapName(int* dl);
extern void createCrashThread(void);
extern void fixEnemyCarProperties(void);
extern void initPause(void);
extern void addBannerText(int map_id, char* str);
extern void warpToDK64K(void);
extern void handleDK64KOverlay(int unk0, int unk1, int unk2);
extern void initDKTV(void);
extern void warpToDKTV(int index);
extern void loadDKTVData(void);
extern void warpHandler(void);

extern int* displayListWrapper(int* dl);
extern void toggleDebugEnabled(void);
extern int debugEnabled(void);
extern int debugOpen(void);

extern const s16 kong_flags[5];
extern char tag_locked;
extern char grab_lock_timer;
extern stack_trace_log stack_trace_addresses[18];