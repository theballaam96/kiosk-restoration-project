typedef struct KongInventory {
    /* 0x000 */ unsigned char moves;
    /* 0x001 */ unsigned char slam;
    /* 0x002 */ unsigned char weapon_bitfield;
    /* 0x003 */ unsigned char ammo_belt;
    /* 0x004 */ unsigned char instrument_bitfield;
    /* 0x005 */ unsigned char unk_5;
    /* 0x006 */ unsigned short coins;
    /* 0x008 */ unsigned short instrument_energy;
    /* 0x00A */ short cb_count[12];
    /* 0x022 */ short cb_tns_count[14];
    /* 0x03E */ short gb_count[14];
} KongInventory;

typedef struct PlayerInventory {
    /* 0x000 */ KongInventory kongs[5];
    /* 0x1C2 */ short normal_ammo;
    /* 0x1C4 */ short homing_ammo;
    /* 0x1C6 */ short oranges;
    /* 0x1C8 */ short crystal_frames;
    /* 0x1CA */ short film;
    /* 0x1CC */ char silver_balloons;
    /* 0x1CD */ char health;
    /* 0x1CE */ char melons;
    /* 0x1CF */ char health_0; // Multiplayer?
    /* 0x1D0 */ char unk_1D0;
    /* 0x1D1 */ char unk_1D1[0x9];
} PlayerInventory;

typedef struct map_bitfield {
	unsigned char test_map : 1;
	unsigned char funkys_store : 1;
	unsigned char dk_arcade : 1;
	unsigned char k_rool_barrel_lankys_maze : 1;
	unsigned char jungle_japes_mountain : 1;
	unsigned char crankys_lab : 1;
	unsigned char jungle_japes_minecart : 1;
	unsigned char jungle_japes : 1;
	unsigned char jungle_japes_army_dillo : 1;
	unsigned char jetpac : 1;
	unsigned char kremling_kosh_very_easy : 1;
	unsigned char stealthy_snoop_normal_no_logo : 1;
	unsigned char jungle_japes_shell : 1;
	unsigned char jungle_japes_lankys_cave : 1;
	unsigned char angry_aztec_beetle_race : 1;
	unsigned char snides_hq : 1;
	unsigned char angry_aztec_tinys_temple : 1;
	unsigned char hideout_helm : 1;
	unsigned char teetering_turtle_trouble_very_easy : 1;
	unsigned char angry_aztec_five_door_temple_dk : 1;
	unsigned char angry_aztec_llama_temple : 1;
	unsigned char angry_aztec_five_door_temple_diddy : 1;
	unsigned char angry_aztec_five_door_temple_tiny : 1;
	unsigned char angry_aztec_five_door_temple_lanky : 1;
	unsigned char angry_aztec_five_door_temple_chunky : 1;
	unsigned char candys_music_shop : 1;
	unsigned char frantic_factory : 1;
	unsigned char frantic_factory_car_race : 1;
	unsigned char hideout_helm_level_intros_game_over : 1;
	unsigned char frantic_factory_power_shed : 1;
	unsigned char gloomy_galleon : 1;
	unsigned char gloomy_galleon_k_rools_ship : 1;
	unsigned char batty_barrel_bandit_very_easy : 1;
	unsigned char jungle_japes_chunkys_cave : 1;
	unsigned char dk_isles_overworld : 1;
	unsigned char k_rool_barrel_dks_target_game : 1;
	unsigned char frantic_factory_crusher_room : 1;
	unsigned char jungle_japes_barrel_blast : 1;
	unsigned char angry_aztec : 1;
	unsigned char gloomy_galleon_seal_race : 1;
	unsigned char nintendo_logo : 1;
	unsigned char angry_aztec_barrel_blast : 1;
	unsigned char troff_n_scoff : 1;
	unsigned char gloomy_galleon_shipwreck_diddy_lanky_chunky : 1;
	unsigned char gloomy_galleon_treasure_chest : 1;
	unsigned char gloomy_galleon_mermaid : 1;
	unsigned char gloomy_galleon_shipwreck_dk_tiny : 1;
	unsigned char gloomy_galleon_shipwreck_lanky_tiny : 1;
	unsigned char fungi_forest : 1;
	unsigned char gloomy_galleon_lighthouse : 1;
	unsigned char k_rool_barrel_tinys_mushroom_game : 1;
	unsigned char gloomy_galleon_mechanical_fish : 1;
	unsigned char fungi_forest_ant_hill : 1;
	unsigned char battle_arena_beaver_brawl : 1;
	unsigned char gloomy_galleon_barrel_blast : 1;
	unsigned char fungi_forest_minecart : 1;
	unsigned char fungi_forest_diddys_barn : 1;
	unsigned char fungi_forest_diddys_attic : 1;
	unsigned char fungi_forest_lankys_attic : 1;
	unsigned char fungi_forest_dks_barn : 1;
	unsigned char fungi_forest_spider : 1;
	unsigned char fungi_forest_front_part_of_mill : 1;
	unsigned char fungi_forest_rear_part_of_mill : 1;
	unsigned char fungi_forest_mushroom_puzzle : 1;
	unsigned char fungi_forest_giant_mushroom : 1;
	unsigned char stealthy_snoop_normal : 1;
	unsigned char mad_maze_maul_hard : 1;
	unsigned char stash_snatch_normal : 1;
	unsigned char mad_maze_maul_easy : 1;
	unsigned char mad_maze_maul_normal : 1;
	unsigned char fungi_forest_mushroom_leap : 1;
	unsigned char fungi_forest_shooting_game : 1;
	unsigned char crystal_caves : 1;
	unsigned char battle_arena_kritter_karnage : 1;
	unsigned char stash_snatch_easy : 1;
	unsigned char stash_snatch_hard : 1;
	unsigned char dk_rap : 1;
	unsigned char minecart_mayhem_easy : 1;
	unsigned char busy_barrel_barrage_easy : 1;
	unsigned char busy_barrel_barrage_normal : 1;
	unsigned char main_menu : 1;
	unsigned char title_screen_not_for_resale_version : 1;
	unsigned char crystal_caves_beetle_race : 1;
	unsigned char fungi_forest_dogadon : 1;
	unsigned char crystal_caves_igloo_tiny : 1;
	unsigned char crystal_caves_igloo_lanky : 1;
	unsigned char crystal_caves_igloo_dk : 1;
	unsigned char creepy_castle : 1;
	unsigned char creepy_castle_ballroom : 1;
	unsigned char crystal_caves_rotating_room : 1;
	unsigned char crystal_caves_shack_chunky : 1;
	unsigned char crystal_caves_shack_dk : 1;
	unsigned char crystal_caves_shack_diddy_middle_part : 1;
	unsigned char crystal_caves_shack_tiny : 1;
	unsigned char crystal_caves_lankys_hut : 1;
	unsigned char crystal_caves_igloo_chunky : 1;
	unsigned char splish_splash_salvage_normal : 1;
	unsigned char k_lumsy : 1;
	unsigned char crystal_caves_ice_castle : 1;
	unsigned char speedy_swing_sortie_easy : 1;
	unsigned char crystal_caves_igloo_diddy : 1;
	unsigned char krazy_kong_klamour_easy : 1;
	unsigned char big_bug_bash_very_easy : 1;
	unsigned char searchlight_seek_very_easy : 1;
	unsigned char beaver_bother_easy : 1;
	unsigned char creepy_castle_tower : 1;
	unsigned char creepy_castle_minecart : 1;
	unsigned char kong_battle_battle_arena : 1;
	unsigned char creepy_castle_crypt_lanky_tiny : 1;
	unsigned char kong_battle_arena_1 : 1;
	unsigned char frantic_factory_barrel_blast : 1;
	unsigned char gloomy_galleon_pufftoss : 1;
	unsigned char creepy_castle_crypt_dk_diddy_chunky : 1;
	unsigned char creepy_castle_museum : 1;
	unsigned char creepy_castle_library : 1;
	unsigned char kremling_kosh_easy : 1;
	unsigned char kremling_kosh_normal : 1;
	unsigned char kremling_kosh_hard : 1;
	unsigned char teetering_turtle_trouble_easy : 1;
	unsigned char teetering_turtle_trouble_normal : 1;
	unsigned char teetering_turtle_trouble_hard : 1;
	unsigned char batty_barrel_bandit_easy : 1;
	unsigned char batty_barrel_bandit_normal : 1;
	unsigned char batty_barrel_bandit_hard : 1;
	unsigned char mad_maze_maul_insane : 1;
	unsigned char stash_snatch_insane : 1;
	unsigned char stealthy_snoop_very_easy : 1;
	unsigned char stealthy_snoop_easy : 1;
	unsigned char stealthy_snoop_hard : 1;
	unsigned char minecart_mayhem_normal : 1;
	unsigned char minecart_mayhem_hard : 1;
	unsigned char busy_barrel_barrage_hard : 1;
	unsigned char splish_splash_salvage_hard : 1;
	unsigned char splish_splash_salvage_easy : 1;
	unsigned char speedy_swing_sortie_normal : 1;
	unsigned char speedy_swing_sortie_hard : 1;
	unsigned char beaver_bother_normal : 1;
	unsigned char beaver_bother_hard : 1;
	unsigned char searchlight_seek_easy : 1;
	unsigned char searchlight_seek_normal : 1;
	unsigned char searchlight_seek_hard : 1;
	unsigned char krazy_kong_klamour_normal : 1;
	unsigned char krazy_kong_klamour_hard : 1;
	unsigned char krazy_kong_klamour_insane : 1;
	unsigned char peril_path_panic_very_easy : 1;
	unsigned char peril_path_panic_easy : 1;
	unsigned char peril_path_panic_normal : 1;
	unsigned char peril_path_panic_hard : 1;
	unsigned char big_bug_bash_easy : 1;
	unsigned char big_bug_bash_normal : 1;
	unsigned char big_bug_bash_hard : 1;
	unsigned char creepy_castle_dungeon : 1;
	unsigned char hideout_helm_intro_story : 1;
	unsigned char dk_isles_dk_theatre : 1;
	unsigned char frantic_factory_mad_jack : 1;
	unsigned char battle_arena_arena_ambush : 1;
	unsigned char battle_arena_more_kritter_karnage : 1;
	unsigned char battle_arena_forest_fracas : 1;
	unsigned char battle_arena_bish_bash_brawl : 1;
	unsigned char battle_arena_kamikaze_kremlings : 1;
	unsigned char battle_arena_plinth_panic : 1;
	unsigned char battle_arena_pinnacle_palaver : 1;
	unsigned char battle_arena_shockwave_showdown : 1;
	unsigned char creepy_castle_basement : 1;
	unsigned char creepy_castle_tree : 1;
	unsigned char k_rool_barrel_diddys_kremling_game : 1;
	unsigned char creepy_castle_chunkys_toolshed : 1;
	unsigned char creepy_castle_trash_can : 1;
	unsigned char creepy_castle_greenhouse : 1;
	unsigned char jungle_japes_lobby : 1;
	unsigned char hideout_helm_lobby : 1;
	unsigned char dks_house : 1;
	unsigned char rock_intro_story : 1;
	unsigned char angry_aztec_lobby : 1;
	unsigned char gloomy_galleon_lobby : 1;
	unsigned char frantic_factory_lobby : 1;
	unsigned char training_grounds : 1;
	unsigned char dive_barrel : 1;
	unsigned char fungi_forest_lobby : 1;
	unsigned char gloomy_galleon_submarine : 1;
	unsigned char orange_barrel : 1;
	unsigned char barrel_barrel : 1;
	unsigned char vine_barrel : 1;
	unsigned char creepy_castle_crypt : 1;
	unsigned char enguarde_arena : 1;
	unsigned char creepy_castle_car_race : 1;
	unsigned char crystal_caves_barrel_blast : 1;
	unsigned char creepy_castle_barrel_blast : 1;
	unsigned char fungi_forest_barrel_blast : 1;
	unsigned char fairy_island : 1;
	unsigned char kong_battle_arena_2 : 1;
	unsigned char rambi_arena : 1;
	unsigned char kong_battle_arena_3 : 1;
	unsigned char creepy_castle_lobby : 1;
	unsigned char crystal_caves_lobby : 1;
	unsigned char dk_isles_snides_room : 1;
	unsigned char crystal_caves_army_dillo : 1;
	unsigned char angry_aztec_dogadon : 1;
	unsigned char training_grounds_end_sequence : 1;
	unsigned char creepy_castle_king_kut_out : 1;
	unsigned char crystal_caves_shack_diddy_upper_part : 1;
	unsigned char k_rool_barrel_diddys_rocketbarrel_game : 1;
	unsigned char k_rool_barrel_lankys_shooting_game : 1;
	unsigned char k_rool_fight_dk_phase : 1;
	unsigned char k_rool_fight_diddy_phase : 1;
	unsigned char k_rool_fight_lanky_phase : 1;
	unsigned char k_rool_fight_tiny_phase : 1;
	unsigned char k_rool_fight_chunky_phase : 1;
	unsigned char bloopers_ending : 1;
	unsigned char k_rool_barrel_chunkys_hidden_kremling_game : 1;
	unsigned char k_rool_barrel_tinys_pony_tail_twirl_game : 1;
	unsigned char k_rool_barrel_chunkys_shooting_game : 1;
	unsigned char k_rool_barrel_dks_rambi_game : 1;
	unsigned char k_lumsy_ending : 1;
	unsigned char k_rools_shoe : 1;
	unsigned char k_rools_arena : 1;
} map_bitfield;

typedef struct movement_bitfield {
	unsigned char null_state : 1;
	unsigned char idle_enemy : 1;
	unsigned char first_person_camera : 1;
	unsigned char first_person_camera_water : 1;
	unsigned char fairy_camera : 1;
	unsigned char fairy_camera_water : 1;
	unsigned char locked_bonus_barrel_0x6 : 1;
	unsigned char minecart_idle : 1;
	unsigned char minecart_crouch : 1;
	unsigned char minecart_jump : 1;
	unsigned char minecart_left : 1;
	unsigned char minecart_right : 1;
	unsigned char idle : 1;
	unsigned char walking : 1;
	unsigned char skidding : 1;
	unsigned char sliding_beetle_race : 1;
	unsigned char sliding_beetle_race_left : 1;
	unsigned char sliding_beetle_race_right : 1;
	unsigned char sliding_beetle_race_forward : 1;
	unsigned char sliding_beetle_race_back : 1;
	unsigned char jumping_beetle_race : 1;
	unsigned char slipping : 1;
	unsigned char slipping_helm_slope : 1;
	unsigned char jumping : 1;
	unsigned char baboon_blast_pad : 1;
	unsigned char bouncing_mushroom : 1;
	unsigned char double_jump : 1;
	unsigned char simian_spring : 1;
	unsigned char simian_slam : 1;
	unsigned char long_jumping : 1;
	unsigned char falling : 1;
	unsigned char falling_gun : 1;
	unsigned char falling_or_splat : 1;
	unsigned char falling_beetle_race : 1;
	unsigned char pony_tail_twirl : 1;
	unsigned char attacking_enemy : 1;
	unsigned char primate_punch : 1;
	unsigned char attacking_enemy_0x25 : 1;
	unsigned char ground_attack : 1;
	unsigned char attacking_enemy_0x27 : 1;
	unsigned char ground_attack_final : 1;
	unsigned char moving_ground_attack : 1;
	unsigned char aerial_attack : 1;
	unsigned char rolling : 1;
	unsigned char throwing_orange : 1;
	unsigned char shockwave : 1;
	unsigned char chimpy_charge : 1;
	unsigned char charging_rambi : 1;
	unsigned char bouncing : 1;
	unsigned char damaged : 1;
	unsigned char stunlocked_kasplat : 1;
	unsigned char damaged_mad_jack : 1;
	unsigned char unknown_0x34 : 1;
	unsigned char damaged_klump_knockback : 1;
	unsigned char death : 1;
	unsigned char damaged_underwater : 1;
	unsigned char damaged_vehicle : 1;
	unsigned char shrinking : 1;
	unsigned char unknown_0x3a : 1;
	unsigned char death_dogadon : 1;
	unsigned char crouching : 1;
	unsigned char uncrouching : 1;
	unsigned char backflip : 1;
	unsigned char entering_orangstand : 1;
	unsigned char orangstand : 1;
	unsigned char jumping_orangstand : 1;
	unsigned char barrel_tag_barrel : 1;
	unsigned char barrel_underwater : 1;
	unsigned char baboon_blast_shot : 1;
	unsigned char cannon_shot : 1;
	unsigned char pushing_object : 1;
	unsigned char picking_up_object : 1;
	unsigned char idle_carrying_object : 1;
	unsigned char walking_carrying_object : 1;
	unsigned char dropping_object : 1;
	unsigned char throwing_object : 1;
	unsigned char jumping_carrying_object : 1;
	unsigned char throwing_object_air : 1;
	unsigned char surface_swimming : 1;
	unsigned char underwater : 1;
	unsigned char leaving_water : 1;
	unsigned char jumping_water : 1;
	unsigned char bananaporter : 1;
	unsigned char monkeyport : 1;
	unsigned char bananaport_multiplayer : 1;
	unsigned char unknown_0x55 : 1;
	unsigned char locked_funky_and_candy : 1;
	unsigned char swinging_on_vine : 1;
	unsigned char leaving_vine : 1;
	unsigned char climbing_tree : 1;
	unsigned char leaving_tree : 1;
	unsigned char grabbed_ledge : 1;
	unsigned char pulling_up_on_ledge : 1;
	unsigned char idle_gun : 1;
	unsigned char walking_gun : 1;
	unsigned char putting_away_gun : 1;
	unsigned char pulling_out_gun : 1;
	unsigned char jumping_gun : 1;
	unsigned char aiming_gun : 1;
	unsigned char rocketbarrel : 1;
	unsigned char taking_photo : 1;
	unsigned char taking_photo_underwater : 1;
	unsigned char damaged_tnt_barrels : 1;
	unsigned char instrument : 1;
	unsigned char unknown_0x68 : 1;
	unsigned char car_race : 1;
	unsigned char learning_gun : 1;
	unsigned char locked_bonus_barrel_0x6b : 1;
	unsigned char feeding_tns : 1;
	unsigned char boat : 1;
	unsigned char baboon_balloon : 1;
	unsigned char updraft : 1;
	unsigned char gb_dance : 1;
	unsigned char key_dance : 1;
	unsigned char crown_dance : 1;
	unsigned char loss_dance : 1;
	unsigned char victory_dance : 1;
	unsigned char vehicle_castle_car_race : 1;
	unsigned char entering_battle_crown : 1;
	unsigned char locked_cutscenes : 1;
	unsigned char gorilla_grab : 1;
	unsigned char learning_move : 1;
	unsigned char locked_car_race_loss : 1;
	unsigned char locked_beetle_race_loss : 1;
	unsigned char trapped : 1;
	unsigned char klaptrap_kong : 1;
	unsigned char surface_swimming_enguarde : 1;
	unsigned char underwater_enguarde : 1;
	unsigned char attacking_enguarde_surface : 1;
	unsigned char attacking_enguarde : 1;
	unsigned char leaving_water_enguarde : 1;
	unsigned char fairy_refill : 1;
	unsigned char unknown_0x84 : 1;
	unsigned char main_menu : 1;
	unsigned char entering_main_menu : 1;
	unsigned char entering_portal : 1;
	unsigned char exiting_portal : 1;
} movement_bitfield;

typedef struct ActorData {
    /* 0x000 */ char unk_00[0x58];
    /* 0x058 */ int actorType;
    /* 0x05C */ char unk_5C[0x144 - 0x5C];
    /* 0x144 */ unsigned char control_state;
} ActorData;

typedef struct PlayerData {
    /* 0x000 */ char unk_00[0x60];
    /* 0x060 */ int obj_props_bitfield;
    /* 0x064 */ char unk_64[0x7C - 0x64];
    /* 0x07C */ float xPos;
    /* 0x080 */ float yPos;
    /* 0x084 */ float zPos;
    /* 0x088 */ char unk_88[0xB8 - 0x88];
    /* 0x0B8 */ float yVelocity;
    /* 0x0BC */ char unk_BC[0x12C - 0xBC];
    /* 0x12C */ void* collision_queue_pointer;
    /* 0x130 */ char unk_130[0x136 - 0x130];
    /* 0x136 */ short hand_state;
    /* 0x138 */ char unk_138[0x144 - 0x138];
    /* 0x144 */ unsigned char control_state;
    /* 0x145 */ unsigned char control_state_progress;
    /* 0x146 */ char unk_146[0x332 - 0x146];
    /* 0x332 */ short new_kong;
    /* 0x334 */ int strong_kong_ostand_bitfield;
} PlayerData;

typedef struct SwapStruct {
    /* 0x000 */ char unk_000[0x2C0];
    /* 0x2C0 */ char size;
} SwapStruct;

typedef struct LoadedActor {
    /* 0x000 */ ActorData* actor;
    /* 0x004 */ int unk4;
} LoadedActor;

typedef struct HUDDisplay {
	/* 0x000 */ void* actual_count_pointer;
	/* 0x004 */	s16 hud_count;
	/* 0x006 */	s8 freeze_timer;
	/* 0x007 */	s8 counter_timer;
	/* 0x008 */	u32 screen_x;
	/* 0x00C */	u32 screen_y;
	/* 0x010 */ s8 unk_10[0x20-0x10];
	/* 0x020 */ u32 hud_state;
	/* 0x024 */ s32 unk_24;
	/* 0x028 */	void* counter_pointer;
	/* 0x02C */ s32 unk_2c;
} HUDDisplay;

typedef struct hudData {
	/* 0x000 */ HUDDisplay item[0xE];
} hudData;

typedef struct buttons {
	unsigned char a : 1; // 0x8000
	unsigned char b : 1; // 0x4000
	unsigned char z : 1; // 0x2000
	unsigned char start : 1; // 0x1000
	unsigned char d_up : 1; // 0x0800
	unsigned char d_down : 1; // 0x0400
	unsigned char d_left : 1; // 0x0200
	unsigned char d_right : 1; // 0x0100
	unsigned char unused_0 : 1; // 0x0080
	unsigned char unused_1 : 1; // 0x0040
	unsigned char l : 1; // 0x0020
	unsigned char r : 1; // 0x0010
	unsigned char c_up : 1; // 0x0008
	unsigned char c_down : 1; // 0x0004
	unsigned char c_left : 1; // 0x0002
	unsigned char c_right : 1; // 0x0001
} buttons;

typedef struct Controller {
	/* 0x000 */ buttons Buttons;
	/* 0x002 */ s8 stickX;
	/* 0x003 */ s8 stickY;
} Controller;

typedef struct DemoStruct {
	/* 0x000 */ s32 map;
	/* 0x004 */ s32 kong;
} DemoStruct;

typedef struct stack_trace_log {
    /* 0x000 */ void* addr;
    /* 0x004 */ int used;
} stack_trace_log;

typedef struct char_spawner_flag_mapping {
	/* 0x000 */ unsigned char map;
	/* 0x001 */ char unk1;
	/* 0x002 */ short spawner_id;
	/* 0x004 */ short flag;
	/* 0x006 */ char required_flag_state;
	/* 0x007 */ char pad7;
} char_spawner_flag_mapping;

typedef struct character_spawner {
	/* 0x000 */ char unk_00[0x13];
	/* 0x013 */ unsigned char trigger;
	/* 0x014 */ char unk_14[0x42 - 0x14];
	/* 0x042 */ short properties;
} character_spawner;

typedef struct spawner_master_data {
	/* 0x000 */ short count;
	/* 0x002 */ short unk2;
	/* 0x004 */ character_spawner* spawners;
} spawner_master_data;