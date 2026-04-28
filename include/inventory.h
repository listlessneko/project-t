#include "entities.h"

void view_inventory(Player *player);
int add_item_to_player_inventory(Player *player, Item *item);
int remove_item_from_player_inventory(Player *player, Item *item);
Item **filtered_inventory(Player *player, ItemKind, int *count);
void discard_item(Player *player, Item *item);
