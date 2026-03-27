#include <stdlib.h>
#include "game.h"
#include "items.h"

void view_inventory(Player *player) {
  return;
}

void add_item_to_player_inventory(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return;
  }

  player->inventory[player->inventory_count-1] = item;
  player->inventory_count++;
}

void remove_item_from_player_inventory(Player *player, Item *item) {
  return;
}

void equip_item(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return;
  }

  switch (item->kind) {
    case WEAPON:
      player->weapon = item;
      break;
    case SHIELD:
      player->shield = item;
      break;
    case POTION:
      break;
    case ACCESSORY:
      player->accessory = item;
      break;
  }
  return;
}

void unequip_item(Player *player, Item *item) {
  return;
}


void use_item(Player *player) {
  return;
}

void discard_item(Player *player) {
  return;
}
