#include <stdio.h>
#include "rooms.h"
#include "utils.h"

typedef struct Player Player;

char *directions[] = { "north", "east", "west", "south" };

void explore(Player *player) {
  print_text(PRINT_FAST3, "[1] Go north\n");
  print_text(PRINT_FAST3, "[2] Go east\n");
  print_text(PRINT_FAST3, "[3] Go west\n");
  print_text(PRINT_FAST3, "[4] Go south\n");

  int choice;
  scanf("%d", &choice);

  print_text(PRINT_NORMAL5, "You decide to go %s.\n", directions[choice - 1]);
}
