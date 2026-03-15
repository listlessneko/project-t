#include <stdio.h>
#include "game.h"
#include "rooms.h"

int main(void) {
  Player player;
  start_game(&player);
  game_loop(&player);
  return 0;
}
