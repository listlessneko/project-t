#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "entities.h"
#include "status.h"
#include "game.h"
#include "rooms.h"
#include "items.h"
#include "inventory.h"
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

MenuNode view_equipment_node = {
  .node_kind = NODE_MENU,
  .data_kind.menu_kind = MENU_VIEW_EQUIPMENT,
  .name = { "Equipment" },
  .description = { "View your equipment." },
  .key = 'E',
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
  .data_kind.action_kind = ACTION_PICK_UP_ITEM,
  .name = { "Pick Up" },
  .description = { "Pick up item." },
  .key = 'P',
  .is_static = 1,
};

MenuNode use_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_USE_ITEM,
  .name = { "Use" },
  .description = { "Use item." },
  .key = 'U',
  .is_static = 1,
};

MenuNode equip_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_EQUIP_ITEM,
  .name = { "Equip" },
  .description = { "Equip item." },
  .key = 'E',
  .is_static = 1,
};

MenuNode unequip_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_UNEQUIP_ITEM,
  .name = { "Unequip" },
  .description = { "Unequip item." },
  .key = 'U',
  .is_static = 1,
};

MenuNode swap_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_SWAP_EQUIPMENT,
  .name = { "Swap" },
  .description = { "Swap equipment." },
  .key = 'S',
  .is_static = 1,
};

MenuNode drop_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_DROP_ITEM,
  .name = { "Drop" },
  .description = { "Drop item." },
  .key = 'D',
  .is_static = 1,
};

MenuNode throw_away_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_THROW_AWAY_ITEM,
  .name = { "Throw Away" },
  .description = { "Throw away item." },
  .key = 'T',
  .is_static = 1,
};

MenuNode prev_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_PREVIOUS_PAGE,
  .name = { "Previous " },
  .description = { "Back to previous page." },
  .key = 'P',
  .is_static = 1,
};

MenuNode next_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_NEXT_PAGE,
  .name = { "Next " },
  .description = { "Go to next page." },
  .key = 'N',
  .is_static = 1,
};

MenuNode back_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_BACK_MENU,
  .name = { "Back\n" },
  .description = { "Back to previous menu." },
  .key = 'B',
  .is_static = 1,
};

MenuNode yes_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_YES,
  .name = { "Yes" },
  .description = { "Confirm action." },
  .key = 'Y',
  .is_static = 1,
};

MenuNode no_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_NO,
  .name = { "No" },
  .description = { "Back to previous menu." },
  .key = 'N',
  .is_static = 1,
};

MenuNode quit_node = {
  .node_kind = NODE_ACTION,
  .data_kind.action_kind = ACTION_QUIT_GAME,
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
  .node_count = 6,
  .nodes = {
    &view_room_node,
    &view_inventory_node,
    &view_equipment_node,
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

  menu_node->node_kind = NODE_MENU_ITEM;
  menu_node->data_kind.menu_kind = menu_kind;
  menu_node->data.item = item;
  menu_node->key = '\0';

  snprintf(menu_node->name, sizeof(menu_node->name), "%s", item->name);
  return menu_node;
}

MenuNode *build_view_equipment_menu_node(ItemKind item_kind, Item *item) {
  MenuNode *menu_node = malloc(sizeof(MenuNode));
  if (menu_node == NULL) {
    return NULL;
  }

  menu_node->node_kind = NODE_MENU_ITEM;
  menu_node->data_kind.menu_kind = MENU_VIEW_EQUIPPED_ITEM;
  menu_node->data.item = item;
  menu_node->key = item_kind_name(item_kind)[0];

  if (item == NULL) {
    snprintf(menu_node->name, sizeof(menu_node->name), "%s: None", item_kind_name(item_kind));
  } else {
    snprintf(menu_node->name, sizeof(menu_node->name), "%s: %s", item_kind_name(item->kind), item->name);
  }
  return menu_node;
}

MenuNode *build_explore_room_menu_node(DirectionKind direction_kind, Room *room) {
  MenuNode *menu_node = malloc(sizeof(MenuNode));
  if (menu_node == NULL) {
    return NULL;
  }

  menu_node->node_kind = NODE_ACTION;
  menu_node->data_kind.action_kind = ACTION_GO_EXPLORE_ROOM;
  menu_node->data.room = room;
  menu_node->action.direction = direction_kind;
  menu_node->key = direction_to_char(direction_kind);

  if (room == NULL) {
    snprintf(menu_node->name, sizeof(menu_node->name), "%s (\?\?\?)", direction_to_string(direction_kind));
  } else {
    snprintf(menu_node->name, sizeof(menu_node->name), "%s (%s)", direction_to_string(direction_kind), room->name);
  }
  return menu_node;
}

void build_map(Player *player, Menu *menu) {
  if (player == NULL || menu == NULL) {
    return;
  }

  Map *adventure_map = player->map;
  char map_str[MAX_MAP_STR_SIZE];

  int offset = 0;
  offset += snprintf(map_str + offset, sizeof(map_str) - offset, "    ");
  for (int w = 0; w < MAX_AREA_WIDTH; w++) {
    offset += snprintf(map_str + offset, sizeof(map_str) - offset, " %d  ", w);
  }
  offset += snprintf(map_str + offset, sizeof(map_str) - offset, "\n");

  offset += snprintf(map_str + offset, sizeof(map_str) - offset, "    ");
  for (int h = 0; h < MAX_AREA_HEIGHT; h++) {
    offset += snprintf(map_str + offset, sizeof(map_str) - offset, "----");
  }
  offset += snprintf(map_str + offset, sizeof(map_str) - offset, "\n");

  for (int y = 0; y < MAX_AREA_WIDTH; y++) {
    offset += snprintf(map_str + offset, sizeof(map_str) - offset, " %d |", y);
    for (int x = 0; x < MAX_AREA_HEIGHT; x++) {
      Room *current_room = adventure_map->grid[x][y];
      char symbol = '?';
      if (current_room == NULL) {
        symbol = '?';
      } else if (current_room->id == player->current_room->id) {
        symbol = '@';
      } else if (current_room->items_count > 0 && current_room->visited) {
        symbol = '!';
      } else if (current_room->visited) {
        symbol = '*';
      } else if (current_room->kind == ROOM_BARRIER) {
        symbol = '#';
      }
      offset += snprintf(map_str + offset, sizeof(map_str) - offset, " %c |", symbol);
    }
    offset += snprintf(map_str + offset, sizeof(map_str) - offset, "\n");
    offset += snprintf(map_str + offset, sizeof(map_str) - offset, "    ");
    for (int h = 0; h < MAX_AREA_HEIGHT; h++) {
      offset += snprintf(map_str + offset, sizeof(map_str) - offset, "----");
    }
    offset += snprintf(map_str + offset, sizeof(map_str) - offset, "\n");
  }
  print_text(PRINT_NORMAL5, "Current Position: %d, %d\n", player->current_room->x, player->current_room->y);
  print_text(PRINT_NORMAL5, "%s", map_str);
}

Menu *menu_malloc(int node_count) {
  Menu *menu = malloc(sizeof(Menu) + sizeof(MenuNode *) * node_count);
  if (menu == NULL) {
    return NULL;
  }
  memset(menu->name, 0, sizeof(menu->name));
  memset(menu->description, 0, sizeof(menu->description));
  memset(menu->options, 0, sizeof(menu->options));
  menu->prev_menu = NULL;
  menu->next_page = NULL;
  menu->prev_page = NULL;
  menu->is_static = 0;
  menu->node_count = node_count;
  return menu;
}

void destroy_menu_node(MenuNode *menu_node) {
  if (menu_node == NULL || menu_node->is_static) {
    return;
  }
  free(menu_node);
}

Menu *build_menu(MenuKind menu_kind, Player *player) {
  if (player == NULL) {
    return NULL;
  }

  Menu *new_menu;

  switch (menu_kind) {
    case MENU_MAIN: {
      return new_menu = &main_menu;
    }
    case MENU_EXPLORE: {
      new_menu = menu_malloc(5);
      new_menu->menu_kind = menu_kind;
      new_menu->name[31] = '\0';
      Room *current_room = player->current_room;
      Map *map = player->map;

      Room *north_room = current_room->y - 1 < 0 ? NULL : map->grid[current_room->x][current_room->y - 1];
      Room *east_room = current_room->x + 1 >= MAX_AREA_WIDTH ? NULL : map->grid[current_room->x + 1][current_room->y];
      Room *west_room = current_room->x - 1 < 0 ? NULL : map->grid[current_room->x - 1][current_room->y];
      Room *south_room = current_room->y + 1 >= MAX_AREA_HEIGHT ? NULL : map->grid[current_room->x][current_room->y + 1];

      new_menu->nodes[0] = build_explore_room_menu_node(DIRECTION_NORTH, north_room);
      new_menu->nodes[1] = build_explore_room_menu_node(DIRECTION_EAST, east_room);
      new_menu->nodes[2] = build_explore_room_menu_node(DIRECTION_WEST, west_room);
      new_menu->nodes[3] = build_explore_room_menu_node(DIRECTION_SOUTH, south_room);
      new_menu->nodes[4] = &back_node;
      break;
    }
    case MENU_VIEW: {
      return new_menu = &view_menu;
    }
    case MENU_VIEW_ROOM: {
      Room *current_room = player->current_room;
      new_menu = menu_malloc(current_room->items_count + 1);
      new_menu->menu_kind = menu_kind;
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
      new_menu->menu_kind = menu_kind;
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
        next_page->menu_kind = menu_kind;
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
    case MENU_VIEW_EQUIPMENT: {
      int node_count = 4;
      new_menu = menu_malloc(node_count);
      new_menu->menu_kind = menu_kind;
      strncpy(new_menu->name, "Equipment", sizeof(new_menu->name) - 1);

      new_menu->nodes[0] = build_view_equipment_menu_node(ITEM_WEAPON, player->weapon);
      new_menu->nodes[1] = build_view_equipment_menu_node(ITEM_SHIELD, player->shield);
      new_menu->nodes[2] = build_view_equipment_menu_node(ITEM_ACCESSORY, player->accessory);
      new_menu->nodes[3] = &back_node;
      break;
    }
    case MENU_FIND_INVENTORY_ITEM_TO_SWAP: {
      new_menu = menu_malloc(2);
      new_menu->menu_kind = menu_kind;
      strncpy(new_menu->name, "Inventory Full", sizeof(new_menu->name) - 1);
      new_menu->name[127] = '\0';
      strncpy(new_menu->description, "Find an inventory item to swap with.", sizeof(new_menu->description) - 1);
      new_menu->description[515] = '\0';

      MenuNode *yes_node = malloc(sizeof(MenuNode));
      yes_node->node_kind = NODE_MENU;
      yes_node->data_kind.menu_kind = MENU_SWAP_VIEW_INVENTORY;
      strncpy(yes_node->name, "Yes", sizeof(yes_node->name) - 1);
      yes_node->name[127] = '\0';
      yes_node->key = 'Y';

      new_menu->nodes[0] = yes_node;
      new_menu->nodes[1] = &no_node;
      break;
    }
    case MENU_SWAP_VIEW_INVENTORY: {
      int item_limit = 5;
      int nav_options = 3;
      int current_item = 0;
      int **filtered_count = 0;
      Item **filtered = filtered_inventory(player, player->current_menu->item->kind, *filtered_count);
      int remaining = **filtered_count - current_item;
      int page_size = remaining > item_limit ? item_limit : remaining;
      int sub_pages = (**filtered_count + item_limit - 1) / item_limit;
      int current_sub_page = 1;

      Menu *next_page;
      new_menu = menu_malloc(page_size + nav_options);
      new_menu->menu_kind = menu_kind;
      snprintf(new_menu->name, sizeof(new_menu->name), "Inventory:\n (Page %d of %d)", current_sub_page, sub_pages);
      new_menu->name[63] = '\0';
      Menu *first_page = new_menu;
      int i;
      for (i = 0; i < page_size; i++) {
        new_menu->nodes[i] = build_view_item_menu_node(MENU_SWAP_WITH_EQUIPPED_ITEM, filtered[current_item]);
        current_item++;
      }
      new_menu->nodes[i++] = &prev_node;
      new_menu->nodes[i++] = &next_node;
      new_menu->nodes[i++] = &back_node;
      new_menu->prev_menu = player->current_menu->prev_menu->prev_menu;

      while (current_sub_page < sub_pages) {
        current_sub_page++;
        remaining = **filtered_count - current_item;
        page_size = remaining > item_limit ? item_limit : remaining;
        next_page = menu_malloc(page_size + nav_options);
        next_page->menu_kind = menu_kind;
        snprintf(next_page->name, sizeof(next_page->name), "Inventory:\n (Page %d of %d)", current_sub_page, sub_pages);
        int j;
        for (j = 0; j < page_size; j++) {
          next_page->nodes[j] = build_view_item_menu_node(MENU_SWAP_WITH_EQUIPPED_ITEM, filtered[current_item]);
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
    case MENU_VIEW_MAP: {
      new_menu = menu_malloc(1);
      new_menu->menu_kind = menu_kind;
      strncpy(new_menu->name, "Map", sizeof(new_menu->name) - 1);
      new_menu->nodes[0] = &back_node;
      break;
    }
    case MENU_CONFIRM: {
      new_menu = menu_malloc(2);

      strncpy(new_menu->name, "Confirm?", sizeof(new_menu->name)-1);
      new_menu->name[127] = '\0';
      new_menu->menu_kind = menu_kind;
      new_menu->nodes[0] = &yes_node;
      new_menu->nodes[1] = &no_node;
    }
    default: {
      new_menu = menu_malloc(1);
      new_menu->menu_kind = menu_kind;
      strncpy(new_menu->name, "Empty Menu", sizeof(new_menu->name) - 1);
      new_menu->nodes[0] = &back_node;
      break;
    }
  }
  return new_menu;
}

Menu *build_item_menu(MenuKind menu_kind, Item *item) {
  Menu *new_menu;

  switch (menu_kind) {
    case MENU_VIEW_ROOM_ITEM: {
      new_menu = menu_malloc(3);
      snprintf(new_menu->name, sizeof(new_menu->name), "%s", item->name);
      snprintf(new_menu->description, sizeof(new_menu->description), "%s", item->description);
      new_menu->menu_kind = menu_kind;

      new_menu->nodes[0] = &pick_up_node;
      new_menu->nodes[1] = &use_node;
      new_menu->nodes[2] = &back_node;
      break;
    }
    case MENU_SWAP_WITH_INVENTORY_ITEM: {
      new_menu = menu_malloc(2);
      strncpy(new_menu->name, "Swap with this item?", sizeof(new_menu->name) - 1);
      new_menu->name[127] = '\0';

      MenuNode *yes_node = malloc(sizeof(MenuNode));
      yes_node->node_kind = NODE_ACTION;
      yes_node->data_kind.action_kind = ACTION_YES;
      strncpy(yes_node->name, "Yes", sizeof(yes_node->name) - 1);
      yes_node->key = 'Y';

      new_menu->nodes[0] = yes_node;
      new_menu->nodes[1] = &no_node;
    }
    case MENU_VIEW_INVENTORY_ITEM: {

      switch (item->kind) {
        case ITEM_WEAPON:
        case ITEM_SHIELD:
        case ITEM_ACCESSORY: {
          new_menu = menu_malloc(4);
          new_menu->item = item;
          snprintf(new_menu->name, sizeof(new_menu->name), "%s", item->name);
          snprintf(new_menu->description, sizeof(new_menu->description), "%s", item->description);
          new_menu->menu_kind = menu_kind;

          new_menu->nodes[0] = &equip_node;
          new_menu->nodes[1] = &drop_node;
          new_menu->nodes[2] = &throw_away_node;
          new_menu->nodes[3] = &back_node;
          break;
        }
        case ITEM_POTION: {
          new_menu = menu_malloc(4);
          new_menu->item = item;
          snprintf(new_menu->name, sizeof(new_menu->name), "%s", item->name);
          snprintf(new_menu->description, sizeof(new_menu->description), "%s", item->description);
          new_menu->menu_kind = menu_kind;

          new_menu->nodes[0] = &use_node;
          new_menu->nodes[1] = &drop_node;
          new_menu->nodes[2] = &throw_away_node;
          new_menu->nodes[3] = &back_node;
          break;
        }
        default:
          new_menu = menu_malloc(1);
          new_menu->item = item;
          snprintf(new_menu->name, sizeof(new_menu->name), "%s", item->name);
          snprintf(new_menu->description, sizeof(new_menu->description), "%s", item->description);
          new_menu->menu_kind = menu_kind;
          new_menu->nodes[0] = &back_node;
          break;
      }
      break;
    }
    case MENU_VIEW_EQUIPPED_ITEM: {
      if (item == NULL) {
        new_menu = NULL;
        print_text(PRINT_FAST3, "You're grasping at air.\n");
        break;
      }
      new_menu = menu_malloc(2);
      new_menu->item = item;
      snprintf(new_menu->name, sizeof(new_menu->name), "%s", item->name);
      snprintf(new_menu->description, sizeof(new_menu->description), "%s", item->description);
      new_menu->menu_kind = menu_kind;
      new_menu->nodes[0] = &swap_node;
      new_menu->nodes[1] = &unequip_node;
      new_menu->nodes[2] = &back_node;
      break;
    }
    case MENU_VIEW_UNEQUIPPED_ITEM: {
      new_menu = menu_malloc(2);
      new_menu->item = item;
      snprintf(new_menu->name, sizeof(new_menu->name), "%s", item->name);
      snprintf(new_menu->description, sizeof(new_menu->description), "%s", item->description);
      new_menu->menu_kind = menu_kind;
      new_menu->nodes[0] = &equip_node;
      new_menu->nodes[1] = &back_node;
      break;
    }
    default:
      new_menu = menu_malloc(1);
      new_menu->item = item;
      snprintf(new_menu->name, sizeof(new_menu->name), "%s", item->name);
      snprintf(new_menu->description, sizeof(new_menu->description), "%s", item->description);
      new_menu->menu_kind = menu_kind;
      new_menu->nodes[0] = &back_node;
      break;
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

void display_menu(Player *player) {
  Menu *menu = player->current_menu;
  print_text(PRINT_NORMAL5, "%s\n", menu->name);
  print_text(PRINT_NORMAL5, "%s\n", menu->description);

  MenuKind menu_kind = menu->menu_kind;
  switch (menu_kind) {
    case MENU_VIEW_MAP: {
      build_map(player, menu);
      break;
    }
    default: {
      int offset = 0;
      for (int k = 0; k < menu->node_count; k++) {
        MenuNode *menu_node = menu->nodes[k];
        if (menu_node->key == '\0') {
          offset += snprintf(menu->options + offset, sizeof(menu->options) - offset, "[%d] %s\n", k+1, menu_node->name);
        } else if (
          menu_node->node_kind == NODE_ACTION && (
          menu_node->data_kind.action_kind == ACTION_NEXT_PAGE ||
          menu_node->data_kind.action_kind == ACTION_PREVIOUS_PAGE ||
          menu_node->data_kind.action_kind == ACTION_BACK_MENU
        )
        ) {
          offset += snprintf(menu->options + offset, sizeof(menu->options) - offset, "[%c]%s", menu_node->key, menu_node->name+1);
        } else {
          offset += snprintf(menu->options + offset, sizeof(menu->options) - offset, "[%c]%s\n", menu_node->key, menu_node->name+1);
        }
      }
      print_text(PRINT_NORMAL5, "%s", menu->options);
      break;
    }
  }

  return;
}

int perform_action(ActionKind action_kind, Player *player, MenuNode *choice) {
  MenuKind prev_menu_kind = player->current_menu->prev_menu->menu_kind;
  Room *current_room = player->current_room;
  Item *current_item = player->current_menu->item;

  switch (action_kind) {
    case ACTION_GO_EXPLORE_ROOM: {
      explore_room(player, choice->action.direction);
      destroy_menu(player->current_menu);
      Menu *new_menu = build_menu(MENU_EXPLORE, player);
      new_menu->prev_menu = &main_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case ACTION_PICK_UP_ITEM: {
      int added_to_inventory = add_item_to_player_inventory(player, current_item);
      if (added_to_inventory == INVENTORY_ITEMS_FULL) {
        print_text(PRINT_NORMAL5, "You're already carrying the weight of the world. Do you need to add any more?\n");
      } else if (added_to_inventory == ITEM_ADD_TO_INVENTORY_INVALID || added_to_inventory == ITEM_ADD_TO_INVENTORY_ERROR) {
        print_text(PRINT_NORMAL5, "Unable to place item in inventory\n");
      } else if (added_to_inventory == ITEM_ADD_TO_INVENTORY_SUCCESS) {
        int removed_from_room = remove_item_from_room(current_room, current_item);
        if (removed_from_room == ITEM_REMOVE_FROM_ROOM_INVALID || removed_from_room == ITEM_ADD_TO_INVENTORY_ERROR) {
          remove_item_from_player_inventory(player, current_item);
          print_text(PRINT_NORMAL5, "Unable to pick up item from ground\n");
        } else if (removed_from_room == ITEM_REMOVE_FROM_INVENTORY_SUCCESS) {
          print_text(PRINT_NORMAL5, "Picked up %s", current_item->name);
        }
      }
      destroy_menu(player->current_menu);
      Menu *new_menu = build_menu(MENU_VIEW_ROOM, player);
      new_menu->prev_menu = &view_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case ACTION_EQUIP_ITEM: {
      int equipped_item = equip_item(player, current_item);

      switch (equipped_item) {
        case ITEM_EQUIP_INVALID:
        case ITEM_EQUIP_ERROR:
          print_text(PRINT_NORMAL5, "Unable to equip item\n");
          break;
        case ITEM_SLOT_ALREADY_EQUIPPED: {
          Menu *new_menu = build_menu(MENU_CONFIRM, player);
          new_menu->prev_menu = player->current_menu;
          player->current_menu = new_menu;
          return 1;
        }
        case ITEM_EQUIP_SUCCESS: {
          int removed_from_inventory = remove_item_from_player_inventory(player, current_item);

          switch (removed_from_inventory) {
            case ITEM_REMOVE_FROM_INVENTORY_INVALID:
            case ITEM_REMOVE_FROM_INVENTORY_ERROR:
              unequip_item(player, current_item);
              print_text(PRINT_NORMAL5, "Unable to remove item from inventory\n");
              break;
            case ITEM_REMOVE_FROM_INVENTORY_SUCCESS:
              print_text(PRINT_NORMAL5, "Equipped %s\n", current_item->name);
              break;
            default:
              break;
          }
        }
        default:
          break;
      }
      destroy_menu(player->current_menu);
      Menu *new_menu = build_menu(prev_menu_kind, player);
      new_menu->prev_menu = &view_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case ACTION_UNEQUIP_ITEM: {
      int unequipped_item = unequip_item(player, current_item);

      switch (unequipped_item) {
        case ITEM_UNEQUIP_INVALID:
        case ITEM_UNEQUIP_ERROR:
          print_text(PRINT_NORMAL5, "Unable to unequip item\n");
        case ITEM_UNEQUIP_SUCCESS: {
          int added_to_inventory = add_item_to_player_inventory(player, current_item);

          switch (added_to_inventory) {
            case ITEM_ADD_TO_INVENTORY_INVALID:
            case ITEM_ADD_TO_INVENTORY_ERROR:
              print_text(PRINT_NORMAL5, "Unable to add item to inventory\n");
              break;
            case INVENTORY_ITEMS_FULL: {
              Menu *new_menu = build_menu(MENU_FIND_INVENTORY_ITEM_TO_SWAP, player);
              new_menu->prev_menu = player->current_menu->prev_menu->prev_menu;
              player->current_menu = new_menu;
              return 1;
            }
            case ITEM_ADD_TO_INVENTORY_SUCCESS: {
              print_text(PRINT_NORMAL5, "Unequipped %s\n", current_item->name);
              destroy_menu(player->current_menu);
              Menu *new_menu = build_menu(prev_menu_kind, player);
              new_menu->prev_menu = &view_menu;
              player->current_menu = new_menu;
              return 1;
            }
          }
        }
      }
    }
    case ACTION_SWAP_EQUIPPED_ITEM: {
      ItemKind equipped_item_kind = player->current_menu->prev_menu->item->kind;
      Item **equipped_item;
      Item *selected_item = player->current_menu->prev_menu->item;

      switch (equipped_item_kind) {
        case ITEM_WEAPON: {
          equipped_item = &player->weapon;
          break;
        }
        case ITEM_SHIELD: {
          equipped_item = &player->shield;
          break;
        }
        case ITEM_ACCESSORY: {
          equipped_item = &player->accessory;
          break;
        }
        default:
          equipped_item = NULL;
          break;
      }

      int swapped_items = swap_items(player, equipped_item, selected_item);

      switch (swapped_items) {
        case ITEM_SWAP_INVALID:
        case ITEM_SWAP_ERROR:
          print_text(PRINT_NORMAL5, "Unable to swap items");
          break;
        case ITEM_SWAP_SUCCESS: {
          print_text(PRINT_NORMAL5, "Equipped %s\nUnequipped %s\n", selected_item->name, (*equipped_item)->name);
        }
      }
      destroy_menu(player->current_menu);
      Menu *new_menu = build_menu(prev_menu_kind, player);
      new_menu->prev_menu = &view_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case ACTION_SWAP_UNEQUIPPED_ITEM: {
      ItemKind equipped_item_kind = player->current_menu->prev_menu->item->kind;
      Item *equipped_item = player->current_menu->prev_menu->item;

      Item **unequipped_item;

      for (int i = 0; i < player->inventory_count; i++) {
      }

      int swapped_items = swap_items(player, unequipped_item, equipped_item);

      switch (swapped_items) {
        case ITEM_SWAP_INVALID:
        case ITEM_SWAP_ERROR:
          print_text(PRINT_NORMAL5, "Unable to swap items");
          break;
        case ITEM_SWAP_SUCCESS: {
          print_text(PRINT_NORMAL5, "Equipped %s\nUnequipped %s\n", equipped_item->name, (*unequipped_item)->name);
        }
      }
      destroy_menu(player->current_menu);
      Menu *new_menu = build_menu(prev_menu_kind, player);
      new_menu->prev_menu = &view_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case ACTION_USE_ITEM: {
      prev_menu_kind = player->current_menu->prev_menu->menu_kind;
      int used_item = use_item(player, current_item);
      if (used_item == ITEM_USE_INVALID || used_item == ITEM_USE_ERROR) {
        print_text(PRINT_NORMAL5, "Unable to use item\n");
      } else if (used_item == ITEM_USE_SUCCESS) {
        char health_regained[12];
        snprintf(health_regained, sizeof(health_regained), "%+d hp", current_item->data.potion.health_bonus);
        char attack_bonus[12];
        snprintf(attack_bonus, sizeof(attack_bonus), "%+d atk", current_item->data.potion.attack_bonus);
        char defense_bonus[12];
        snprintf(defense_bonus, sizeof(defense_bonus), "%+d def", current_item->data.potion.defense_bonus);
        print_text(PRINT_NORMAL5, "Used %s (%s, %s, %s)\n", health_regained, attack_bonus, defense_bonus);
      }
      destroy_menu(player->current_menu);
      Menu *new_menu = build_menu(prev_menu_kind, player);
      new_menu->prev_menu = &view_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case ACTION_DROP_ITEM: {
      int added_to_room = add_item_to_room(current_room, current_item);
      if (added_to_room == ROOM_ITEMS_FULL) {
        print_text(PRINT_NORMAL5, "You should stop littering. The world is already filled with enough rubbish.\n");
      } else if (added_to_room == ITEM_ADD_TO_ROOM_INVALID || added_to_room == ITEM_ADD_TO_INVENTORY_ERROR) {
        print_text(PRINT_NORMAL5, "Unable to drop item on ground\n");
      } else if (added_to_room == ITEM_ADD_TO_ROOM_SUCCESS) {
        int removed_from_inventory = remove_item_from_player_inventory(player, current_item);
        if (removed_from_inventory == ITEM_REMOVE_FROM_INVENTORY_INVALID || removed_from_inventory == ITEM_REMOVE_FROM_INVENTORY_ERROR) {
          print_text(PRINT_NORMAL5, "Unable to remove item from inventory\n");
        } else if (removed_from_inventory == ITEM_REMOVE_FROM_INVENTORY_SUCCESS) {
          print_text(PRINT_NORMAL5, "Dropped %s\n", current_item->name);
        }
      }
      destroy_menu(player->current_menu);
      Menu *new_menu = build_menu(MENU_VIEW_INVENTORY, player);
      new_menu->prev_menu = &view_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case ACTION_THROW_AWAY_ITEM: {
      int removed_from_inventory = remove_item_from_player_inventory(player, current_item);
      if (removed_from_inventory == ITEM_REMOVE_FROM_INVENTORY_INVALID || removed_from_inventory == ITEM_REMOVE_FROM_INVENTORY_ERROR) {
        print_text(PRINT_NORMAL5, "Unable to remove item from inventory\n");
      } else if (removed_from_inventory == ITEM_REMOVE_FROM_INVENTORY_SUCCESS) {
        destroy_item(current_item);
        print_text(PRINT_NORMAL5, "You toss the %s into the void.\n", current_item->name);
      }
      destroy_menu(player->current_menu);
      Menu *new_menu = build_menu(MENU_VIEW_INVENTORY, player);
      new_menu->prev_menu = &view_menu;
      player->current_menu = new_menu;
      return 1;
    }
    case ACTION_PREVIOUS_PAGE: {
      player->current_menu = player->current_menu->prev_page;
      return 1;
    }
    case ACTION_NEXT_PAGE: {
      player->current_menu = player->current_menu->next_page;
      return 1;
    }
    case ACTION_NO:
    case ACTION_BACK_MENU: {
      Menu *temp = player->current_menu;
      player->current_menu = player->current_menu->prev_menu;
      destroy_menu(temp);
      return 1;
    }
    case ACTION_YES: {
    }
    case ACTION_QUIT_GAME: {
      print_text(PRINT_NORMAL5, "You open your eyes and realize it was just a dream.\n");
      return 0;
    }
    default:
    print_text(PRINT_NORMAL5, "You stare off into the distance...\n");
    return 1;
  }
}

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
  display_menu(player);
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
    case NODE_MENU_ITEM: {
      print_text(PRINT_FAST3, "Selected: Item\n");
      MenuKind menu_kind = menu_node->data_kind.menu_kind;
      print_text(PRINT_FAST3, "Selected MenuKind: %d\n", menu_kind);
      Item *item = menu_node->data.item;
      Menu *new_menu = build_item_menu(menu_kind, item);
      if (new_menu != NULL) {
        new_menu->prev_menu = player->current_menu;
        player->current_menu = new_menu;
      }
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
