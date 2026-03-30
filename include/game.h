#pragma once

#include "items.h"
#include "rooms.h"

typedef enum EntityKind {
  PLAYER,
  ENEMY,
  ITEM,
  ROOM,
  UNKNOWN,
} EntityKind;

typedef enum EnemyKind {
  ENEMY_EASY,
  ENEMY_NORMAL,
  ENEMY_HARD,
} EnemyKind;

typedef struct Enemy {
  EntityKind entity_kind;
  EnemyKind enemy_kind;
  int id;
  char name[32];
  char description[256];
  int level;
  int health;
  int max_health;
  int attack;
  int defense;
} Enemy;

typedef enum PlayerKind {
  ADVENTURER,
} PlayerKind;

typedef struct Player {
  EntityKind entity_kind;
  PlayerKind player_kind;
  int id;
  char name[32];
  char description[256];
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
