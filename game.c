#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "utils.h"

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

  print_text(PRINT_NORMAL5, "Hello, %s. It is time to begin your quest.\n", player->name);
  print_text(PRINT_VERY_SLOW100, "...\n");
  print_text(PRINT_NORMAL5, "You find yourself standing at the entrance of a castle.\n");
}
