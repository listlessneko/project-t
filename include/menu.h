#include "entities.h"

typedef enum MenuNodeKind {
  MENU_NODE_MAIN,
  MENU_NODE_EXPLORE,
  MENU_NODE_EXAMINE,
  MENU_NODE_FIGHT,
  MENU_NODE_EXAMINE_ROOM,
  MENU_NODE_EXAMINE_INVENTORY,
  MENU_NODE_EXAMINE_MAP,
  MENU_NODE_EXAMINE_STATS,
} MenuNodeKind;

typedef enum MenuKind {
  MENU_MAIN,
  MENU_EXPLORE,
  MENU_EXAMINE,
  MENU_FIGHT,
} MenuKind;

typedef struct BaseMenu {
  MenuKind menu_kind;
  char *name[32];
  char *description[256];
} BaseMenu;

typedef struct MenuNode {
  MenuNodeKind menu_node_kind;
  union {
    BaseMenu *base_menu;
    Player *player;
    Enemy *enemy;
    Room *room;
    Item *item;
  } data;
} MenuNode;

typedef struct Menu {
  char *name[32];
  char *description[256];
  int count;
  MenuNode *options[];
} Menu;

void display_menu(Menu *menu);
