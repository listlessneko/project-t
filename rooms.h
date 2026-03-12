#pragma once

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
} Room;

void explore(Player *player);
void view_map(Player *player);
