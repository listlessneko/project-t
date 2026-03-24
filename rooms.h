#pragma once

// A way to track how many rooms have been generated so far
// A function that generates a new room and returns a pointer to it
// Logic in explore that checks if a direction exists, generates if not, then moves the player

#define MAX_ROOMS 12
#define MAX_SAFE_ROOMS 1
#define MAX_EASY_ROOMS 3
#define MAX_NORMAL_ROOMS 3
#define MAX_HARD_ROOMS 3

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
  Item *items;
  int visited;
} Room;

typedef struct RoomAppearanceTemplate {
  char *name;
  char *description;
  RoomKind kind;
} RoomAppearanceTemplate;

typedef struct RoomContentsTemplate {
  char *enemy_name;
  int enemy_max_health;
  int enemy_min_health;
  int enemy_max_attack;
  int enemy_min_attack;
  int enemy_max_defense;
  int enemy_min_defense;
  Item *items;
  RoomKind kind;
} RoomContentsTemplate;

typedef struct VisitedRooms {
  Room *visited[MAX_ROOMS];
  int count;
} VisitedRooms;

extern char *directions[];

int explore(Player *player);
void explore_room(Player *player, int choice);
Room *generate_room(Player *player, int choice);
void view_map(Player *player);
