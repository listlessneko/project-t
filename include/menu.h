#include "entities.h"

typedef enum MenuNodeKind {
  MENU_NODE_MAIN,
  MENU_NODE_BASE_MENU,
  MENU_NODE_EXPLORE,
  MENU_NODE_EXPLORE_ROOM,
  MENU_NODE_EXAMINE,
  MENU_NODE_FIGHT,
  MENU_NODE_EXAMINE_ROOM,
  MENU_NODE_EXAMINE_ROOM_ITEM,
  MENU_NODE_EXAMINE_INVENTORY,
  MENU_NODE_EXAMINE_INVENTORY_ITEM,
  MENU_NODE_EXAMINE_MAP,
  MENU_NODE_EXAMINE_STATS,
  MENU_NODE_BACK,
  MENU_NODE_QUIT,
} MenuNodeKind;

typedef enum MenuKind {
  MENU_MAIN,
  MENU_EXPLORE,
  MENU_EXAMINE,
  MENU_EXAMINE_ROOM,
  MENU_EXAMINE_INVENTORY,
  MENU_EXAMINE_MAP,
  MENU_EXAMINE_STATS,
  MENU_FIGHT,
} MenuKind;

typedef enum ActionKind {
  ACTION_BACK,
  ACTION_QUIT,
} ActionKind;

typedef struct BaseMenu {
  MenuKind menu_kind;
  char name[32];
  char description[256];
} BaseMenu;

typedef struct BaseAction {
  ActionKind action_kind;
  char name[32];
  char description[256];
} BaseAction;

typedef struct BaseRoom {
  EntityKind entity_kind;
  char name[32];
  char description[256];
  Room *room;
} BaseRoom;

typedef struct MenuNode {
  MenuNodeKind menu_node_kind;
  char name[32];
  char description[256];
  union {
    BaseMenu *base_menu;
    BaseAction *base_action;
    Player *player;
    Enemy *enemy;
    Room *room;
    Item *item;
  } data;
} MenuNode;

typedef struct Menu {
  MenuKind menu_kind;
  char name[32];
  char description[256];
  int count;
  MenuNode *options[];
} Menu;

MenuNode *build_menu_node(MenuNodeKind menu_node_kind, void *data);
void menu_realloc(Menu *menu, int count);
void display_menu(Menu *menu);
Menu *parse_player_choice(Player *player, Menu *menu, char *choice);
