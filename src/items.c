#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"
#include "entities.h"
#include "status.h"
#include "game.h"
#include "inventory.h"

static int item_id_counter = 0;

const char *item_kind_name(ItemKind kind) {
  switch(kind) {
    case ITEM_WEAPON:
      return "Weapon";
    case ITEM_SHIELD:
      return "Shield";
    case ITEM_POTION:
      return "Potion";
    case ITEM_ACCESSORY:
      return "Accessory";
    default:
      return "Unknown";
  }
}

Item *create_item(ItemKind kind, char *name, int health_bonus, int attack_bonus, int defense_bonus) {
  if (kind < 0 || kind > 3) {
    return NULL;
  }

  Item *new_item = malloc(sizeof(Item));
  if (new_item == NULL) {
    return NULL;
  }

  strcpy(new_item->name, name);
  new_item->kind = kind;
  new_item->id = item_id_counter++;

  switch (kind) {
    case ITEM_WEAPON:
      new_item->data.weapon.attack_bonus = attack_bonus;
      break;
    case ITEM_SHIELD:
      new_item->data.shield.defense_bonus = defense_bonus;
      break;
    case ITEM_ACCESSORY:
      new_item->data.accessory.attack_bonus = attack_bonus;
      new_item->data.accessory.defense_bonus = defense_bonus;
      break;
    case ITEM_POTION:
      new_item->data.potion.health_bonus = health_bonus;
      new_item->data.potion.attack_bonus = attack_bonus;
      new_item->data.potion.defense_bonus = defense_bonus;
      break;
    default:
      break;
  }

  return new_item;
}

int equip_item(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return ITEM_EQUIP_INVALID;
  }

  switch (item->kind) {
    case ITEM_WEAPON:
      if (player->weapon == NULL) {
        player->weapon = item;
        return ITEM_EQUIP_SUCCESS;
      } else {
        return ITEM_SLOT_ALREADY_EQUIPPED;
      }
    case ITEM_SHIELD:
      if (player->shield == NULL) {
        player->shield = item;
        return ITEM_EQUIP_SUCCESS;
      } else {
        return ITEM_SLOT_ALREADY_EQUIPPED;
      }
    case ITEM_POTION:
      return ITEM_EQUIP_INVALID;
    case ITEM_ACCESSORY:
      if (player->accessory == NULL) {
        player->accessory = item;
        return ITEM_EQUIP_SUCCESS;
      } else {
        return ITEM_SLOT_ALREADY_EQUIPPED;
      }
    default:
      return ITEM_EQUIP_ERROR;
  }
}

int unequip_item(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return ITEM_UNEQUIP_INVALID;
  }

  switch (item->kind) {
    case ITEM_WEAPON: {
      if (player->weapon == NULL) {
        return ITEM_SLOT_EMPTY;
      } else if (player->inventory_count >= MAX_INVENTORY_SIZE) {
        return INVENTORY_ITEMS_FULL;
      } else {
        player->weapon = NULL;
        return ITEM_UNEQUIP_SUCCESS;
      }
    }
    case ITEM_SHIELD: {
      if (player->shield == NULL) {
        return ITEM_SLOT_EMPTY;
      } else if (player->inventory_count >= MAX_INVENTORY_SIZE) {
        return INVENTORY_ITEMS_FULL;
      } else {
        player->shield = NULL;
        return ITEM_UNEQUIP_SUCCESS;
      }
    }
    case ITEM_ACCESSORY: {
      if (player->accessory == NULL) {
        return ITEM_SLOT_EMPTY;
      } else if (player->inventory_count >= MAX_INVENTORY_SIZE) {
        return INVENTORY_ITEMS_FULL;
      } else {
        player->accessory = NULL;
        return ITEM_UNEQUIP_SUCCESS;
      }
    }
    default:
      return ITEM_UNEQUIP_ERROR;
  }
}


int use_item(Player *player, Item *item) {
  if (player == NULL || item == NULL) {
    return ITEM_USE_INVALID;
  }

  switch (item->kind) {
    case ITEM_WEAPON:
    case ITEM_SHIELD:
    case ITEM_ACCESSORY:
      return ITEM_USE_INVALID;
    case ITEM_POTION: {
      int health_regained = player->health + item->data.potion.health_bonus;
      int max_health = player->max_health;
      player->health = health_regained > max_health ? max_health : health_regained;

      player->attack += item->data.potion.attack_bonus;
      player->defense += item->data.potion.defense_bonus;

      destroy_item(item);
      return ITEM_USE_SUCCESS;
    }
    default:
      return ITEM_USE_ERROR;
  }
}

int swap_items(Player *player, Item **item_a, Item *item_b) {
  if (player == NULL || item_a == NULL || item_b == NULL) {
    return ITEM_SWAP_INVALID;
  }

  for (int i = 0; i < player->inventory_count; i++) {
    if (player->inventory[i]->id == item_b->id) {
      Item *temp = player->inventory[i];
      player->inventory[i] = *item_a;
      *item_a = temp;
      return ITEM_SWAP_SUCCESS;
    }
  }
  return ITEM_SWAP_ERROR;
}

void destroy_item(Item *item) {
  free(item);
}

