#include "entities.h"

#define CMD_PICK_UP "pick up"
#define CMD_DROP "drop"
#define CMD_EXAMINE "examine"
#define CMD_GO "go"
#define CMD_USE "use"
#define CMD_QUIT "quit"

typedef enum MenuKind {
  MENU_KIND_MAIN,
  MENU_KIND_EXPLORE,
  MENU_KIND_EXAMINE,
  MENU_KIND_FIGHT,
  MENU_KIND_EXAMINE_AREA,
  MENU_KIND_EXAMINE_INVENTORY,
  MENU_KIND_EXAMINE_MAP,
  MENU_KIND_EXAMINE_STATS,
  MENU_KIND_UNKNOWN
} MenuKind;

typedef enum SelectionKind {
  SELECT_KIND_QUIT,
  SELECT_KIND_GO,
  SELECT_KIND_PICK_UP,
  SELECT_KIND_USE,
  SELECT_KIND_DROP,
  SELECT_KIND_THROW_AWAY,
  SELECT_KIND_MAP,
  SELECT_KIND_STATS,
  SELECT_KIND_UNKNOWN
} SelectionKind;

typedef struct MenuOptions {
  union {
    MenuKind menu;
    SelectionKind selection;
  } display_type;
  char *name;
  char *description;
} MenuOptions;

typedef struct Selections {
  SelectionKind selection_kind;
  char *name;
  char *description;
} Selections;

typedef union MenuData {
  MenuOptions menu;
  Selections selection;
  Area *area;
  Item *item;
} MenuData;

typedef struct ParsedCommand {
  SelectionKind kind;
  char target[32];
} ParsedCommand;

typedef struct DisplayOptions {
  union {
    MenuKind menu;
    SelectionKind selection;
  } display;
  int count;
  MenuData *data[];
} DisplayOptions;

DisplayOptions *parse_menu_input(Player *player, MenuKind menu_kind);
void display_menu(MenuOptions *options);
ParsedCommand parse_input(const char *input);
int explore(Player *player);
int drop_item(Player *player, Item *item, Area *area);
int pick_up_item(Player *player, Item *item, Area *area);
