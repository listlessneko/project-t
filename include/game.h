#pragma once

#include "items.h"
#include "rooms.h"

typedef struct Enemy {
  char name[32];
  int level;
  int health;
  int max_health;
  int attack;
  int defense;
} Enemy;

typedef struct Player {
  char name[32];
  int level;
  int exp;
  int health;
  int max_health;
  int attack;
  int defense;
  int gold;
  Item *weapon;
  Item *shield;
  Item *accessory;
  Item *inventory[12];
  int inventory_count;
  Room *current_room;
  VisitedRooms *visited_rooms;
} Player;


void start_game(Player *player);
Player *create_player();
void initialize_visited_rooms(Player *player);
Enemy *create_enemy(char *name, int max_health, int attack, int defense);
void destroy_enemy(Enemy *enemy);
void game_loop(Player *player);
void combat(Player *player, Enemy *enemy);
