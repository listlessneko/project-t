#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "rooms.h"
#include "items.h"
#include "utils.h"

char *directions[] = { "north", "east", "west", "south" };

RoomKindCounter room_kind_counter = {
  .safe = 0,
  .easy = 0,
  .normal = 0,
  .hard = 0
};

RoomAppearanceTemplate safe_room_appearance_templates[] = {
  {
    .name = "Grove",
    .description = "This is a grove...",
    .kind = SAFE
  }
};

RoomAppearanceTemplate easy_room_appearance_templates[] = {
  {
    .name = "Glade",
    .description = "This is a glade...",
    .kind = EASY
  },
  {
    .name = "Clearing",
    .description = "This is a clearing...",
    .kind = EASY
  },
  {
    .name = "Hollow",
    .description = "This is a hollow...",
    .kind = EASY
  },
};

RoomAppearanceTemplate normal_room_appearance_templates[] = {
  {
    .name = "Ridge",
    .description = "This is a ridge...",
    .kind = NORMAL
  },
  {
    .name = "Creek Bed",
    .description = "This is a creek bed...",
    .kind = NORMAL
  },
  {
    .name = "Undergrowth",
    .description = "This is an undergrowth...",
    .kind = NORMAL
  },
  {
    .name = "Fork",
    .description = "This is a Fork...",
    .kind = NORMAL
  },
  {
    .name = "Abandoned Camp",
    .description = "This is an Abandoned Camp...",
    .kind = NORMAL
  },
};

RoomAppearanceTemplate hard_room_appearance_templates[] = {
  {
    .name = "Main Road",
    .description = "This is Main Road...",
    .kind = HARD
  },
  {
    .name = "Wens Pass",
    .description = "This is Wens Pass...",
    .kind = HARD
  },
  {
    .name = "Wens Village",
    .description = "This is Wens Village...",
    .kind = HARD
  },
};

RoomContentsTemplate safe_room_contents_templates[] = {
  {
    .enemy_max_health = -1,
    .enemy_min_health = -1,
    .enemy_max_attack = -1,
    .enemy_min_attack = -1,
    .enemy_max_defense = -1,
    .enemy_min_defense = -1,
    .kind = SAFE
  }
};

RoomContentsTemplate easy_room_contents_templates[] = {
  {
    .enemy_name = "Bandit",
    .enemy_max_health = 5,
    .enemy_min_health = 3,
    .enemy_max_attack = 2,
    .enemy_min_attack = 1,
    .enemy_max_defense = 2,
    .enemy_min_defense = 1,
    .kind = EASY
  }
};

RoomContentsTemplate normal_room_contents_templates[] = {
  {
    .enemy_name = "Raiders",
    .enemy_max_health = 8,
    .enemy_min_health = 5,
    .enemy_max_attack = 4,
    .enemy_min_attack = 2,
    .enemy_max_defense = 4,
    .enemy_min_defense = 2,
    .kind = NORMAL
  }
};

RoomContentsTemplate hard_room_contents_templates[] = {
  {
    .enemy_name = "Warrior",
    .enemy_max_health = 12,
    .enemy_min_health = 8,
    .enemy_max_attack = 8,
    .enemy_min_attack = 5,
    .enemy_max_defense = 8,
    .enemy_min_defense = 5,
    .kind = HARD
  }
};

int add_item_to_room(Room *room, Item *item) {
  if (room == NULL || item == NULL) {
    return ITEM_ADD_TO_ROOM_INVALID;
  }

  if (room->items_count >= MAX_ROOM_ITEMS) {
    return ROOM_ITEMS_FULL;
  }
  room->items[room->items_count] = item;
  room->items_count++;
  return ITEM_ADD_TO_ROOM_SUCCESS;
}

void explore_room(Player *player, int choice) {
  Room **next = NULL;
  if (choice == 1) {
    next = &player->current_room->north;
  } else if (choice == 2) {
    next = &player->current_room->east;
  } else if (choice == 3) {
    next = &player->current_room->west;
  } else if (choice == 4) {
    next = &player->current_room->south;
  }

  if (*next == NULL) {
    if (player->visited_rooms->count < MAX_ROOMS) {
      *next = generate_room(player, choice);
      player->visited_rooms->visited[(*next)->id] = *next;
      player->visited_rooms->visited[(*next)->id]->visited = 1;
      player->visited_rooms->count++;
      player->current_room = *next;
    } else {
      print_text(PRINT_NORMAL5, "You've reached a dead end. Somehow...\n");
    }
  } else {
    player->current_room = *next;
  }
  if (player->current_room->kind == SAFE) {
    print_text(PRINT_NORMAL5, "[Entered %s]\n", player->current_room->name);
    print_text(PRINT_NORMAL5, "%s\n", player->current_room->description);
  } else {
    print_text(PRINT_NORMAL5, "[Entered %s]\n", player->current_room->name);
    print_text(PRINT_NORMAL5, "%s\n", player->current_room->description);
    print_text(PRINT_NORMAL5, "You see a %s\n", player->current_room->enemy->name);
    print_text(PRINT_NORMAL5, "Health: %d\n", player->current_room->enemy->health);
  }
}

Room *generate_room(Player *player, int choice) {
  Room *new_room;
  if (player->current_room == NULL) {
    new_room = malloc(sizeof(Room));
    if (new_room == NULL) {
      return NULL;
    }
    new_room->kind = SAFE;
    room_kind_counter.safe++;
    strcpy(new_room->name, safe_room_appearance_templates[0].name);
    strcpy(new_room->description, safe_room_appearance_templates[0].description);
  } else {

    int visited_count = player->visited_rooms->count;
    RoomKind current_room_kind = player->current_room->kind;

    if (visited_count > MAX_ROOMS) {
      return NULL;
    }

    int max_room_kind = 0;
    int room_kind_count = 0;
    switch (current_room_kind) {
      case SAFE:
        max_room_kind = MAX_SAFE_ROOMS;
        room_kind_count = room_kind_counter.safe;
        break;
      case EASY:
        max_room_kind = MAX_EASY_ROOMS;
        room_kind_count = room_kind_counter.easy;
        break;
      case NORMAL:
        max_room_kind = MAX_NORMAL_ROOMS;
        room_kind_count = room_kind_counter.normal;
        break;
      case HARD:
        max_room_kind = MAX_HARD_ROOMS;
        room_kind_count = room_kind_counter.hard;
        break;
    }

    if (room_kind_count >= max_room_kind) {
      current_room_kind = (RoomKind)(current_room_kind + 1);
      switch (current_room_kind) {
        case SAFE:
          max_room_kind = MAX_SAFE_ROOMS;
          break;
        case EASY:
          max_room_kind = MAX_EASY_ROOMS;
          break;
        case NORMAL:
          max_room_kind = MAX_NORMAL_ROOMS;
          break;
        case HARD:
          max_room_kind = MAX_HARD_ROOMS;
          break;
      }
    }

    new_room = malloc(sizeof(Room));
    if (new_room == NULL) {
      return NULL;
    }

    new_room->kind = current_room_kind;
    int appearance_index = rand() % max_room_kind;
    RoomAppearanceTemplate fateful_room_appearance;
    RoomContentsTemplate fateful_room_contents;
    switch (new_room->kind) {
      case SAFE:
        room_kind_counter.safe++;
        fateful_room_appearance = safe_room_appearance_templates[appearance_index];
        fateful_room_contents = safe_room_contents_templates[0];
        break;
      case EASY:
        room_kind_counter.easy++;
        fateful_room_appearance = easy_room_appearance_templates[appearance_index];
        fateful_room_contents = easy_room_contents_templates[0];
        break;
      case NORMAL:
        room_kind_counter.normal++;
        fateful_room_appearance = normal_room_appearance_templates[appearance_index];
        fateful_room_contents = normal_room_contents_templates[0];
        break;
      case HARD:
        room_kind_counter.hard++;
        fateful_room_appearance = hard_room_appearance_templates[room_kind_counter.hard - 1];
        fateful_room_contents = hard_room_contents_templates[0];

    }

    strcpy(new_room->name, fateful_room_appearance.name);
    strcpy(new_room->description, fateful_room_appearance.description);
    int fateful_max_health = rand() % (fateful_room_contents.enemy_max_health - fateful_room_contents.enemy_min_health + 1) + fateful_room_contents.enemy_min_health;
    int fateful_attack = rand() % (fateful_room_contents.enemy_max_attack - fateful_room_contents.enemy_min_attack + 1) + fateful_room_contents.enemy_min_attack;
    int fateful_defense = rand() % (fateful_room_contents.enemy_max_defense - fateful_room_contents.enemy_min_defense + 1) + fateful_room_contents.enemy_min_defense;
    Enemy *enemy = create_enemy(fateful_room_contents.enemy_name, fateful_max_health, fateful_attack, fateful_defense);
    new_room->enemy = enemy;
  }

  if (choice == 1) {
    new_room->south = player->current_room;
  } else if (choice == 2) {
    new_room->west = player->current_room;
  } else if (choice == 3) {
    new_room->east = player->current_room;
  } else if (choice == 4) {
    new_room->north = player->current_room;
  }
  new_room->id = player->visited_rooms->count;
  new_room->visited = 0;
  return new_room;
}

