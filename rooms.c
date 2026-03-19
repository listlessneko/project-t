#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "rooms.h"
#include "terminal.h"
#include "utils.h"

int room_count = 0;

char *directions[] = { "north", "east", "west", "south" };
RoomTemplate room_templates[] = {
  {
    .name = "Grove",
    .description = "This is a grove...",
    .kind = SAFE
  },
  {
    .name = "Glade",
    .description = "This is a glade...",
    .kind = EASY
  },
  {
    .name = "Clearing",
    .description = "This is a clearing...",
    .kind = EASY
  },
  {
    .name = "Hollow",
    .description = "This is a hollow...",
    .kind = EASY
  },
  {
    .name = "Ridge",
    .description = "This is a ridge...",
    .kind = NORMAL
  },
  {
    .name = "Creek Bed",
    .description = "This is a creek bed...",
    .kind = NORMAL
  },
  {
    .name = "Undergrowth",
    .description = "This is an undergrowth...",
    .kind = NORMAL
  },
  {
    .name = "Fork",
    .description = "This is a Fork...",
    .kind = NORMAL
  },
  {
    .name = "Abandoned Camp",
    .description = "This is an Abandoned Camp...",
    .kind = NORMAL
  },
  {
    .name = "Main Road",
    .description = "This is Main Road...",
    .kind = HARD
  },
  {
    .name = "Wens Pass",
    .description = "This is Wens Pass...",
    .kind = HARD
  },
  {
    .name = "Wens Village",
    .description = "This is Wens Village...",
    .kind = HARD
  },
};

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

  if (*next == NULL && player->visited_rooms->count < MAX_ROOMS) {
    *next = generate_room(player);
  }
  player->current_room = *next;
}

Room *generate_room(Player *player) {
  if (player->visited_rooms->count < MAX_ROOMS) {
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
  print_text(PRINT_FAST3,
             "[1] Go north\n"
             "[2] Go east\n"
             "[3] Go west\n"
             "[4] Go south\n"
             );

  char choice[32];
  read_input(choice, sizeof(choice));

  int choice_int = atoi(choice);
  if (choice_int >= 1 && choice_int <= 4) {
    explore_room(player, choice_int);
  } else if (strcmp(choice, "quit") == 0) {
    print_text(PRINT_NORMAL5, "You open your eyes and realize it was just a dream.\n");
    return 1;
  } else {
    print_text(PRINT_NORMAL5, "You stare off into the distance...\n");
  }
  return 0;
}

