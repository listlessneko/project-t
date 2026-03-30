#include <stdlib.h>
#include <string.h>
#include "actions.h"
#include "game.h"
#include "inventory.h"
#include "items.h"
#include "rooms.h"
#include "utils.h"
#include "terminal.h"

ParsedCommand parse_input(const char *input) {
  ParsedCommand output = {
    .kind = CMD_KIND_UNKNOWN,
    .target = ""
  };

  if (input == NULL) {
    return output;
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

int drop_item(Player *player, Item *item, Room *room) {
  if (player == NULL || item == NULL || room == NULL) {
    return DROP_ITEM_INVALID;
  }

  int removed_from_inventory = remove_item_from_player_inventory(player, item);
  if (removed_from_inventory == ITEM_REMOVE_FROM_INVENTORY_SUCCESS) {
    int added_to_room = add_item_to_room(room, item);
    if (added_to_room == ITEM_ADD_TO_ROOM_SUCCESS) {
      return DROP_ITEM_SUCCESS;
    } else if (added_to_room == ROOM_ITEMS_FULL) {
      destroy_item(item);
      return DROP_ITEM_FULL;
    }
  }
  return DROP_ITEM_ERROR;
}

int pick_up_item(Player *player, Item *item, Room *room) {
  if (player == NULL || item == NULL || room == NULL) {
    return PICK_UP_ITEM_INVALID;
  }

  int removed_from_room = remove_item_from_room(room, item);
  if (removed_from_room == ITEM_REMOVE_FROM_ROOM_SUCCESS) {
    int added_to_inventory = add_item_to_player_inventory(player, item);
    if (added_to_inventory == INVENTORY_ITEMS_FULL) {
      add_item_to_room(room, item);
      return PICK_UP_ITEM_FULL;
    } else if (added_to_inventory == ITEM_ADD_TO_INVENTORY_SUCCESS) {
      return PICK_UP_ITEM_SUCCESS;
    }
  }
  return PICK_UP_ITEM_ERROR;
}
