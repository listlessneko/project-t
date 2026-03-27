#pragma once

typedef enum {
  WEAPON,
  ARMOR,
  POTION,
  ACCESSORY
} ItemKind;

typedef struct Weapon {
  int attack_bonus;
} Weapon;

typedef struct Armor {
  int defense_bonus;
} Armor;

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
  union {
    Weapon weapon;
    Armor armor;
    Potion potion;
    Accessory accessory;
  } data;
} Item;

Item *create_item(ItemKind kind, char *name, int health_bonus, int attack_bonus, int defense_bonus);
void destroy_item(Item *item);
