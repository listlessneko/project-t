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
  char name[32];
  char description[256];
  ItemKind kind;
  union {
    Weapon weapon;
    Shield shield;
    Potion potion;
    Accessory accessory;
  } data;
} Item;

Item *create_item(ItemKind kind, char *name, int health_bonus, int attack_bonus, int defense_bonus);
void destroy_item(Item *item);
