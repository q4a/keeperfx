/******************************************************************************/
// Free implementation of Bullfrog's Dungeon Keeper strategy game.
/******************************************************************************/
/** @file dungeon_data.h
 *     Header file for dungeon_data.c.
 * @par Purpose:
 *     Dungeon data structures definitions.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     10 Nov 2009 - 20 Jan 2010
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef DK_DNGN_DATA_H
#define DK_DNGN_DATA_H

#include "bflib_basics.h"
#include "globals.h"
#include "dungeon_stats.h"
#include "engine_camera.h"
#include "thing_creature.h"
#include "thing_doors.h"
#include "room_data.h"
#include "player_data.h"
#include "map_events.h"
#include "tasks_list.h"
#include "thing_traps.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
#define DUNGEONS_COUNT          5
#define IMP_TASK_MAX_COUNT     64
#define DUNGEON_RESEARCH_COUNT 34
#define MAX_THINGS_IN_HAND      8
#define KEEPER_SPELLS_COUNT    20
#define TURN_TIMERS_COUNT       8
#define SCRIPT_FLAGS_COUNT      8
#define MAX_SOE_RADIUS         13
#define CREATURE_GUI_JOBS_COUNT 3

#define INVALID_DUNGEON (&bad_dungeon)

enum DungeonCreatureTendencies {
    CrTend_None       = 0,
    CrTend_Imprison   = 1,
    CrTend_Flee       = 2,
};

enum DungeonResearchCategory {
    RsCat_None        = 0,
    RsCat_Power       = 1,
    RsCat_Room        = 2,
    RsCat_Creature    = 3,
};

enum DungeonManufactureBuildFlags {
    MnfBldF_Manufacturable = 0x01,
    MnfBldF_Built          = 0x02,
    MnfBldF_Used           = 0x04,
};

/******************************************************************************/
#pragma pack(1)

struct DiggerStack { // sizeof = 4
      unsigned short field_0;
      unsigned short task_id;
};

struct ResearchVal { // sizeof = 6
  unsigned char rtyp;
  unsigned char rkind;
  long req_amount;
};

struct TurnTimer { // sizeof = 5
  unsigned long count;
  unsigned char state;
};

#define SIZEOF_Dungeon 0x1508
struct Dungeon {
    unsigned short dnheart_idx;
    struct Coord3d mappos;
    unsigned char creature_tendencies;
    unsigned char field_9;
    unsigned char computer_enabled;
    unsigned short room_kind[ROOM_TYPES_COUNT];
    short creatr_list_start;
    short digger_list_start;
    short field_31;
    short things_in_hand[MAX_THINGS_IN_HAND];
    short field_43;
    int field_45;
    int field_49;
    int field_4D;
    short field_51;
    short field_53;
    int field_55;
    int field_59;
    int field_5D;
    short field_61;
    unsigned char num_things_in_hand;
    short field_64[480];
    unsigned short job_breeds_count[CREATURE_TYPES_COUNT][3];
    unsigned short field_4E4[CREATURE_TYPES_COUNT][3];
    short field_5A4[15];
    unsigned char room_slabs_count[ROOM_TYPES_COUNT+1];
    int sight_casted_gameturn;
    short sight_casted_thing_idx;
    unsigned char sight_casted_splevel;
    unsigned char sight_casted_stl_x;
    unsigned char sight_casted_stl_y;
    unsigned char soe_explored_flags[2*MAX_SOE_RADIUS][2*MAX_SOE_RADIUS];
    unsigned char field_881;
    unsigned char field_882;
    unsigned char field_883;
    int field_884;
    unsigned long must_obey_turn;
    int field_88C[2];
    unsigned char field_894[CREATURE_TYPES_COUNT];
    unsigned char creatures_praying[CREATURE_TYPES_COUNT];
    unsigned char chickens_sacrificed;
    unsigned char field_8D5;
    unsigned char creature_sacrifice[CREATURE_TYPES_COUNT];
    unsigned char creature_sacrifice_exp[CREATURE_TYPES_COUNT];
    unsigned char field_916[2];
    unsigned char num_active_diggers;
    unsigned char num_active_creatrs;
    unsigned char owned_creatures_of_model[CREATURE_TYPES_COUNT];
    unsigned char total_rooms;
    unsigned short total_doors;
    unsigned short total_area;
    unsigned short total_creatures_left;
    int field_941;
    int doors_destroyed;
    short field_949;
    short field_94B[CREATURE_TYPES_COUNT];
    short creatures_scavenge_gain;
    short creatures_scavenge_lost;
    long scavenge_turn_points[CREATURE_TYPES_COUNT];
    short scavenge_targets[CREATURE_TYPES_COUNT];
    int creature_max_level[CREATURE_TYPES_COUNT];
    unsigned short creatures_annoyed;
    unsigned short battles_lost;
    unsigned short battles_won;
    /** Amount of room tiles a player had which were destroyed (vandalized or damaged by enemy). */
    unsigned short rooms_destroyed;
    unsigned short spells_stolen;
    unsigned short times_broken_into;
    unsigned short gold_pots_stolen;
    int last_entrance_generation_gameturn;
    int turns_between_entrance_generation;
    int field_AE5;
    int field_AE9[2];
    unsigned long max_gameplay_score;
    short field_AF5;
    short field_AF7;
    int total_money_owned;
    int offmap_money_owned;
    short hates_player[DUNGEONS_COUNT];
    struct MapTask task_list[MAPTASKS_COUNT];
    int field_E8F;
    int field_E93[3];
    unsigned char owner;
    int camera_deviate_quake;
    int camera_deviate_jump;
    long score;
    struct ResearchVal research[DUNGEON_RESEARCH_COUNT];
    int current_research_idx;
    unsigned char research_num;
unsigned char field_F7D;
    unsigned char room_buildable[ROOM_TYPES_COUNT];
    unsigned char room_resrchable[ROOM_TYPES_COUNT];
    /** How many creatures are force-enabled for each kind.
     * Force-enabled creature can come from portal without additional conditions,
     * but only until dungeon has up to given amount of their kind. */
    unsigned char creature_force_enabled[CREATURE_TYPES_COUNT];
    /** Defines whether a creature of each kind is allowed to come from portal.
     * Allowed creatures can join a dungeon if whether attraction condition is met
     * or force-enabled amount isn't reached. */
    unsigned char creature_allowed[CREATURE_TYPES_COUNT];
    unsigned char magic_level[KEEPER_SPELLS_COUNT];
    unsigned char magic_resrchable[KEEPER_SPELLS_COUNT];
    /** Amount of traps of every kind which are stored in workshops. Only on-map trap crates which exist in workshop are mentioned here.*/
    unsigned char trap_amount_stored[TRAP_TYPES_COUNT];
    /** Stores flag information about players manufacture of traps of specific kind. */
    unsigned char trap_build_flags[TRAP_TYPES_COUNT];
    /** Amount of traps of every kind for which we can place blueprints. This include both off-map traps and on-map trap boxes.*/
    unsigned char trap_amount_placeable[TRAP_TYPES_COUNT];
    /** Amount of doors of every kind which are stored in workshops. Only on-map door crates which exist in workshop are mentioned here.*/
    unsigned char door_amount_stored[DOOR_TYPES_COUNT];
    /** Stored flag information about players manufacture of doors of specific kind. */
    unsigned char door_build_flags[DOOR_TYPES_COUNT];
    /** Stored information whether player can place blueprints of doors of specific kind (actually, doors are placed instantly). */
    unsigned char door_amount_placeable[DOOR_TYPES_COUNT];
    struct TurnTimer turn_timers[TURN_TIMERS_COUNT];
    unsigned char script_flags[SCRIPT_FLAGS_COUNT];
    long max_creatures_attracted;
    unsigned char field_1060;
    long field_1061;
    struct Coord3d essential_pos;
    struct DiggerStack imp_stack[IMP_TASK_MAX_COUNT];
    unsigned long digger_stack_update_turn;
    unsigned long digger_stack_length;
    unsigned char visible_event_idx;
    /** Array with battle indexes with the battles currently visible in fight event message */
    unsigned char visible_battles[3];
    short zoom_annoyed_creature_idx;
    long total_experience_creatures_gained;
    long total_research_points;
long field_1181;
    long manufacture_progress;
    unsigned char manufacture_class;
    unsigned char manufacture_kind;
long field_118B;
long manufacture_level;
long field_1193;
    struct LevelStats lvstats;
    struct CreatureStorage dead_creatures[DEAD_CREATURES_MAX_COUNT];
    long dead_creatures_count;
    long dead_creature_idx;
    /** Contains map event index or each even button visible on screen. */
    unsigned char event_button_index[EVENT_BUTTONS_COUNT+1];
    long field_13B4[EVENT_KIND_COUNT-2]; // TODO FIGHT missing 8 bytes, we're using a WA for that
    unsigned short tortured_creatures[CREATURE_TYPES_COUNT];
    unsigned char bodies_rotten_for_vampire;
unsigned char field_1461[36];
    long field_1485;
    /** Stores how many creatures of each kind of has joined the dungeon during the level.
     * Values are saturated at 255. */
    unsigned char creature_models_joined[CREATURE_TYPES_COUNT];
    unsigned long fights_num;
    unsigned char research_override; // could be easily changed into flags..
int field_14AE;
unsigned char field_14B2[2];
int field_14B4;
    long creatures_total_pay;
unsigned char field_14BC[6];
    /** Index of last creature picked up of given model. */
    unsigned short selected_creatures_of_model[CREATURE_TYPES_COUNT];
    /** Index of last creature picked up of given GUI Job. */
    unsigned short selected_creatures_of_gui_job[CREATURE_GUI_JOBS_COUNT];
    };

#pragma pack()
/******************************************************************************/
extern struct Dungeon bad_dungeon;
/******************************************************************************/
struct Dungeon *get_players_num_dungeon_f(long plyr_idx,const char *func_name);
struct Dungeon *get_players_dungeon_f(const struct PlayerInfo *player,const char *func_name);
struct Dungeon *get_dungeon_f(PlayerNumber plyr_num,const char *func_name);
#define get_players_num_dungeon(plyr_idx) get_players_num_dungeon_f(plyr_idx,__func__)
#define get_players_dungeon(player) get_players_dungeon_f(player,__func__)
#define get_dungeon(plyr_idx) get_dungeon_f(plyr_idx,__func__)
#define get_my_dungeon() get_players_num_dungeon_f(my_player_number,__func__)

TbBool dungeon_invalid(const struct Dungeon *dungeon);

void clear_dungeons(void);
void init_dungeons(void);

void decrease_dungeon_area(PlayerNumber plyr_idx, long value);
void increase_room_area(PlayerNumber plyr_idx, long value);
void decrease_room_area(PlayerNumber plyr_idx, long value);
void increase_dungeon_area(PlayerNumber plyr_idx, long value);

void player_add_offmap_gold(PlayerNumber plyr_idx, long value);

void init_dungeons_essential_position(void);
const struct Coord3d *dungeon_get_essential_pos(PlayerNumber plyr_idx);
TbBool player_has_heart(PlayerNumber plyr_idx);
struct Thing *get_player_soul_container(PlayerNumber plyr_idx);

TbBool player_has_room(PlayerNumber plyr_idx, RoomKind rkind);
TbBool dungeon_has_room(const struct Dungeon *dungeon, RoomKind rkind);
struct Room *player_has_room_of_type(PlayerNumber plyr_idx, RoomKind rkind);

TbBool set_creature_tendencies(struct PlayerInfo *player, unsigned short tend_type, TbBool val);
TbBool toggle_creature_tendencies(struct PlayerInfo *player, unsigned short tend_type);
TbBool player_creature_tends_to(PlayerNumber plyr_idx, unsigned short tend_type);

TbBool set_trap_buildable_and_add_to_amount(PlayerNumber plyr_idx, ThingModel trap_kind, long buildable, long amount);
TbBool set_door_buildable_and_add_to_amount(PlayerNumber plyr_idx, ThingModel door_kind, long buildable, long amount);

TbBool restart_script_timer(PlayerNumber plyr_idx, long timer_id);
TbBool set_script_flag(PlayerNumber plyr_idx, long flag_id, long value);

/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
