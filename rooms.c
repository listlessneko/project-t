#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "rooms.h"
#include "utils.h"

int room_count = 0;

char *directions[] = { "north", "east", "west", "south" };

void explore_room(Player *player, int choice) {
  Room **next = NULL;
  if (choice == 1) {
    next = &player->current_room->north;
  } else if (choice == 2) {
    next = &player->current_room->east;
  } else if (choice == 3) {
    next = &player->current_room->west;
  } else if (choice == 4) {
    next = &player->current_room->south;
  }

  if (*next == NULL && room_count < MAX_ROOMS) {
    *next = generate_room();
  }
  player->current_room = *next;
}

Room *generate_room(void) {
  if (room_count < MAX_ROOMS) {
    Room *new_room = malloc(sizeof(Room));
    if (new_room == NULL) {
      return NULL;
    }
    // room attributes
    room_count++;
    new_room->visited = 0;
    return new_room;
  } else {
    return NULL;
  }
}


int explore(Player *player) {
  print_text(PRINT_FAST3, "[1] Go north\n");
  print_text(PRINT_FAST3, "[2] Go east\n");
  print_text(PRINT_FAST3, "[3] Go west\n");
  print_text(PRINT_FAST3, "[4] Go south\n");

  char choice[32];
  fgets(choice, sizeof(choice), stdin);
  choice[strcspn(choice, "\n")] = '\0';

  int choice_int = atoi(choice);
  if (choice_int >= 1 && choice_int <= 4) {
    explore_room(player, choice_int);
  } else if (strcmp(choice, "quit") == 0) {
    print_text(PRINT_NORMAL5, "You open your eyes and realize it was just a dream.");
    return 1;
  } else {
    print_text(PRINT_NORMAL5, "You stare off into the distance...");
  }
  return 0;
}

