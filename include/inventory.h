#include "items.h"
#include "game.h"

typedef enum {
  ITEM_CREATION_SUCCESS,
  ITEM_CREATION_ERROR,
  ITEM_CREATION_INVALID,
  ITEM_DESTROYED_SUCCESS,
  ITEM_DESTROYED_ERROR,
  ITEM_DESTROYED_INVALID,
  ITEM_ADD_TO_INVENTORY_SUCCESS,
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
  ITEM_UNEQUIP_INVALID
} ItemInteractionResult;

void view_inventory(Player *player);
int add_item_to_player_inventory(Player *player, Item *item);
int remove_item_from_player_inventory(Player *player, Item *item);
int equip_item(Player *player, Item *item);
int unequip_item(Player *player, Item *item);
int use_item(Player *player, Item *item);
void discard_item(Player *player, Item *item);
