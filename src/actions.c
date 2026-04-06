#include <stdlib.h>
#include "actions.h"
#include "game.h"
#include "inventory.h"
#include "items.h"
#include "rooms.h"

int drop_item(Player *player, Item *item, Room *room) {
  if (player == NULL || item == NULL || room == NULL) {
    return DROP_ITEM_INVALID;
  }

  int removed_from_inventory = remove_item_from_player_inventory(player, item);
  if (removed_from_inventory == ITEM_REMOVE_FROM_INVENTORY_SUCCESS) {
    int added_to_room = add_item_to_room(room, item);
    if (added_to_room == ITEM_ADD_TO_ROOM_SUCCESS) {
      return DROP_ITEM_SUCCESS;
    } else if (added_to_room == ROOM_ITEMS_FULL) {
      destroy_item(item);
      return DROP_ITEM_FULL;
    }
  }
  return DROP_ITEM_ERROR;
}

int pick_up_item(Player *player, Item *item, Room *room) {
  if (player == NULL || item == NULL || room == NULL) {
    return PICK_UP_ITEM_INVALID;
  }

  int removed_from_room = remove_item_from_room(room, item);
  if (removed_from_room == ITEM_REMOVE_FROM_ROOM_SUCCESS) {
    int added_to_inventory = add_item_to_player_inventory(player, item);
    if (added_to_inventory == INVENTORY_ITEMS_FULL) {
      add_item_to_room(room, item);
      return PICK_UP_ITEM_FULL;
    } else if (added_to_inventory == ITEM_ADD_TO_INVENTORY_SUCCESS) {
      return PICK_UP_ITEM_SUCCESS;
    }
  }
  return PICK_UP_ITEM_ERROR;
}
