#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "terminal.h"
#include "game.h"
#include "utils.h"
#include "rooms.h"

void start_game(Player *player) {
  srand(time(NULL));
  player->level = 1;
  player->exp = 0;
  player->health = 30;
  player->max_health = 30;
  player->attack = 5;
  player->defense = 3;
  player->gold = 0;
  player->inventory_count = 0;
  player->visited_rooms = malloc(sizeof(VisitedRooms));
  if (player->visited_rooms == NULL) {
    return;
  }
  player->visited_rooms->count = 0;
  player->current_room = generate_room(player);
  player->visited_rooms->visited[0] = player->current_room;
  player->visited_rooms->count = 1;
  print_text(PRINT_NORMAL5, "What is your name, traveler?\n");

  read_input(player->name, 32);

  print_text(PRINT_NORMAL5, "Hello, %s. It is time to continue your journey.\n", player->name);
  print_text(PRINT_VERY_SLOW50, "...\n");
  print_text(PRINT_NORMAL5, "You find yourself sitting in the middle of a forest.\n");
  print_text(PRINT_NORMAL5, "You've been resting your strained back against a large tree while letting your mind wander off.\n");
  print_text(PRINT_NORMAL5, "The breaking sound of a distant tree branch snaps you back to reality.\n");
  print_text(PRINT_NORMAL5, "You have to keep moving before the sun sets.\n");
}

void game_loop(Player *player) {
  while(!explore(player)) {}
}
