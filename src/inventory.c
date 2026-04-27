#include <stdlib.h>
#include "entities.h"
#include "status.h"
#include "game.h"
#include "items.h"
#include "inventory.h"

int add_item_to_player_inventory(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return ITEM_ADD_TO_INVENTORY_INVALID;
  }

  player->inventory[player->inventory_count] = item;
  player->inventory_count++;
  return ITEM_ADD_TO_INVENTORY_SUCCESS;
}

int remove_item_from_player_inventory(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return ITEM_REMOVE_FROM_INVENTORY_INVALID;
  }

  for (int i = 0; i < player->inventory_count; i++) {
    if (player->inventory[i]->id == item->id) {
      if (i != player->inventory_count-1) {
        player->inventory[i] = player->inventory[player->inventory_count-1];
      }
      player->inventory[player->inventory_count-1] = NULL;
      player->inventory_count--;
      return ITEM_REMOVE_FROM_INVENTORY_SUCCESS;
    }
  }
  return ITEM_REMOVE_FROM_INVENTORY_ERROR;
}
