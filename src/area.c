#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "status.h"
#include "game.h"
#include "area.h"
#include "item.h"
#include "utils.h"

char *directions[] = { "north", "east", "west", "south" };

AreaKindCounter area_kind_counter = {
  .safe = 0,
  .easy = 0,
  .normal = 0,
  .hard = 0
};

AreaAppearanceTemplate safe_area_appearance_templates[] = {
  {
    .name = "Grove",
    .description = "This is a grove...",
    .kind = AREA_SAFE
  }
};

AreaAppearanceTemplate easy_area_appearance_templates[] = {
  {
    .name = "Glade",
    .description = "This is a glade...",
    .kind = AREA_EASY
  },
  {
    .name = "Clearing",
    .description = "This is a clearing...",
    .kind = AREA_EASY
  },
  {
    .name = "Hollow",
    .description = "This is a hollow...",
    .kind = AREA_EASY
  },
};

AreaAppearanceTemplate normal_area_appearance_templates[] = {
  {
    .name = "Ridge",
    .description = "This is a ridge...",
    .kind = AREA_NORMAL
  },
  {
    .name = "Creek Bed",
    .description = "This is a creek bed...",
    .kind = AREA_NORMAL
  },
  {
    .name = "Undergrowth",
    .description = "This is an undergrowth...",
    .kind = AREA_NORMAL
  },
  {
    .name = "Fork",
    .description = "This is a Fork...",
    .kind = AREA_NORMAL
  },
  {
    .name = "Abandoned Camp",
    .description = "This is an Abandoned Camp...",
    .kind = AREA_NORMAL
  },
};

AreaAppearanceTemplate hard_area_appearance_templates[] = {
  {
    .name = "Main Road",
    .description = "This is Main Road...",
    .kind = AREA_HARD
  },
  {
    .name = "Wens Pass",
    .description = "This is Wens Pass...",
    .kind = AREA_HARD
  },
  {
    .name = "Wens Village",
    .description = "This is Wens Village...",
    .kind = AREA_HARD
  },
};

AreaContentsTemplate safe_area_contents_templates[] = {
  {
    .enemy_max_health = -1,
    .enemy_min_health = -1,
    .enemy_max_attack = -1,
    .enemy_min_attack = -1,
    .enemy_max_defense = -1,
    .enemy_min_defense = -1,
    .kind = AREA_SAFE
  }
};

AreaContentsTemplate easy_area_contents_templates[] = {
  {
    .enemy_name = "Bandit",
    .enemy_max_health = 5,
    .enemy_min_health = 3,
    .enemy_max_attack = 2,
    .enemy_min_attack = 1,
    .enemy_max_defense = 2,
    .enemy_min_defense = 1,
    .kind = AREA_EASY
  }
};

AreaContentsTemplate normal_area_contents_templates[] = {
  {
    .enemy_name = "Raiders",
    .enemy_max_health = 8,
    .enemy_min_health = 5,
    .enemy_max_attack = 4,
    .enemy_min_attack = 2,
    .enemy_max_defense = 4,
    .enemy_min_defense = 2,
    .kind = AREA_NORMAL
  }
};

AreaContentsTemplate hard_area_contents_templates[] = {
  {
    .enemy_name = "Warrior",
    .enemy_max_health = 12,
    .enemy_min_health = 8,
    .enemy_max_attack = 8,
    .enemy_min_attack = 5,
    .enemy_max_defense = 8,
    .enemy_min_defense = 5,
    .kind = AREA_HARD
  }
};

int add_item_to_area(Area *area, Item *item) {
  if (area == NULL || item == NULL) {
    return ITEM_ADD_TO_AREA_INVALID;
  }

  if (area->items_count >= MAX_AREA_ITEMS) {
    return AREA_ITEMS_FULL;
  }
  area->items[area->items_count] = item;
  area->items_count++;
  return ITEM_ADD_TO_AREA_SUCCESS;
}

int remove_item_from_area(Area *area, Item *item) {
  if (area == NULL || item == NULL) {
    return ITEM_REMOVE_FROM_AREA_INVALID;
  }

  for (int i = 0; i < area->items_count; i++) {
    if (area->items[i]->id == item->id) {
      if (i != area->items_count-1) {
        area->items[i] = area->items[area->items_count-1];
      }
      area->items[area->items_count-1] = NULL;
      area->items_count--;
      return ITEM_REMOVE_FROM_AREA_SUCCESS;
    }
  }
  return ITEM_REMOVE_FROM_AREA_ERROR;
}

void explore_area(Player *player, int choice) {
  Area **next = NULL;
  if (choice == 1) {
    next = &player->current_area->north;
  } else if (choice == 2) {
    next = &player->current_area->east;
  } else if (choice == 3) {
    next = &player->current_area->west;
  } else if (choice == 4) {
    next = &player->current_area->south;
  }

  if (*next == NULL) {
    if (player->visited_areas->count < MAX_AREAS) {
      *next = generate_area(player, choice);
      player->visited_areas->visited[(*next)->id] = *next;
      player->visited_areas->visited[(*next)->id]->visited = 1;
      player->visited_areas->count++;
      player->current_area = *next;
    } else {
      print_text(PRINT_NORMAL5, "You've reached a dead end. Somehow...\n");
    }
  } else {
    player->current_area = *next;
  }
  if (player->current_area->area_kind == AREA_SAFE) {
    print_text(PRINT_NORMAL5, "[Entered %s]\n", player->current_area->name);
    print_text(PRINT_NORMAL5, "%s\n", player->current_area->description);
  } else {
    print_text(PRINT_NORMAL5, "[Entered %s]\n", player->current_area->name);
    print_text(PRINT_NORMAL5, "%s\n", player->current_area->description);
    print_text(PRINT_NORMAL5, "You see a %s\n", player->current_area->enemy->name);
    print_text(PRINT_NORMAL5, "Health: %d\n", player->current_area->enemy->health);
  }
}

Area *generate_area(Player *player, int choice) {
  Area *new_area;
  if (player->current_area == NULL) {
    new_area = malloc(sizeof(Area));
    if (new_area == NULL) {
      return NULL;
    }
    new_area->area_kind = AREA_SAFE;
    area_kind_counter.safe++;
    strcpy(new_area->name, safe_area_appearance_templates[0].name);
    strcpy(new_area->description, safe_area_appearance_templates[0].description);
  } else {

    int visited_count = player->visited_areas->count;
    AreaKind current_area_kind = player->current_area->area_kind;

    if (visited_count > MAX_AREAS) {
      return NULL;
    }

    int max_area_kind = 0;
    int area_kind_count = 0;
    switch (current_area_kind) {
      case AREA_SAFE:
        max_area_kind = MAX_SAFE_AREAS;
        area_kind_count = area_kind_counter.safe;
        break;
      case AREA_EASY:
        max_area_kind = MAX_EASY_AREAS;
        area_kind_count = area_kind_counter.easy;
        break;
      case AREA_NORMAL:
        max_area_kind = MAX_NORMAL_AREAS;
        area_kind_count = area_kind_counter.normal;
        break;
      case AREA_HARD:
        max_area_kind = MAX_HARD_AREAS;
        area_kind_count = area_kind_counter.hard;
        break;
    }

    if (area_kind_count >= max_area_kind) {
      current_area_kind = (AreaKind)(current_area_kind + 1);
      switch (current_area_kind) {
        case AREA_SAFE:
          max_area_kind = MAX_SAFE_AREAS;
          break;
        case AREA_EASY:
          max_area_kind = MAX_EASY_AREAS;
          break;
        case AREA_NORMAL:
          max_area_kind = MAX_NORMAL_AREAS;
          break;
        case AREA_HARD:
          max_area_kind = MAX_HARD_AREAS;
          break;
      }
    }

    new_area = malloc(sizeof(Area));
    if (new_area == NULL) {
      return NULL;
    }

    new_area->area_kind = current_area_kind;
    int appearance_index = rand() % max_area_kind;
    AreaAppearanceTemplate fateful_area_appearance;
    AreaContentsTemplate fateful_area_contents;
    switch (new_area->area_kind) {
      case AREA_SAFE:
        area_kind_counter.safe++;
        fateful_area_appearance = safe_area_appearance_templates[appearance_index];
        fateful_area_contents = safe_area_contents_templates[0];
        break;
      case AREA_EASY:
        area_kind_counter.easy++;
        fateful_area_appearance = easy_area_appearance_templates[appearance_index];
        fateful_area_contents = easy_area_contents_templates[0];
        break;
      case AREA_NORMAL:
        area_kind_counter.normal++;
        fateful_area_appearance = normal_area_appearance_templates[appearance_index];
        fateful_area_contents = normal_area_contents_templates[0];
        break;
      case AREA_HARD:
        area_kind_counter.hard++;
        fateful_area_appearance = hard_area_appearance_templates[area_kind_counter.hard - 1];
        fateful_area_contents = hard_area_contents_templates[0];

    }

    strcpy(new_area->name, fateful_area_appearance.name);
    strcpy(new_area->description, fateful_area_appearance.description);
    int fateful_max_health = rand() % (fateful_area_contents.enemy_max_health - fateful_area_contents.enemy_min_health + 1) + fateful_area_contents.enemy_min_health;
    int fateful_attack = rand() % (fateful_area_contents.enemy_max_attack - fateful_area_contents.enemy_min_attack + 1) + fateful_area_contents.enemy_min_attack;
    int fateful_defense = rand() % (fateful_area_contents.enemy_max_defense - fateful_area_contents.enemy_min_defense + 1) + fateful_area_contents.enemy_min_defense;
    Enemy *enemy = create_enemy(fateful_area_contents.enemy_name, fateful_max_health, fateful_attack, fateful_defense);
    new_area->enemy = enemy;
  }

  if (choice == 1) {
    new_area->south = player->current_area;
  } else if (choice == 2) {
    new_area->west = player->current_area;
  } else if (choice == 3) {
    new_area->east = player->current_area;
  } else if (choice == 4) {
    new_area->north = player->current_area;
  }
  new_area->id = player->visited_areas->count;
  new_area->visited = 0;
  return new_area;
}

