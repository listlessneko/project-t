#include "entities.h"

#define CMD_PICK_UP "pick up"
#define CMD_DROP "drop"
#define CMD_EXAMINE "examine"
#define CMD_GO "go"
#define CMD_USE "use"
#define CMD_QUIT "quit"

typedef enum CommandKind {
  CMD_KIND_EXAMINE,
  CMD_KIND_GO,
  CMD_KIND_PICK_UP,
  CMD_KIND_DROP,
  CMD_KIND_USE,
  CMD_KIND_QUIT,
  CMD_KIND_UNKNOWN
} CommandKind;

typedef struct ParsedCommand {
  CommandKind kind;
  char target[32];
} ParsedCommand;

ParsedCommand parse_input(const char *input);
int explore(Player *player);
int drop_item(Player *player, Item *item, Room *room);
int pick_up_item(Player *player, Item *item, Room *room);
