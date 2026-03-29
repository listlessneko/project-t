#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

static int item_id_counter = 0;

const char *item_kind_name(ItemKind kind) {
  switch(kind) {
    case WEAPON:
      return "Weapon";
    case SHIELD:
      return "Shield";
    case POTION:
      return "Potion";
    case ACCESSORY:
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
    Item empty = {0};
    return NULL;
  }

  strcpy(new_item->name, name);
  new_item->kind = kind;
  new_item->id = item_id_counter++;

  switch (kind) {
    case WEAPON:
      new_item->data.weapon.attack_bonus = attack_bonus;
      break;
    case SHIELD:
      new_item->data.shield.defense_bonus = defense_bonus;
      break;
    case ACCESSORY:
      new_item->data.accessory.attack_bonus = attack_bonus;
      new_item->data.accessory.defense_bonus = defense_bonus;
      break;
    case POTION:
      new_item->data.potion.health_bonus = health_bonus;
      new_item->data.potion.attack_bonus = attack_bonus;
      new_item->data.potion.defense_bonus = defense_bonus;
      break;
  }

  return new_item;
}

void destroy_item(Item *item) {
  free(item);
}

