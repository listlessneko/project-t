#pragma once

#include "entities.h"
#include "rooms.h"

typedef enum NodeKind {
  NODE_MENU,
  NODE_ACTION,
} NodeKind;

typedef enum MenuKind {
  MENU_MAIN,
  MENU_EXPLORE,
  MENU_EXPLORE_ROOM,
  MENU_VIEW,
  MENU_FIGHT,
  MENU_VIEW_ROOM,
  MENU_VIEW_ROOM_ITEM,
  MENU_VIEW_INVENTORY,
  MENU_VIEW_INVENTORY_ITEM,
  MENU_VIEW_MAP,
  MENU_VIEW_STATS,
} MenuKind;

typedef enum ActionKind {
  ACTION_GO,
  ACTION_PICK_UP,
  ACTION_USE,
  ACTION_DROP,
  ACTION_THROW_AWAY,
  ACTION_PREVIOUS,
  ACTION_NEXT,
  ACTION_BACK,
  ACTION_QUIT,
} ActionKind;

typedef struct MenuNode {
  NodeKind node_kind;
  union {
    MenuKind menu_kind;
    ActionKind action_kind;
  } data_kind;
  char name[64];
  char description[256];
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
  char name[64];
  char description[256];
  int is_static;
  struct Menu *prev_menu;
  struct Menu *prev_page;
  struct Menu *next_page;
  int options_count;
  MenuNode *options[];
} Menu;

extern Menu main_menu;

int playing(Player *player);
MenuNode *build_menu_node(NodeKind node_kind, void *data);
MenuNode *build_room_menu_node(DirectionKind direction_kind, Room *room);
Menu *menu_realloc(Menu *menu, int count);
void display_menu(Menu *menu);
MenuNode *parse_player_choice(Player *player, char *choice);
