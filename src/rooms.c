#include <stdlib.h>
#include <string.h>
#include "entities.h"
#include "status.h"
#include "game.h"
#include "rooms.h"
#include "items.h"
#include "terminal.h"
#include "utils.h"

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
    .kind = ROOM_SAFE
  }
};

RoomAppearanceTemplate easy_room_appearance_templates[] = {
  {
    .name = "Glade",
    .description = "This is a glade...",
    .kind = ROOM_EASY
  },
  {
    .name = "Clearing",
    .description = "This is a clearing...",
    .kind = ROOM_EASY
  },
  {
    .name = "Hollow",
    .description = "This is a hollow...",
    .kind = ROOM_EASY
  },
};

RoomAppearanceTemplate normal_room_appearance_templates[] = {
  {
    .name = "Ridge",
    .description = "This is a ridge...",
    .kind = ROOM_NORMAL
  },
  {
    .name = "Creek Bed",
    .description = "This is a creek bed...",
    .kind = ROOM_NORMAL
  },
  {
    .name = "Undergrowth",
    .description = "This is an undergrowth...",
    .kind = ROOM_NORMAL
  },
  {
    .name = "Fork",
    .description = "This is a Fork...",
    .kind = ROOM_NORMAL
  },
  {
    .name = "Abandoned Camp",
    .description = "This is an Abandoned Camp...",
    .kind = ROOM_NORMAL
  },
};

RoomAppearanceTemplate hard_room_appearance_templates[] = {
  {
    .name = "Main Road",
    .description = "This is Main Road...",
    .kind = ROOM_HARD
  },
  {
    .name = "Wens Pass",
    .description = "This is Wens Pass...",
    .kind = ROOM_HARD
  },
  {
    .name = "Wens Village",
    .description = "This is Wens Village...",
    .kind = ROOM_HARD
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
    .kind = ROOM_SAFE
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
    .kind = ROOM_EASY
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
    .kind = ROOM_NORMAL
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
    .kind = ROOM_HARD
  }
};

const char *direction_to_string(DirectionKind direction_kind) {
  switch (direction_kind) {
    case DIRECTION_NORTH: return "north";
    case DIRECTION_EAST: return "east";
    case DIRECTION_WEST: return "west";
    case DIRECTION_SOUTH: return "south";
    default: return "unknown";
  }
}

char direction_to_char(DirectionKind direction_kind) {
  switch (direction_kind) {
    case DIRECTION_NORTH: return 'N';
    case DIRECTION_EAST: return 'E';
    case DIRECTION_WEST: return 'W';
    case DIRECTION_SOUTH: return 'S';
    default: return '?';
  }
}

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

int remove_item_from_room(Room *room, Item *item) {
  if (room == NULL || item == NULL) {
    return ITEM_ADD_TO_ROOM_INVALID;
  }

  for (int i = 0; i < room->items_count; i++) {
    if (room->items[i]->id == item->id) {
      if (i != room->items_count-1) {
        room->items[i] = room->items[room->items_count-1];
      }
      room->items[room->items_count-1] = NULL;
      room->items_count--;
      return ITEM_REMOVE_FROM_ROOM_SUCCESS;
    }
  }

  room->items[room->items_count] = item;
  room->items_count++;
  return ITEM_ADD_TO_ROOM_SUCCESS;
}

void explore_room(Player *player, DirectionKind direction) {
  Room **next = NULL;
  int current_x = player->current_room->x;
  int current_y = player->current_room->y;
  if (direction == DIRECTION_NORTH) {
    next = &player->map->grid[current_x][current_y + 1];
  } else if (direction == DIRECTION_EAST) {
    next = &player->map->grid[current_x + 1][current_y];
  } else if (direction == DIRECTION_WEST) {
    next = &player->map->grid[current_x - 1][current_y];
  } else if (direction == DIRECTION_SOUTH) {
    next = &player->map->grid[current_x][current_y - 1];
  }

  if (*next == NULL) {
    if (player->visited_rooms->count < MAX_ROOMS) {
      print_text(PRINT_NORMAL5, "Generating room...\n");
      *next = build_room(player, direction);
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
  if (player->current_room->kind == ROOM_SAFE) {
    print_text(PRINT_NORMAL5, "[Entered %s]\n", player->current_room->name);
    print_text(PRINT_NORMAL5, "%s\n", player->current_room->description);
  } else {
    print_text(PRINT_NORMAL5, "[Entered %s]\n", player->current_room->name);
    print_text(PRINT_NORMAL5, "%s\n", player->current_room->description);
    print_text(PRINT_NORMAL5, "You see a %s\n", player->current_room->enemy->name);
    print_text(PRINT_NORMAL5, "Health: %d\n", player->current_room->enemy->health);
  }
}

Room *build_room(Player *player, DirectionKind direction) {
  Room *new_room;
  if (player->current_room == NULL) {
    new_room = malloc(sizeof(Room));
    if (new_room == NULL) {
      return NULL;
    }
    new_room->kind = ROOM_SAFE;
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
      case ROOM_SAFE:
        max_room_kind = MAX_SAFE_ROOMS;
        room_kind_count = room_kind_counter.safe;
        break;
      case ROOM_EASY:
        max_room_kind = MAX_EASY_ROOMS;
        room_kind_count = room_kind_counter.easy;
        break;
      case ROOM_NORMAL:
        max_room_kind = MAX_NORMAL_ROOMS;
        room_kind_count = room_kind_counter.normal;
        break;
      case ROOM_HARD:
        max_room_kind = MAX_HARD_ROOMS;
        room_kind_count = room_kind_counter.hard;
        break;
      case ROOM_UNKNOWN:
        return NULL;
    }

    if (room_kind_count >= max_room_kind) {
      current_room_kind = (RoomKind)(current_room_kind + 1);
      switch (current_room_kind) {
        case ROOM_SAFE:
          max_room_kind = MAX_SAFE_ROOMS;
          break;
        case ROOM_EASY:
          max_room_kind = MAX_EASY_ROOMS;
          break;
        case ROOM_NORMAL:
          max_room_kind = MAX_NORMAL_ROOMS;
          break;
        case ROOM_HARD:
          max_room_kind = MAX_HARD_ROOMS;
          break;
        case ROOM_UNKNOWN:
          return NULL;
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
      case ROOM_SAFE:
        room_kind_counter.safe++;
        fateful_room_appearance = safe_room_appearance_templates[appearance_index];
        fateful_room_contents = safe_room_contents_templates[0];
        break;
      case ROOM_EASY:
        room_kind_counter.easy++;
        fateful_room_appearance = easy_room_appearance_templates[appearance_index];
        fateful_room_contents = easy_room_contents_templates[0];
        break;
      case ROOM_NORMAL:
        room_kind_counter.normal++;
        fateful_room_appearance = normal_room_appearance_templates[appearance_index];
        fateful_room_contents = normal_room_contents_templates[0];
        break;
      case ROOM_HARD:
        room_kind_counter.hard++;
        fateful_room_appearance = hard_room_appearance_templates[room_kind_counter.hard - 1];
        fateful_room_contents = hard_room_contents_templates[0];
        break;
      case ROOM_UNKNOWN:
        return NULL;
    }

    strcpy(new_room->name, fateful_room_appearance.name);
    strcpy(new_room->description, fateful_room_appearance.description);
    int fateful_max_health = rand() % (fateful_room_contents.enemy_max_health - fateful_room_contents.enemy_min_health + 1) + fateful_room_contents.enemy_min_health;
    int fateful_attack = rand() % (fateful_room_contents.enemy_max_attack - fateful_room_contents.enemy_min_attack + 1) + fateful_room_contents.enemy_min_attack;
    int fateful_defense = rand() % (fateful_room_contents.enemy_max_defense - fateful_room_contents.enemy_min_defense + 1) + fateful_room_contents.enemy_min_defense;
    Enemy *enemy = create_enemy(fateful_room_contents.enemy_name, fateful_max_health, fateful_attack, fateful_defense);
    new_room->enemy = enemy;
  }

  if (player->map == NULL) {
    Map *new_map = calloc(1, sizeof(Map));
    if (new_map == NULL) {
      return NULL;
    }
    player->map = new_map;
    new_room->x = rand() % MAX_AREA_WIDTH;
    print_text(PRINT_FAST3, "x: [%d]\n", new_room->x);
    new_room->y = rand() % MAX_AREA_HEIGHT;
    print_text(PRINT_FAST3, "y: [%d]\n", new_room->y);
    player->map->grid[new_room->x][new_room->y] = new_room;
  }

  switch (direction) {
    case DIRECTION_NORTH: {
      new_room->x = player->current_room->x;
      new_room->y = player->current_room->y + 1;
      player->map->grid[new_room->x][new_room->y] = new_room;
    }
    case DIRECTION_EAST: {
      new_room->x = player->current_room->x + 1;
      new_room->y = player->current_room->y;
      player->map->grid[new_room->x][new_room->y] = new_room;
    }
    case DIRECTION_WEST:{
      new_room->x = player->current_room->x - 1;
      new_room->y = player->current_room->y;
      player->map->grid[new_room->x][new_room->y] = new_room;
    }
    case DIRECTION_SOUTH: {
      new_room->x = player->current_room->x;
      new_room->y = player->current_room->y - 1;
      player->map->grid[new_room->x][new_room->y] = new_room;
    }
    default:
      break;
  }

  new_room->id = player->visited_rooms->count;
  new_room->visited = 0;

  return new_room;
}
