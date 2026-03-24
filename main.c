#include "game.h"
#include "rooms.h"
#include "terminal.h"

int main(void) {
  #ifndef _WIN32
    enable_raw_mode();
  #endif
  Player *player = create_player();
  start_game(player);
  game_loop(player);
  return 0;
}
