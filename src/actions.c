#pragma once

#include <stdlib.h>
#include <string.h>
#include "entities.h"
#include "status.h"
#include "actions.h"
#include "game.h"
#include "inventory.h"
#include "item.h"
#include "area.h"
#include "terminal.h"
#include "utils.h"

MenuOptions main_menu_options[] = {
  {
    .display_type = { MENU_KIND_EXPLORE },
    .name = "Explore",
    .description = "Continue your adventure.",
  },
  {
    .display_type = { MENU_KIND_EXAMINE },
    .name = "Examine",
    .description = "Examine your surroundings and self.",
  },
  {
    .display_type = { MENU_KIND_FIGHT },
    .name = "Fight",
    .description = "Take care of the vagabond.",
  },
  {
    .display_type = { SELECT_KIND_QUIT },
    .name = "Quit",
    .description = "Quit the adventure.",
  },
};

MenuOptions examine_menu_options[] ={
  {
    .display_type = { MENU_KIND_EXAMINE_AREA },
    .name = "Area",
    .description = "View your surroundings.",
  },
  {
    .display_type = { MENU_KIND_EXAMINE_INVENTORY },
    .name = "Inventory",
    .description = "View your inventory.",
  },
  {
    .display_type = { MENU_KIND_EXAMINE_MAP },
    .name = "Map",
    .description = "Study your surroundings.",
  },
  {
    .display_type = { MENU_KIND_EXAMINE_STATS },
    .name = "Stats",
    .description = "See how far you've come.",
  }
};

DisplayOptions *parse_menu_input(Player *player, MenuKind menu_kind) {
  if (player == NULL || menu_kind == MENU_KIND_UNKNOWN) {
    return NULL;
  }
  
  int count = 0;

  switch (menu_kind) {
    case MENU_KIND_MAIN: {
      count = 3;
      if (player->current_area->enemy != NULL) {
        count++;
      }
    case MENU_KIND_EXAMINE: {
    }
  }
}

ParsedCommand parse_input(const char *input) {
  ParsedCommand output = {
    .kind = CMD_KIND_UNKNOWN,
    .target = ""
  };

  if (input == NULL) {
    return output;
  }
  return output;
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
    explore_area(player, choice_int);
  } else if (strcmp(choice, "quit") == 0) {
    print_text(PRINT_NORMAL5, "You open your eyes and realize it was just a dream.\n");
    return 1;
  } else {
    print_text(PRINT_NORMAL5, "You stare off into the distance...\n");
  }
  return 0;
}

int drop_item(Player *player, Item *item, Area *area) {
  if (player == NULL || item == NULL || area == NULL) {
    return DROP_ITEM_INVALID;
  }

  int removed_from_inventory = remove_item_from_player_inventory(player, item);
  if (removed_from_inventory == ITEM_REMOVE_FROM_INVENTORY_SUCCESS) {
    int added_to_area = add_item_to_area(area, item);
    if (added_to_area == ITEM_ADD_TO_AREA_SUCCESS) {
      return DROP_ITEM_SUCCESS;
    } else if (added_to_area == AREA_ITEMS_FULL) {
      destroy_item(item);
      return DROP_ITEM_FULL;
    }
  }
  return DROP_ITEM_ERROR;
}

int pick_up_item(Player *player, Item *item, Area *area) {
  if (player == NULL || item == NULL || area == NULL) {
    return PICK_UP_ITEM_INVALID;
  }

  int removed_from_area = remove_item_from_area(area, item);
  if (removed_from_area == ITEM_REMOVE_FROM_AREA_SUCCESS) {
    int added_to_inventory = add_item_to_player_inventory(player, item);
    if (added_to_inventory == INVENTORY_ITEMS_FULL) {
      add_item_to_area(area, item);
      return PICK_UP_ITEM_FULL;
    } else if (added_to_inventory == ITEM_ADD_TO_INVENTORY_SUCCESS) {
      return PICK_UP_ITEM_SUCCESS;
    }
  }
  return PICK_UP_ITEM_ERROR;
}
