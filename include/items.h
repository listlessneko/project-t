#pragma once

#include "game.h"

typedef enum {
  ITEM_CREATION_SUCCESS,
  ITEM_CREATION_ERROR,
  ITEM_CREATION_INVALID,
  ITEM_DESTROYED_SUCCESS,
  ITEM_DESTROYED_ERROR,
  ITEM_DESTROYED_INVALID,
  ITEM_ADD_TO_INVENTORY_SUCCESS,
  INVENTORY_ITEMS_FULL,
  ITEM_ADD_TO_INVENTORY_ERROR,
  ITEM_ADD_TO_INVENTORY_INVALID,
  ITEM_REMOVE_FROM_INVENTORY_SUCCESS,
  ITEM_REMOVE_FROM_INVENTORY_ERROR,
  ITEM_REMOVE_FROM_INVENTORY_INVALID,
  ITEM_USE_SUCCESS,
  ITEM_USE_ERROR,
  ITEM_USE_INVALID,
  ITEM_EQUIP_SUCCESS,
  ITEM_SLOT_ALREADY_EQUIPPED,
  ITEM_EQUIP_ERROR,
  ITEM_EQUIP_INVALID,
  ITEM_UNEQUIP_SUCCESS,
  ITEM_UNEQUIP_ERROR,
  ITEM_UNEQUIP_INVALID,
  ITEM_ADD_TO_ROOM_SUCCESS,
  ITEM_ADD_TO_ROOM_ERROR,
  ITEM_ADD_TO_ROOM_INVALID,
  ITEM_REMOVE_FROM_ROOM_SUCCESS,
  ROOM_ITEMS_FULL,
  ITEM_REMOVE_FROM_ROOM_ERROR,
  ITEM_REMOVE_FROM_ROOM_INVALID,
  DROP_ITEM_SUCCESS,
  DROP_ITEM_FULL,
  DROP_ITEM_ERROR,
  DROP_ITEM_INVALID,
  PICK_UP_ITEM_SUCCESS,
  PICK_UP_ITEM_FULL,
  PICK_UP_ITEM_ERROR,
  PICK_UP_ITEM_INVALID,
  CHOOSE_ITEM_SUCCESS,
  CHOOSE_ITEM_ERROR,
  CHOOSE_ITEM_INVALID,
} ItemInteractionResult;


typedef enum {
  WEAPON,
  SHIELD,
  POTION,
  ACCESSORY
} ItemKind;

typedef struct Weapon {
  int attack_bonus;
} Weapon;

typedef struct Shield {
  int defense_bonus;
} Shield;

typedef struct Potion {
  int health_bonus;
  int attack_bonus;
  int defense_bonus;
} Potion;

typedef struct Accessory {
  int attack_bonus;
  int defense_bonus;
} Accessory;

typedef struct Item {
  char name[32];
  ItemKind kind;
  int id;
  union {
    Weapon weapon;
    Shield shield;
    Potion potion;
    Accessory accessory;
  } data;
} Item;

const char *item_kind_name(ItemKind kind);
Item *create_item(ItemKind kind, char *name, int health_bonus, int attack_bonus, int defense_bonus);
void destroy_item(Item *item);
