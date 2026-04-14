#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "entities.h"
#include "game.h"
#include "rooms.h"
#include "items.h"
#include "terminal.h"
#include "utils.h"

MenuNode explore_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_EXPLORE,
  .name = { "Explore" },
  .description = { "Continue on your adventure." },
  .is_static = 1,
};

MenuNode examine_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_EXAMINE,
  .name = { "Examine" },
  .description = { "Examine your surrounding or yourself." },
  .is_static = 1,
};

MenuNode examine_room_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_EXAMINE_ROOM,
  .name = { "Examine room" },
  .description = { "Examine your surroundings." },
};

MenuNode examine_inventory_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_EXAMINE_INVENTORY,
  .name = { "Examine inventory" },
  .description = { "Examine your items." },
  .is_static = 1,
};

MenuNode examine_map_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_EXAMINE_MAP,
  .name = { "Examine map" },
  .description = { "Examine how far you have traveled." },
  .is_static = 1,
};

MenuNode examine_stats_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_EXAMINE_STATS,
  .name = { "Examine stats" },
  .description = { "Examine how far you have grown." },
  .is_static = 1,
};

MenuNode fight_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_FIGHT,
  .name = { "Fight" },
  .description = { "Eliminate the enemy." },
  .is_static = 1,
};

MenuNode pick_up_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_PICK_UP,
  .name = { "Pick Up" },
  .description = { "Pick up item." },
  .is_static = 1,
};

MenuNode use_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_USE,
  .name = { "Use" },
  .description = { "Use item." },
  .is_static = 1,
};

MenuNode drop_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_DROP,
  .name = { "Drop" },
  .description = { "Drop item." },
  .is_static = 1,
};

MenuNode throw_away_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_THROW_AWAY,
  .name = { "Throw Away" },
  .description = { "Throw away item." },
  .is_static = 1,
};

MenuNode back_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_BACK,
  .name = { "Back" },
  .description = { "Back to previous menu." },
  .is_static = 1,
};

MenuNode quit_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_QUIT,
  .name = { "Quit" },
  .description = { "Return to reality." },
  .is_static = 1,
};

Menu main_menu = {
  .name = { "Main Menu" },
  .description = { "This is the main menu." },
  .is_static = 1,
  .prev_menu = NULL,
  .prev_page = NULL,
  .next_page = NULL,
  .options_count = 4,
  .options = {
    &explore_node,
    &examine_node,
    &fight_node,
    &quit_node
  }
};

Menu examine_menu = {
  .name = { "Examine" },
  .description = { "This is the examine menu." },
  .prev_menu = &main_menu,
  .is_static = 1,
  .prev_page = NULL,
  .next_page = NULL,
  .options_count = 5,
  .options = {
    &examine_room_node,
    &examine_inventory_node,
    &examine_map_node,
    &examine_stats_node,
    &back_node
  }
};

MenuNode *build_examine_item_menu_node(MenuKind menu_kind, Item *item) {
  MenuNode *menu_node = malloc(sizeof(MenuNode));
  if (menu_node == NULL) {
    return NULL;
  }

  menu_node->node_kind = NODE_MENU;
  menu_node->data_kind.menu_kind = menu_kind;
  menu_node->data.item = item;

  snprintf(menu_node->name, sizeof(menu_node->name), "Examine %s", item->name);
  return menu_node;
};

MenuNode *build_explore_room_menu_node(DirectionKind direction_kind, Room *room) {
  MenuNode *menu_node = malloc(sizeof(MenuNode));
  if (menu_node == NULL) {
    return NULL;
  }

  menu_node->node_kind = NODE_ACTION;
  menu_node->data_kind.action_kind = ACTION_GO;
  menu_node->data.room = room;
  menu_node->action.direction = direction_kind;

  if (room == NULL) {
    snprintf(menu_node->name, sizeof(menu_node->name), "Go %s (???)", direction_to_string(direction_kind));
  } else {
    snprintf(menu_node->name, sizeof(menu_node->name), "Go %s (%s)", direction_to_string(direction_kind), room->name);
  }
  return menu_node;
};

Menu *menu_malloc(int options_count) {
  Menu *menu = malloc(sizeof(Menu) + sizeof(MenuNode *) * options_count);
  if (menu == NULL) {
    return NULL;
  }
  menu->options_count = options_count;
  return menu;
};

void destroy_menu_node(MenuNode *menu_node) {
  if (menu_node == NULL || menu_node->is_static) {
    return;
  }
  free(menu_node);
}

Menu *build_menu(MenuKind menu_kind, Player *player) {

  Menu *new_menu = NULL;

  switch (menu_kind) {
    case MENU_MAIN: {
      return new_menu = &main_menu;
    }
    case MENU_EXPLORE: {
      new_menu = menu_malloc(5);
      strncpy(new_menu->name, "Explore Menu", sizeof(new_menu->name) - 1);
      new_menu->name[31] = '\0';
      Room *current_room = player->current_room;
      new_menu->options[0] = build_explore_room_menu_node(DIRECTION_NORTH, current_room->north);
      new_menu->options[1] = build_explore_room_menu_node(DIRECTION_EAST, current_room->east);
      new_menu->options[2] = build_explore_room_menu_node(DIRECTION_WEST, current_room->west);
      new_menu->options[3] = build_explore_room_menu_node(DIRECTION_SOUTH, current_room->south);
      new_menu->options[4] = &back_node;
      break;
    }
    case MENU_EXAMINE: {
      return new_menu = &examine_menu;
    }
    case MENU_EXAMINE_ROOM: {
      Room *current_room = player->current_room;
      new_menu = menu_malloc(current_room->items_count + 1);
      int i = 0;
      for (i = 0; i < current_room->items_count; i++) {
        new_menu->options[i] = build_examine_item_menu_node(MENU_EXAMINE_ROOM_ITEM, current_room->items[i]);
      }
      new_menu->options[i] = &back_node;
      break;
    }
    case MENU_EXAMINE_INVENTORY: {
      new_menu = menu_malloc(player->inventory_count + 1);
      int i = 0;
      for (i = 0; i < player->inventory_count; i++) {
        new_menu->options[i] = build_examine_item_menu_node(MENU_EXAMINE_INVENTORY_ITEM, player->inventory[i]);
      }
      new_menu->options[i] = &back_node;
      break;
    }
    case MENU_EXAMINE_MAP: {
      new_menu = menu_malloc(1);
      new_menu->options[0] = &back_node;
      break;
    }
    case MENU_EXAMINE_STATS: {
      new_menu = menu_malloc(1);
      new_menu->options[0] = &back_node;
      break;
    }
  }
  return new_menu;
}

void destroy_menu(Menu *menu) {
  if (menu == NULL || menu->is_static) {
    return;
  }

  for (int i = 0; i < menu->options_count; i++) {
    destroy_menu_node(menu->options[i]);
  }

  destroy_menu(menu->prev_page);
  destroy_menu(menu->next_page);
  free(menu);
}

void display_menu(Menu *menu) {
  /*print_text(PRINT_NORMAL5, "%s\n", menu->name);*/
  /*print_text(PRINT_NORMAL5, "%s\n", menu->description);*/
  /**/
  for (int i = 0; i < menu->options_count; i++) {
    MenuNode *menu_node = menu->options[i];
    print_text(PRINT_FAST3, "[%d] %s\n", i+1, menu_node->name);
  }
  return;
}

int perform_action(ActionKind action_kind, Player *player, MenuNode *choice) {
  switch (action_kind) {
    case ACTION_GO: {
      explore_room(player, choice->action.direction);
      destroy_menu(player->current_menu);
      player->current_menu = &main_menu;
      return 1;
    }
    case ACTION_BACK: {
      Menu *temp = player->current_menu;
      player->current_menu = player->current_menu->prev_menu;
      destroy_menu(temp);
      return 1;
    }
    case ACTION_QUIT: {
      print_text(PRINT_NORMAL5, "You open your eyes and realize it was just a dream.\n");
      return 0;
    }
    default:
    print_text(PRINT_NORMAL5, "You stare off into the distance...\n");
    return 1;
  }
};

MenuNode *parse_player_choice(Player *player, char *choice) {
  if (choice == NULL) {
    return NULL;
  }

  int choice_int = atoi(choice);

  if (choice_int == 0) {
    return NULL;
  }

  MenuNode *menu_node = player->current_menu->options[choice_int-1];
  return menu_node;
}

int playing(Player *player) {
  print_text(PRINT_FAST3, "Looping...\n");
  print_text(PRINT_FAST3, "Current Menu: %s\n", player->current_menu->name);
  display_menu(player->current_menu);
  char choice[32];
  read_input(choice, sizeof(choice));
  print_text(PRINT_FAST3, "Choice: %s\n", choice);
  MenuNode *menu_node = parse_player_choice(player, choice);
  if (menu_node == NULL) {
    print_text(PRINT_NORMAL5, "You stare off into the distance...\n");
    return 1;
  }
  NodeKind node_kind = menu_node->node_kind;

  switch (node_kind) {
    case NODE_MENU: {
      print_text(PRINT_FAST3, "Menu...\n");
      MenuKind menu_kind = menu_node->data_kind.menu_kind;
      Menu *new_menu = build_menu(menu_kind, player);
      new_menu->prev_menu = player->current_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case NODE_ACTION: {
      print_text(PRINT_FAST3, "Action...\n");
      ActionKind action_kind = menu_node->data_kind.action_kind;
      int result = perform_action(action_kind, player, menu_node);
      return result;
    }
    default:
      return 1;
  }
}
