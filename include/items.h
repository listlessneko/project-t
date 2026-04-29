#pragma once

#include "entities.h"

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
  EntityKind entity_kind;
  int id;
  char name[MAX_NAME_LEN];
  char description[MAX_DESCRIPTION_LEN];
  ItemKind kind;
  union {
    Weapon weapon;
    Shield shield;
    Potion potion;
    Accessory accessory;
  } data;
} Item;

const char *item_kind_name(ItemKind kind);
Item *create_item(ItemKind kind, char *name, int health_bonus, int attack_bonus, int defense_bonus);
int equip_item(Player *player, Item *item);
int unequip_item(Player *player, Item *item);
int use_item(Player *player, Item *item);
int swap_items(Player *player, Item **item_a, Item *item_b);
void destroy_item(Item *item);
