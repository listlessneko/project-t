#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "entities.h"
#include "game.h"
#include "rooms.h"
#include "items.h"
#include "terminal.h"
#include "utils.h"

BaseMenu explore_option = {
  .menu_kind = MENU_EXPLORE,
  .name = { "Explore" },
  .description = { "Continue on your adventure." },
};

BaseMenu examine_option = {
  .menu_kind = MENU_EXAMINE,
  .name = { "Examine" },
  .description = { "Examine your surrounding or yourself." },
};

BaseMenu examine_room_option = {
  .menu_kind = MENU_EXAMINE_ROOM,
  .name = { "Examine room" },
  .description = { "Examine your surroundings." },
};

BaseMenu examine_inventory_option = {
  .menu_kind = MENU_EXAMINE_INVENTORY,
  .name = { "Examine inventory" },
  .description = { "Examine your items." },
};

BaseMenu examine_map_option = {
  .menu_kind = MENU_EXAMINE_MAP,
  .name = { "Examine map" },
  .description = { "Examine how far you have traveled." },
};

BaseMenu examine_stats_option = {
  .menu_kind = MENU_EXAMINE_STATS,
  .name = { "Examine stats" },
  .description = { "Examine how far you have grown." },
};

BaseMenu fight_option = {
  .menu_kind = MENU_FIGHT,
  .name = { "Fight" },
  .description = { "Eliminate the enemy." },
};

BaseAction back_option = {
  .action_kind = ACTION_BACK,
  .name = { "BACK" },
  .description = { "Back to previous menu." },
};

BaseAction quit_option = {
  .action_kind = ACTION_QUIT,
  .name = { "Quit" },
  .description = { "Return to reality." },
};

BaseRoom north_room = {
  .entity_kind = ENTITY_ROOM,
  .name = { "north" },
  .description = { "Explore north." },
};

BaseRoom east_room = {
  .entity_kind = ENTITY_ROOM,
  .name = { "east" },
  .description = { "Explore east." },
};

BaseRoom west_room = {
  .entity_kind = ENTITY_ROOM,
  .name = { "west" },
  .description = { "Explore west." },
};

BaseRoom south_room = {
  .entity_kind = ENTITY_ROOM,
  .name = { "south" },
  .description = { "Explore south." },
};

MenuNode explore_node = {
  .menu_node_kind = MENU_NODE_BASE_MENU,
  .data.base_menu = &explore_option,
};

MenuNode examine_node = {
  .menu_node_kind = MENU_NODE_BASE_MENU,
  .data.base_menu = &examine_option,
};

MenuNode examine_room_node = {
  .menu_node_kind = MENU_NODE_EXAMINE_ROOM,
  .data.base_menu = &examine_room_option,
};

MenuNode examine_inventory_node = {
  .menu_node_kind = MENU_NODE_EXAMINE_INVENTORY,
  .data.base_menu = &examine_inventory_option,
};

MenuNode examine_map_node = {
  .menu_node_kind = MENU_NODE_EXAMINE_MAP,
  .data.base_menu = &examine_map_option,
};

MenuNode examine_stats_node = {
  .menu_node_kind = MENU_NODE_EXAMINE_STATS,
  .data.base_menu = &examine_stats_option,
};

MenuNode fight_node = {
  .menu_node_kind = MENU_NODE_BASE_MENU,
  .data.base_menu = &fight_option,
};

MenuNode quit_node = {
  .menu_node_kind = MENU_NODE_QUIT,
  .data.base_action = &quit_option,
};

MenuNode back_node = {
  .menu_node_kind = MENU_NODE_BACK,
  .data.base_action = &back_option,
};

Menu main_menu = {
  .menu_kind = MENU_MAIN,
  .name = { "Main Menu" },
  .description = { "This is the main menu." },
  .count = 4,
  .options = {
    &explore_node,
    &examine_node,
    &fight_node,
    &quit_node
  }
};

MenuNode *build_menu_node(MenuNodeKind menu_node_kind, void *data) {
  MenuNode *menu_node = malloc(sizeof(MenuNode));
  if (menu_node == NULL) {
    return NULL;
  }

  menu_node->menu_node_kind = menu_node_kind;

  switch (menu_node_kind) {
    case MENU_NODE_EXPLORE: {
      BaseRoom *base_room = data;
      strncpy(menu_node->name, base_room->name, sizeof(menu_node->name));
      strncpy(menu_node->description, base_room->description, sizeof(menu_node->description));
      menu_node->data.room = base_room->room;
      break;
    }
    case MENU_NODE_EXAMINE_ROOM:
    case MENU_NODE_EXAMINE_INVENTORY: {
      menu_node->data.item = data;
      break;
    }
    case MENU_NODE_BACK:
    case MENU_NODE_QUIT: {
      menu_node->data.base_action = data;
      break;
    }
  }

  return menu_node;
};

void menu_realloc(Menu *menu, int count) {
  void *temp = realloc(menu, sizeof(Menu) + sizeof(MenuNode *) * count);
  if (temp == NULL) {
    return;
  }
  menu = temp;
  menu->count = count;
  return;
};

void display_menu(Menu *menu) {
  print_text(PRINT_NORMAL5, "%s\n", menu->name);
  print_text(PRINT_NORMAL5, "%s\n", menu->description);

  for (int i = 0; i < menu->count; i++) {
    MenuNode *menu_node = menu->options[i];
    MenuNodeKind menu_node_kind = menu_node->menu_node_kind;

    switch (menu_node_kind) {
      case MENU_NODE_BASE_MENU:
        print_text(PRINT_FAST3, "[%d] %s\n", i, menu_node->data.base_menu->name);
        break;
      case MENU_NODE_EXPLORE:
        if (menu_node->data.room != NULL) {
          print_text(PRINT_FAST3, "[%d] Go %s (%s)\n", i, menu_node->name, menu_node->data.room->name);
        } else {
          print_text(PRINT_FAST3, "[%d] Go %s \n", i, menu_node->name);
        }
        break;
      case MENU_NODE_EXAMINE:
        print_text(PRINT_FAST3, "[%d] Examine %s\n", i, menu_node->data.base_menu->name);
        break;
      case MENU_NODE_EXAMINE_ROOM:
        print_text(PRINT_FAST3, "[%d] Examine %s\n", i, menu_node->data.item->name);
        break;
      case MENU_NODE_EXAMINE_INVENTORY:
        print_text(PRINT_FAST3, "[%d] Examine %s\n", i, menu_node->data.item->name);
        break;
      case MENU_NODE_BACK:
      case MENU_NODE_QUIT:
        print_text(PRINT_FAST3, "[%d] %s\n", i, menu_node->data.base_action->name);
        break;
      default:
        break;
    }
  }
  return;
}

Menu *parse_player_choice(Player *player, Menu *menu, char *choice) {
  int choice_int = atoi(choice);

  MenuNode *menu_node = menu->options[choice_int-1];
  MenuNodeKind menu_node_kind = menu_node->menu_node_kind;

  switch (menu_node_kind) {
    case MENU_NODE_EXPLORE: {
      menu_realloc(menu, 5);
      int i = -1;
      Room *current_room = player->current_room;
      north_room.room = current_room->north;
      east_room.room = current_room->east;
      west_room.room = current_room->west;
      south_room.room = current_room->south;

      menu->options[i++] = build_menu_node(MENU_NODE_EXPLORE_ROOM, &north_room);
      menu->options[i++] = build_menu_node(MENU_NODE_EXPLORE_ROOM, &east_room);
      menu->options[i++] = build_menu_node(MENU_NODE_EXPLORE_ROOM, &west_room);
      menu->options[i++] = build_menu_node(MENU_NODE_EXPLORE_ROOM, &south_room);
      menu->options[i++] = &back_node;
    }
    case MENU_NODE_EXAMINE: {
      menu_realloc(menu, 5);
      int i = -1;
      menu->options[i++] = &examine_room_node;
      menu->options[i++] = &examine_inventory_node;
      menu->options[i++] = &examine_map_node;
      menu->options[i++] = &examine_stats_node;
      menu->options[i++] = &back_node;
    }

  }
return menu;
}
