#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "items.h"
#include "inventory.h"
#include "terminal.h"
#include "game.h"
#include "utils.h"
#include "rooms.h"

Player *create_player() {
  Player *player = malloc(sizeof(Player));
  if (player == NULL) {
    return NULL;
  }
  player->level = 1;
  player->exp = 0;
  player->health = 30;
  player->max_health = 30;
  player->attack = 5;
  player->defense = 3;
  player->gold = 0;
  player->inventory_count = 0;

  Item *sword = create_item(ITEM_WEAPON, "Sword", 0, 1, 0);
  add_item_to_player_inventory(player, sword);
  equip_item(player, sword);

  Item *shield = create_item(ITEM_SHIELD, "Shield", 0, 0, 1);
  add_item_to_player_inventory(player, shield);
  equip_item(player, shield);

  Item *axe = create_item(ITEM_WEAPON, "Axe", 0, 1, 0);
  add_item_to_player_inventory(player, axe);

  Item *round_shield = create_item(ITEM_SHIELD, "Round Shield", 0, 0, 1);
  add_item_to_player_inventory(player, round_shield);

  Item *Dagger = create_item(ITEM_WEAPON, "Dagger", 0, 1, 0);
  add_item_to_player_inventory(player, Dagger);

  Item *rectangle_shield = create_item(ITEM_SHIELD, "Rectangle Shield", 0, 0, 1);
  add_item_to_player_inventory(player, rectangle_shield);

  Item *short_sword = create_item(ITEM_WEAPON, "Short Sword", 0, 1, 0);
  add_item_to_player_inventory(player, short_sword);

  Item *square_shield = create_item(ITEM_SHIELD, "Square Shield", 0, 0, 1);
  add_item_to_player_inventory(player, square_shield);

  Item *long_sword = create_item(ITEM_WEAPON, "Long Sword", 0, 1, 0);
  add_item_to_player_inventory(player, long_sword);

  Item *triangle_shield = create_item(ITEM_SHIELD, "Triangle Shield", 0, 0, 1);
  add_item_to_player_inventory(player, triangle_shield);

  player->current_room = NULL;
  player->map = NULL;

  initialize_visited_rooms(player);

  player->current_menu = &main_menu;

  return player;
};

void initialize_visited_rooms(Player *player) {
  player->visited_rooms = malloc(sizeof(VisitedRooms));
  if (player->visited_rooms == NULL) {
    return;
  }
  player->visited_rooms->count = 0;
  return;
}

Enemy *create_enemy(char *name, int max_health, int attack, int defense) {
  Enemy *enemy = malloc(sizeof(Enemy));
  if (enemy == NULL) {
    return NULL;
  }
  strcpy(enemy->name, name);
  enemy->max_health = max_health;
  enemy->health = max_health;
  enemy->attack = attack;
  enemy->defense = defense;
  return enemy;
};

void destroy_enemy(Enemy *enemy) {
  free(enemy);
}

void start_game(Player *player) {
  srand(time(NULL));
  print_text(PRINT_NORMAL5, "What is your name, traveler?\n");

  read_input(player->name, 32);

  print_text(PRINT_NORMAL5, "Hello, %s. It is time to continue your journey.\n", player->name);
  print_text(PRINT_VERY_SLOW50, "...\n");
  print_text(PRINT_NORMAL5, "You find yourself sitting in the middle of a forest.\n");
  print_text(PRINT_NORMAL5, "You've been resting your strained back against a large tree while letting your mind wander off.\n");
  print_text(PRINT_NORMAL5, "The breaking sound of a distant tree branch snaps you back to reality.\n");
  print_text(PRINT_NORMAL5, "You have to keep moving before the sun sets.\n");

  player->map = NULL;
  player->current_room = NULL;
  player->current_room = build_room(player, DIRECTION_NONE);
  player->visited_rooms->visited[0] = player->current_room;
  player->visited_rooms->count = 1;
  print_text(PRINT_NORMAL5, "[Entered %s]\n", player->current_room->name);
  print_text(PRINT_NORMAL5, "%s\n", player->current_room->description);
}

void game_loop(Player *player) {
  while(playing(player)) {}
}
