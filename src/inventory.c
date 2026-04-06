#include <stdlib.h>
#include "game.h"
#include "items.h"
#include "inventory.h"

void view_inventory(Player *player) {
  return;
}

int add_item_to_player_inventory(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return ITEM_ADD_TO_INVENTORY_INVALID;
  }

  player->inventory[player->inventory_count-1] = item;
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

int equip_item(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return ITEM_EQUIP_INVALID;
  }

  switch (item->kind) {
    case WEAPON:
      if (player->weapon == NULL) {
        player->weapon = item;
        return ITEM_EQUIP_SUCCESS;
      } else {
        return ITEM_SLOT_ALREADY_EQUIPPED;
      }
    case SHIELD:
      player->shield = item;
      return ITEM_EQUIP_SUCCESS;
    case POTION:
      return ITEM_EQUIP_INVALID;
    case ACCESSORY:
      player->accessory = item;
      return ITEM_EQUIP_SUCCESS;
  }
}

int unequip_item(Player *player, Item *item) {
  return ITEM_UNEQUIP_INVALID;
}


int use_item(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return ITEM_USE_ERROR;
  }

  switch (item->kind) {
    case WEAPON:
    case SHIELD:
      return ITEM_USE_INVALID;
    case POTION: {
      int health_regained = player->health + item->data.potion.health_bonus;
      int max_health = player->max_health;
      player->health = health_regained > max_health ? max_health : health_regained;

      player->attack += item->data.potion.attack_bonus;
      player->defense += item->data.potion.defense_bonus;

      destroy_item(item);
      return ITEM_USE_SUCCESS;
    }
    case ACCESSORY:
      return ITEM_USE_INVALID;
    default:
      return ITEM_USE_INVALID;
  }
}

void discard_item(Player *player, Item *item) {
  return;
}
