#include "items.h"
#include "game.h"

void view_inventory(Player *player);
int add_item_to_player_inventory(Player *player, Item *item);
int remove_item_from_player_inventory(Player *player, Item *item);
int equip_item(Player *player, Item *item);
int unequip_item(Player *player, Item *item);
int use_item(Player *player, Item *item);
void discard_item(Player *player, Item *item);
