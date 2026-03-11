#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

void start_game(Player *player) {
  srand(time(NULL));
  player->level = 1;
  player->health = 30;
  player->max_health = 30;
  player->attack = 5;
  player->defense = 3;
  printf("What is your name, traveler?\n");
  fgets(player->name, 32, stdin);
  player->name[strcspn(player->name, "\n")] = '\0';
  printf("Hello, %s.\n", player->name);
}
