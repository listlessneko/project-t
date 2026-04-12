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
  .node_kind = NODE_MENU_EXPLORE,
  .name = { "Explore" },
  .description = { "Continue on your adventure." },
};

MenuNode examine_node = {
  .node_kind = NODE_MENU_EXAMINE,
  .name = { "Examine" },
  .description = { "Examine your surrounding or yourself." },
};

MenuNode examine_room_node = {
  .node_kind = NODE_MENU_EXAMINE_ROOM,
  .name = { "Examine room" },
  .description = { "Examine your surroundings." },
};

MenuNode examine_inventory_node = {
  .node_kind = NODE_MENU_EXAMINE_INVENTORY,
  .name = { "Examine inventory" },
  .description = { "Examine your items." },
};

MenuNode examine_map_node = {
  .node_kind = NODE_MENU_EXAMINE_MAP,
  .name = { "Examine map" },
  .description = { "Examine how far you have traveled." },
};

MenuNode examine_stats_node = {
  .node_kind = NODE_MENU_EXAMINE_STATS,
  .name = { "Examine stats" },
  .description = { "Examine how far you have grown." },
};

MenuNode fight_node = {
  .node_kind = NODE_MENU_FIGHT,
  .name = { "Fight" },
  .description = { "Eliminate the enemy." },
};

MenuNode pick_up_node = {
  .node_kind = NODE_ACTION_PICK_UP,
  .name = { "Pick Up" },
  .description = { "Pick up item." },
};

MenuNode use_node = {
  .node_kind = NODE_ACTION_USE,
  .name = { "Use" },
  .description = { "Use item." },
};

MenuNode drop_node = {
  .node_kind = NODE_ACTION_DROP,
  .name = { "Drop" },
  .description = { "Drop item." },
};

MenuNode throw_away_node = {
  .node_kind = NODE_ACTION_THROW_AWAY,
  .name = { "Throw Away" },
  .description = { "Throw away item." },
};

MenuNode back_node = {
  .node_kind = NODE_ACTION_BACK,
  .name = { "BACK" },
  .description = { "Back to previous menu." },
};

MenuNode quit_node = {
  .node_kind = NODE_ACTION_QUIT,
  .name = { "Quit" },
  .description = { "Return to reality." },
};

Menu main_menu = {
  .name = { "Main Menu" },
  .description = { "This is the main menu." },
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

MenuNode *build_menu_node(NodeKind node_kind, void *data) {
  MenuNode *menu_node = malloc(sizeof(MenuNode));
  if (menu_node == NULL) {
    return NULL;
  }

  menu_node->node_kind = node_kind;

  switch (node_kind) {
    case NODE_MENU_EXAMINE_ROOM_ITEM:
    case NODE_MENU_EXAMINE_INVENTORY_ITEM: {
      menu_node->data.item = data;
      break;
    }
  }

  return menu_node;
};

MenuNode *build_room_menu_node(DirectionKind direction_kind, Room *room) {
  MenuNode *menu_node = malloc(sizeof(MenuNode));
  if (menu_node == NULL) {
    return NULL;
  }

  menu_node->node_kind = NODE_MENU_EXPLORE_ROOM;
  menu_node->data.room = room;

  if (room == NULL) {
    snprintf(menu_node->name, sizeof(menu_node->name), "%s", direction_to_string(direction_kind));
  } else {
    snprintf(menu_node->name, sizeof(menu_node->name), "%s (%s)", direction_to_string(direction_kind), room->name);
  }
  return menu_node;
};

Menu *menu_realloc(Menu *menu, int count) {
  void *temp = realloc(menu, sizeof(Menu) + sizeof(MenuNode *) * count);
  if (temp == NULL) {
    return NULL;
  }
  menu = temp;
  menu->options_count = count;
  return menu;
};

void destroy_menu_node(MenuNode *menu_node) {
  if (menu_node == NULL) {
    return;
  }
  free(menu_node);
}

void destroy_menu(Menu *menu) {
  if (menu == NULL) {
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
  print_text(PRINT_NORMAL5, "%s\n", menu->name);
  print_text(PRINT_NORMAL5, "%s\n", menu->description);

  for (int i = 0; i < menu->options_count; i++) {
    MenuNode *menu_node = menu->options[i];
    NodeKind node_kind = menu_node->node_kind;

    switch (node_kind) {
      case NODE_MENU_MAIN:
        print_text(PRINT_FAST3, "[%d] %s\n", i, menu_node->name);
        break;
      case NODE_MENU_EXPLORE:
        if (menu_node->data.room != NULL) {
          print_text(PRINT_FAST3, "[%d] Go %s (%s)\n", i, menu_node->name, menu_node->data.room->name);
        } else {
          print_text(PRINT_FAST3, "[%d] Go %s \n", i, menu_node->name);
        }
        break;
      case NODE_MENU_EXAMINE:
        print_text(PRINT_FAST3, "[%d] Examine %s\n", i, menu_node->name);
        break;
      case NODE_MENU_EXAMINE_ROOM:
        print_text(PRINT_FAST3, "[%d] Examine %s\n", i, menu_node->data.item->name);
        break;
      case NODE_MENU_EXAMINE_INVENTORY:
        print_text(PRINT_FAST3, "[%d] Examine %s\n", i, menu_node->data.item->name);
        break;
      case NODE_ACTION_BACK:
      case NODE_ACTION_QUIT:
        print_text(PRINT_FAST3, "[%d] %s\n", i, menu_node->name);
        break;
      default:
        break;
    }
  }
  return;
}

Menu *parse_player_choice(Player *player, Menu *current_menu, char *choice) {
  int choice_int = atoi(choice);

  MenuNode *menu_node = current_menu->options[choice_int-1];
  NodeKind node_kind = menu_node->node_kind;

  Menu *new_menu;

  switch (node_kind) {
    case NODE_MENU_EXPLORE: {
      Menu *new_menu = menu_realloc(current_menu, 5);
      int i = -1;
      Room *current_room = player->current_room;

      new_menu->options[i++] = build_room_menu_node(DIRECTION_NORTH, current_room->north);
      new_menu->options[i++] = build_room_menu_node(DIRECTION_EAST, current_room->east);
      new_menu->options[i++] = build_room_menu_node(DIRECTION_WEST, current_room->west);
      new_menu->options[i++] = build_room_menu_node(DIRECTION_SOUTH, current_room->south);
      new_menu->options[i++] = &back_node;
    }
    case NODE_MENU_EXAMINE: {
      Menu *new_menu = menu_realloc(current_menu, 5);
      int i = -1;
      new_menu->options[i++] = &examine_room_node;
      new_menu->options[i++] = &examine_inventory_node;
      new_menu->options[i++] = &examine_map_node;
      new_menu->options[i++] = &examine_stats_node;
      new_menu->options[i++] = &back_node;
    }
    case NODE_MENU_EXAMINE_ROOM: {
      Room *current_room = player->current_room;
      new_menu = menu_realloc(current_menu, current_room->items_count + 1);
      int i = 0;
      for (i = 0; i < current_room->items_count; i++) {
        new_menu->options[i] = build_menu_node(NODE_MENU_EXAMINE_ROOM_ITEM, current_room->items[i]);
      }
      new_menu->options[i] = &back_node;
    }
    case NODE_MENU_EXAMINE_INVENTORY: {
      new_menu = menu_realloc(current_menu, player->inventory_count + 1);
      int i = 0;
      for (i = 0; i < player->inventory_count; i++) {
        new_menu->options[i] = build_menu_node(NODE_MENU_EXAMINE_INVENTORY_ITEM, player->inventory[i]);
      }
      new_menu->options[i] = &back_node;
    }
    case NODE_MENU_EXAMINE_INVENTORY_ITEM: {
      new_menu = menu_realloc(current_menu, 5);
      int i = 0;
      for (i = 0; i < player->inventory_count; i++) {
        new_menu->options[i] = build_menu_node(NODE_MENU_EXAMINE_INVENTORY_ITEM, player->inventory[i]);
      }
      new_menu->options[i] = &back_node;
    }
    case NODE_MENU_EXAMINE_MAP: {
      new_menu = menu_realloc(current_menu, 1);
      new_menu->options[0] = &back_node;
    }
    case NODE_MENU_EXAMINE_STATS: {
      new_menu = menu_realloc(current_menu, 1);
      new_menu->options[0] = &back_node;
    }
    case NODE_ACTION_BACK: {
      new_menu = current_menu->prev_menu;
    }
  }
  new_menu->prev_menu = current_menu;
  return new_menu;
}
