#pragma once

typedef enum {
  WEAPON,
  ARMOR,
  POTION,
  ACCESSORY
} ItemKind;

typedef struct Weapon {
  char name[32];
  int attack_bonus;
} Weapon;

typedef struct Armor {
  char name[32];
  int defense_bonus;
} Armor;

typedef struct Potion {
  char name[32];
  int health_bonus;
  int attack_bonus;
  int defense_bonus;
} Potion;

typedef struct Accessory {
  char name[32];
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

Item create_item();
