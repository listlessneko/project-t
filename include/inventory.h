#include "items.h"
#include "game.h"

void view_inventory(Player *player);
void add_item_to_player_inventory(Player *player, Item *item);
void remove_item_from_player_inventory(Player *player, Item *item);
void equip_item(Player *player, Item *item);
void unequip_item(Player *player, Item *item);
void use_item(Player *player);
void discard_item(Player *player);
