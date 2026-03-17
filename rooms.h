#pragma once

// A way to track how many rooms have been generated so far
// A function that generates a new room and returns a pointer to it
// Logic in explore that checks if a direction exists, generates if not, then moves the player

#define MAX_ROOMS 10

typedef struct Player Player;
typedef struct Enemy Enemy;
typedef struct Item Item;

typedef struct Room {
  char name[50];
  char description[256];
  struct Room *north;
  struct Room *east;
  struct Room *west;
  struct Room *south;
  Enemy *enemy;
  Item *items;
  int visited;
} Room;

typedef struct RoomTemplate {
  char *name;
  char *description;
} RoomTemplate;

extern char *directions[];

int explore(Player *player);
void explore_room(Player *player, int choice);
Room *generate_room(void);
void view_map(Player *player);
