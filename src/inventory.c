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

  int index = -1;
  for (int i = 0; i < player->inventory_count; i++) {
    if (player->inventory[i]->id == item->id) {
      index = i;
      break;
    }
  }

  if (index > -1) {
    int j;
    for (j = index; j < player->inventory_count-1; j++) {
      player->inventory[j] = player->inventory[j+1];
    }
    player->inventory[j] = NULL;
    player->inventory_count--;
    return ITEM_REMOVE_FROM_INVENTORY_SUCCESS;
  }
  return ITEM_REMOVE_FROM_INVENTORY_ERROR;
}

Item **filtered_inventory(Player *player, ItemKind item_kind, int *count) {
  if (player == NULL || item_kind == ITEM_UNKNOWN) {
    return NULL;
  }

  int filtered_count = 0;

  for (int i = 0; i < player->inventory_count; i++) {
    if (player->inventory[i]->kind == item_kind) {
      filtered_count++;
    }
  }

  Item **filtered = malloc(sizeof(Item *) * filtered_count);
  if (filtered == NULL) {
    return NULL;
  }

  int f_index = 0;
  for (int j = 0; j < player->inventory_count; j++) {
     if (player->inventory[j]->kind == item_kind) {
      (filtered)[f_index] = player->inventory[j];
      f_index++;
    }
  }

  *count = filtered_count;
  return filtered;
}

