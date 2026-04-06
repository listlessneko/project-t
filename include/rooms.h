#pragma once

#define MAX_ROOMS 12
#define MAX_SAFE_ROOMS 1
#define MAX_EASY_ROOMS 3
#define MAX_NORMAL_ROOMS 5
#define MAX_HARD_ROOMS 3
#define MAX_ROOM_ITEMS 3

typedef enum RoomKind {
  SAFE,
  EASY,
  NORMAL,
  HARD,
} RoomKind;

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
  char name[50];
  char description[256];
  int id;
  RoomKind kind;
  struct Room *north;
  struct Room *east;
  struct Room *west;
  struct Room *south;
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

extern char *directions[];

int explore(Player *player);
void explore_room(Player *player, int choice);
Room *generate_room(Player *player, int choice);
int add_item_to_room(Room *room, Item *item);
int remove_item_from_room(Room *room, Item *item);
void view_map(Player *player);
