#include <stddef.h>
#include <stdlib.h>

typedef struct {
  char name[32];
  int level;
  int health;
  int max_health;
  int attack;
  int defense;
} Player;

void start_game(Player *player);
