#pragma once

#include "entities.h"
#include "utils.h"

#define MAX_AREA_WIDTH 10
#define MAX_AREA_HEIGHT 10
#define MAX_MAP_SIZE (MAX_AREA_WIDTH * MAX_AREA_HEIGHT + MAX_AREA_HEIGHT + 1)
#define MAX_MAP_STR_SIZE MAX_PRINT_BUFFER
#define MAX_ROOMS 12
#define MAX_ROOMS 12
#define MAX_SAFE_ROOMS 1
#define MAX_EASY_ROOMS 3
#define MAX_NORMAL_ROOMS 5
#define MAX_HARD_ROOMS 3
#define MAX_ROOM_ITEMS 3

typedef struct Map {
  Room *grid[MAX_AREA_WIDTH][MAX_AREA_HEIGHT];
} Map;

typedef enum DirectionKind {
  DIRECTION_NONE,
  DIRECTION_NORTH,
  DIRECTION_EAST,
  DIRECTION_WEST,
  DIRECTION_SOUTH,
} DirectionKind;

typedef struct RoomKindCounter {
  int safe;
  int easy;
  int normal;
  int hard;
} RoomKindCounter;

typedef struct RoomKindLimits {
  int safe;
  int easy;
  int normal;
  int hard;
} RoomKindLimits;

typedef struct Player Player;
typedef struct Enemy Enemy;
typedef struct Item Item;

typedef struct Room {
  EntityKind entity_kind;
  int id;
  char name[MAX_NAME_LEN];
  char description[MAX_DESCRIPTION_LEN];
  RoomKind kind;
  int x;
  int y;
  Enemy *enemy;
  Item *items[MAX_ROOM_ITEMS];
  int items_count;
  int visited;
} Room;

typedef struct RoomAppearanceTemplate {
  char *name;
  char *description;
  RoomKind kind;
} RoomAppearanceTemplate;

typedef struct RoomContentsTemplate {
  char *enemy_name;
  RoomKind kind;
  int enemy_max_health;
  int enemy_min_health;
  int enemy_max_attack;
  int enemy_min_attack;
  int enemy_max_defense;
  int enemy_min_defense;
} RoomContentsTemplate;

typedef struct VisitedRooms {
  Room *visited[MAX_ROOMS];
  int count;
} VisitedRooms;

const char *direction_to_string(DirectionKind direction_kind);
char direction_to_char(DirectionKind direction_kind);
int explore(Player *player);
void explore_room(Player *player, DirectionKind direction);
Room *build_room(Player *player, DirectionKind direction);
int add_item_to_room(Room *room, Item *item);
int remove_item_from_room(Room *room, Item *item);
