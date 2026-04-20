#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
  .key = 'E',
  .is_static = 1,
};

MenuNode view_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_VIEW,
  .name = { "View" },
  .description = { "View your surrounding or yourself." },
  .key = 'V',
  .is_static = 1,
};

MenuNode view_room_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_VIEW_ROOM,
  .name = { "Area" },
  .description = { "View your surroundings." },
  .key = 'A',
  .is_static = 1,
};

MenuNode view_inventory_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_VIEW_INVENTORY,
  .name = { "Inventory" },
  .description = { "View your items." },
  .key = 'I',
  .is_static = 1,
};

MenuNode view_map_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_VIEW_MAP,
  .name = { "Map" },
  .description = { "View how far you have traveled." },
  .key = 'M',
  .is_static = 1,
};

MenuNode view_stats_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_VIEW_STATS,
  .name = { "Stats" },
  .description = { "View how far you have grown." },
  .key = 'S',
  .is_static = 1,
};

MenuNode fight_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_FIGHT,
  .name = { "Fight" },
  .description = { "Eliminate the enemy." },
  .key = 'F',
  .is_static = 1,
};

MenuNode pick_up_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_PICK_UP,
  .name = { "Pick Up" },
  .description = { "Pick up item." },
  .key = 'E',
  .is_static = 1,
};

MenuNode use_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_USE,
  .name = { "Use" },
  .description = { "Use item." },
  .key = 'E',
  .is_static = 1,
};

MenuNode drop_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_DROP,
  .name = { "Drop" },
  .description = { "Drop item." },
  .key = 'D',
  .is_static = 1,
};

MenuNode throw_away_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_THROW_AWAY,
  .name = { "Throw Away" },
  .description = { "Throw away item." },
  .key = 'T',
  .is_static = 1,
};

MenuNode prev_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_PREVIOUS,
  .name = { "Previous " },
  .description = { "Back to previous page." },
  .key = 'P',
  .is_static = 1,
};

MenuNode next_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_NEXT,
  .name = { "Next " },
  .description = { "Go to next page." },
  .key = 'N',
  .is_static = 1,
};

MenuNode back_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_BACK,
  .name = { "Back\n" },
  .description = { "Back to previous menu." },
  .key = 'B',
  .is_static = 1,
};

MenuNode quit_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_QUIT,
  .name = { "Quit" },
  .description = { "Return to reality." },
  .key = 'Q',
  .is_static = 1,
};

Menu main_menu = {
  .name = { "Main Menu" },
  .description = { "This is the main menu." },
  .is_static = 1,
  .prev_menu = NULL,
  .prev_page = NULL,
  .next_page = NULL,
  .node_count = 4,
  .nodes = {
    &explore_node,
    &view_node,
    &fight_node,
    &quit_node
  }
};

Menu view_menu = {
  .name = { "View" },
  .description = { "This is the view menu." },
  .prev_menu = &main_menu,
  .is_static = 1,
  .prev_page = NULL,
  .next_page = NULL,
  .node_count = 5,
  .nodes = {
    &view_room_node,
    &view_inventory_node,
    &view_map_node,
    &view_stats_node,
    &back_node
  }
};

MenuNode *build_view_item_menu_node(MenuKind menu_kind, Item *item) {
  MenuNode *menu_node = malloc(sizeof(MenuNode));
  if (menu_node == NULL) {
    return NULL;
  }

  menu_node->node_kind = NODE_MENU;
  menu_node->data_kind.menu_kind = menu_kind;
  menu_node->data.item = item;
  menu_node->key = '\0';

  snprintf(menu_node->name, sizeof(menu_node->name), "%s", item->name);
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
  menu_node->key = direction_to_char(direction_kind);

  if (room == NULL) {
    snprintf(menu_node->name, sizeof(menu_node->name), "%s (???)", direction_to_string(direction_kind));
  } else {
    snprintf(menu_node->name, sizeof(menu_node->name), "%s (%s)", direction_to_string(direction_kind), room->name);
  }
  return menu_node;
};

Menu *menu_malloc(int node_count) {
  Menu *menu = malloc(sizeof(Menu) + sizeof(MenuNode *) * node_count);
  if (menu == NULL) {
    return NULL;
  }
  menu->prev_menu = NULL;
  menu->next_page = NULL;
  menu->prev_page = NULL;
  menu->is_static = 0;
  menu->node_count = node_count;
  return menu;
};

void destroy_menu_node(MenuNode *menu_node) {
  if (menu_node == NULL || menu_node->is_static) {
    return;
  }
  free(menu_node);
}

Menu *build_menu(MenuKind menu_kind, Player *player) {
  print_text(PRINT_FAST3, "Building menu...\n");

  Menu *new_menu;

  switch (menu_kind) {
    case MENU_MAIN: {
      return new_menu = &main_menu;
    }
    case MENU_EXPLORE: {
      new_menu = menu_malloc(5);
      strncpy(new_menu->name, "Explore Menu", sizeof(new_menu->name) - 1);
      new_menu->name[31] = '\0';
      print_text(PRINT_FAST3, "%s\n", new_menu->name);
      Room *current_room = player->current_room;
      Map *map = player->map;
      new_menu->nodes[0] = build_explore_room_menu_node(DIRECTION_NORTH, map->grid[current_room->x][current_room->y + 1]);
      new_menu->nodes[1] = build_explore_room_menu_node(DIRECTION_EAST, map->grid[current_room->x + 1][current_room->y]);
      new_menu->nodes[2] = build_explore_room_menu_node(DIRECTION_WEST, map->grid[current_room->x - 1][current_room->y]);
      new_menu->nodes[3] = build_explore_room_menu_node(DIRECTION_SOUTH, map->grid[current_room->x][current_room->y - 1]);
      new_menu->nodes[4] = &back_node;
      break;
    }
    case MENU_VIEW: {
      return new_menu = &view_menu;
    }
    case MENU_VIEW_ROOM: {
      Room *current_room = player->current_room;
      new_menu = menu_malloc(current_room->items_count + 1);
      int i = 0;
      for (i = 0; i < current_room->items_count; i++) {
        new_menu->nodes[i] = build_view_item_menu_node(MENU_VIEW_ROOM_ITEM, current_room->items[i]);
      }
      new_menu->nodes[i] = &back_node;
      break;
    }
    case MENU_VIEW_INVENTORY: {
      int item_limit = 5;
      int nav_options = 3;
      int current_item = 0;
      int remaining = player->inventory_count - current_item;
      int page_size = remaining > item_limit ? item_limit : remaining;
      int sub_pages = (player->inventory_count + item_limit - 1) / item_limit;
      int current_sub_page = 1;

      Menu *next_page;
      new_menu = menu_malloc(page_size + nav_options);
      snprintf(new_menu->name, sizeof(new_menu->name), "Inventory:\n (Page %d of %d)", current_sub_page, sub_pages);
      new_menu->name[63] = '\0';
      Menu *first_page = new_menu;
      int i;
      for (i = 0; i < page_size; i++) {
        new_menu->nodes[i] = build_view_item_menu_node(MENU_VIEW_INVENTORY_ITEM, player->inventory[current_item]);
        current_item++;
      }
      new_menu->nodes[i++] = &prev_node;
      new_menu->nodes[i++] = &next_node;
      new_menu->nodes[i++] = &back_node;
      new_menu->prev_menu = player->current_menu;

      while (current_sub_page < sub_pages) {
        current_sub_page++;
        remaining = player->inventory_count - current_item;
        page_size = remaining > item_limit ? item_limit : remaining;
        next_page = menu_malloc(page_size + nav_options);
        snprintf(next_page->name, sizeof(next_page->name), "Inventory:\n (Page %d of %d)", current_sub_page, sub_pages);
        int j;
        for (j = 0; j < page_size; j++) {
          next_page->nodes[j] = build_view_item_menu_node(MENU_VIEW_INVENTORY_ITEM, player->inventory[current_item]);
          current_item++;
        }
        next_page->nodes[j++] = &prev_node;
        next_page->nodes[j++] = &next_node;
        next_page->nodes[j++] = &back_node;
        next_page->prev_menu = player->current_menu;
        new_menu->next_page = next_page;
        next_page->prev_page = new_menu;
        new_menu = next_page;
      }
      new_menu->next_page = first_page;
      first_page->prev_page = new_menu;
      new_menu = first_page;
      break;
    }
    default: {
      new_menu = menu_malloc(1);
      strncpy(new_menu->name, "Empty Menu", sizeof(new_menu->name) - 1);
      new_menu->nodes[0] = &back_node;
      break;
    }
  }

  return new_menu;
}

void destroy_menu_pages(Menu *menu, Menu *first_page) {
  if (menu == NULL || menu == first_page) {
    return;
  }

  for (int i = 0; i < menu->node_count; i++) {
    destroy_menu_node(menu->nodes[i]);
  }
  
  destroy_menu_pages(menu->next_page, first_page);
  free(menu);
}

void destroy_menu(Menu *menu) {
  print_text(PRINT_FAST3, "Destroying menu: %s\n", menu->name);
  if (menu == NULL || menu->is_static) {
    return;
  }

  for (int i = 0; i < menu->node_count; i++) {
    destroy_menu_node(menu->nodes[i]);
  }

  if (menu->next_page != NULL) {
    destroy_menu_pages(menu->next_page, menu);
  }
  free(menu);
}

void display_menu(Menu *menu) {
  print_text(PRINT_NORMAL5, "%s\n", menu->name);
  /*print_text(PRINT_NORMAL5, "%s\n", menu->description);*/

  int offset = 0;
  for (int k = 0; k < menu->node_count; k++) {
    MenuNode *menu_node = menu->nodes[k];
    if (menu_node->key == '\0') {
      offset += snprintf(menu->options + offset, sizeof(menu->options) - offset, "[%d] %s\n", k+1, menu_node->name);
    } else if (
      menu_node->node_kind == NODE_ACTION && (
      menu_node->data_kind.action_kind == ACTION_NEXT ||
      menu_node->data_kind.action_kind == ACTION_PREVIOUS ||
      menu_node->data_kind.action_kind == ACTION_BACK
      )
    ) {
      offset += snprintf(menu->options + offset, sizeof(menu->options) - offset, "[%c]%s", menu_node->key, menu_node->name+1);
    } else {
      offset += snprintf(menu->options + offset, sizeof(menu->options) - offset, "[%c]%s\n", menu_node->key, menu_node->name+1);
    }
  }

  print_text(PRINT_NORMAL5, "%s", menu->options);
  return;
}

int perform_action(ActionKind action_kind, Player *player, MenuNode *choice) {
  switch (action_kind) {
    case ACTION_GO: {
      explore_room(player, choice->action.direction);
      destroy_menu(player->current_menu);
      Menu *new_menu = build_menu(MENU_EXPLORE, player);
      new_menu->prev_menu = &main_menu;
      player->current_menu = new_menu;
      return 1;
    }
    /*case ACTION_PICK_UP:*/
    /*case ACTION_USE:*/
    /*case ACTION_DROP:*/
    /*case ACTION_THROW_AWAY:*/
    case ACTION_PREVIOUS: {
      player->current_menu = player->current_menu->prev_page;
      return 1;
    }
    case ACTION_NEXT: {
      player->current_menu = player->current_menu->next_page;
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
  if (choice == NULL || *choice == '\0') {
    return NULL;
  }

  MenuNode *menu_node = NULL;

  int choice_int = atoi(choice);

  if (choice_int > 0 && choice_int <= player->current_menu->node_count) {
    menu_node = player->current_menu->nodes[choice_int-1];
  } else {
    for (int i = 0; i < player->current_menu->node_count; i++) {
      MenuNode *current_option = player->current_menu->nodes[i];
      if (toupper(*choice) == current_option->key) {
        menu_node = current_option;
        break;
      }
    }
  }

  return menu_node;
}

int playing(Player *player) {
  print_text(PRINT_FAST3, "(Looping...)\n");
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
      print_text(PRINT_FAST3, "Selected: Menu\n");
      MenuKind menu_kind = menu_node->data_kind.menu_kind;
      Menu *new_menu = build_menu(menu_kind, player);
      new_menu->prev_menu = player->current_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case NODE_ACTION: {
      print_text(PRINT_FAST3, "Selected: Action\n");
      ActionKind action_kind = menu_node->data_kind.action_kind;
      int result = perform_action(action_kind, player, menu_node);
      return result;
    }
    default:
      return 1;
  }
}
