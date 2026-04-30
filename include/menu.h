#pragma once

#include "entities.h"
#include "rooms.h"

#define MAX_MENU_NAME_LEN (MAX_NAME_LEN * 2 + 2)
#define MAX_MENU_DESCRIPTION_LEN (MAX_DESCRIPTION_LEN * 2 + 2)
#define MAX_MENU_NODE_NAME_LEN (MAX_NAME_LEN * 2 + 2)
#define MAX_MENU_NODE_DESCRIPTION_LEN (MAX_DESCRIPTION_LEN * 2 + 2)

typedef enum NodeKind {
  NODE_MENU,
  NODE_MENU_ITEM,
  NODE_ACTION,
} NodeKind;

typedef enum MenuKind {
  MENU_MAIN,
  MENU_CONFIRM,
  MENU_EXPLORE,
  MENU_EXPLORE_ROOM,
  MENU_VIEW,
  MENU_FIGHT,
  MENU_VIEW_ROOM,
  MENU_VIEW_ROOM_ITEM,
  MENU_VIEW_INVENTORY,
  MENU_VIEW_INVENTORY_ITEM,
  MENU_SWAP_WITH_EQUIPPED_ITEM,
  MENU_VIEW_UNEQUIPPED_ITEM,
  MENU_SWAP_EQUIPPED_ITEM,
  MENU_SWAP_UNEQUIPPED_ITEM,
  MENU_VIEW_EQUIPMENT,
  MENU_VIEW_EQUIPPED_ITEM,
  MENU_FIND_INVENTORY_ITEM_TO_SWAP,
  MENU_SWAP_VIEW_INVENTORY,
  MENU_SWAP_WITH_INVENTORY_ITEM,
  MENU_VIEW_MAP,
  MENU_VIEW_STATS,
} MenuKind;

typedef enum ActionKind {
  ACTION_GO_EXPLORE_ROOM,
  ACTION_PICK_UP_ITEM,
  ACTION_EQUIP_ITEM,
  ACTION_UNEQUIP_ITEM,
  ACTION_SWAP_EQUIPPED_ITEM,
  ACTION_SWAP_UNEQUIPPED_ITEM,
  ACTION_USE_ITEM,
  ACTION_DROP_ITEM,
  ACTION_THROW_AWAY_ITEM,
  ACTION_PREVIOUS_PAGE,
  ACTION_NEXT_PAGE,
  ACTION_BACK_MENU,
  ACTION_YES,
  ACTION_NO,
  ACTION_QUIT_GAME,
} ActionKind;

typedef struct MenuNode {
  NodeKind node_kind;
  union {
    MenuKind menu_kind;
    ActionKind action_kind;
  } data_kind;
  char name[MAX_MENU_NODE_NAME_LEN];
  char description[MAX_MENU_NODE_DESCRIPTION_LEN];
  char key;
  int is_static;
  union {
    Player *player;
    Enemy *enemy;
    Room *room;
    Item *item;
  } data;
  union {
    DirectionKind direction;
  } action;
} MenuNode;

typedef struct Menu {
  MenuKind menu_kind;
  char name[MAX_MENU_NAME_LEN];
  char description[MAX_MENU_DESCRIPTION_LEN];
  char options[1000];
  int is_static;
  struct Menu *prev_menu;
  struct Menu *prev_page;
  struct Menu *next_page;
  Item *item;
  int node_count;
  MenuNode *nodes[];
} Menu;

extern Menu main_menu;

int playing(Player *player);
MenuNode *build_menu_node(NodeKind node_kind, void *data);
MenuNode *build_room_menu_node(DirectionKind direction_kind, Room *room);
Menu *menu_realloc(Menu *menu, int count);
void display_menu(Player *player);
MenuNode *parse_player_choice(Player *player, char *choice);
