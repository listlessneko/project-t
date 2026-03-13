#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
  print_text(PRINT_NORMAL5, "What is your name, traveler?\n");

  fgets(player->name, 32, stdin);
  player->name[strcspn(player->name, "\n")] = '\0';

  print_text(PRINT_NORMAL5, "Hello, %s. It is time to continue your journey.\n", player->name);
  print_text(PRINT_VERY_SLOW50, "...\n");
  print_text(PRINT_NORMAL5, "You find yourself sitting in the middle of a forest.\n");
  print_text(PRINT_NORMAL5, "You've been resting your strained back against a large tree while letting your mind wander off.\n");
  print_text(PRINT_NORMAL5, "The breaking sound of a distant tree branch snaps you back to reality.\n");
  print_text(PRINT_NORMAL5, "You have to keep moving before the sun sets.\n");

  explore(player);
}
