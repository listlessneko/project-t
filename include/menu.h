#include "entities.h"
#include "rooms.h"

typedef enum NodeKind {
  NODE_MENU_MAIN,
  NODE_MENU_EXPLORE,
  NODE_MENU_EXPLORE_ROOM,
  NODE_MENU_EXAMINE,
  NODE_MENU_FIGHT,
  NODE_MENU_EXAMINE_ROOM,
  NODE_MENU_EXAMINE_ROOM_ITEM,
  NODE_MENU_EXAMINE_INVENTORY,
  NODE_MENU_EXAMINE_INVENTORY_ITEM,
  NODE_MENU_EXAMINE_MAP,
  NODE_MENU_EXAMINE_STATS,
  NODE_ACTION_PICK_UP,
  NODE_ACTION_USE,
  NODE_ACTION_DROP,
  NODE_ACTION_THROW_AWAY,
  NODE_ACTION_BACK,
  NODE_ACTION_QUIT,
} NodeKind;

typedef struct MenuNode {
  NodeKind node_kind;
  char name[32];
  char description[256];
  union {
    Player *player;
    Enemy *enemy;
    Room *room;
    Item *item;
  } data;
} MenuNode;

typedef struct Menu {
  char name[32];
  char description[256];
  struct Menu *prev_menu;
  struct Menu *prev_page;
  struct Menu *next_page;
  int options_count;
  MenuNode *options[];
} Menu;

MenuNode *build_menu_node(NodeKind node_kind, void *data);
MenuNode *build_room_menu_node(DirectionKind direction_kind, Room *room);
Menu *menu_realloc(Menu *menu, int count);
void display_menu(Menu *menu);
Menu *parse_player_choice(Player *player, Menu *menu, char *choice);
