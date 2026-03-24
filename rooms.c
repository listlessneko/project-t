#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "rooms.h"
#include "terminal.h"
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
    .items = NULL,
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
    .items = NULL,
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
    .items = NULL,
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
    .items = NULL,
    .kind = HARD
  }
};


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

  if (player->visited_rooms->count < MAX_ROOMS) {
    if (*next == NULL) {
      printf("visited_count: %d\n", player->visited_rooms->count);
      printf("max_count: %d\n", MAX_ROOMS);
      *next = generate_room(player, choice);
      player->visited_rooms->visited[(*next)->id] = *next;
      player->visited_rooms->visited[(*next)->id]->visited = 1;
      player->visited_rooms->count++;
    }
    player->current_room = *next;
    if (player->current_room->kind == SAFE) {
      print_text(PRINT_NORMAL5,
                 "[Entered %s]\n",
                 "%s\n",
                 player->current_room->name,
                 player->current_room->description
                 );
    } else {
      print_text(PRINT_NORMAL5, "[Entered %s]\n", player->current_room->name);
      print_text(PRINT_NORMAL5, "%s\n", player->current_room->description);
      print_text(PRINT_NORMAL5, "You see a %s\n", player->current_room->enemy->name);
      print_text(PRINT_NORMAL5, "Health: %d\n", player->current_room->enemy->health);
    }
  } else {
    print_text(PRINT_NORMAL5, "You've reached a dead end. Somehow...\n");
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
    printf("visited_count: %d\n", visited_count);
    RoomKind current_room_kind = player->current_room->kind;
    printf("current_room_kind: %d\n", current_room_kind);

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

    printf("max_room_kind: %d\n", max_room_kind);
    printf("room_kind_count: %d\n", room_kind_count);

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
      if (current_room_kind >= HARD) {
        return NULL;
      }
    }

    new_room = malloc(sizeof(Room));
    if (new_room == NULL) {
      return NULL;
    }

    RoomAppearanceTemplate *room_kind_appearance_templates;
    RoomContentsTemplate *room_kind_contents_templates;
    printf("current_room_kind: %d\n", current_room_kind);
    switch (current_room_kind) {
      case SAFE:
        room_kind_counter.safe++;
        room_kind_appearance_templates = safe_room_appearance_templates;
        room_kind_contents_templates = safe_room_contents_templates;
        break;
      case EASY:
        room_kind_counter.easy++;
        room_kind_appearance_templates = easy_room_appearance_templates;
        room_kind_contents_templates = easy_room_contents_templates;
        break;
      case NORMAL:
        room_kind_counter.normal++;
        room_kind_appearance_templates = normal_room_appearance_templates;
        room_kind_contents_templates = normal_room_contents_templates;
        break;
      case HARD:
        room_kind_counter.hard++;
        room_kind_appearance_templates = hard_room_appearance_templates;
        room_kind_contents_templates = hard_room_contents_templates;
        break;
    }

    int appearance_index = rand() % max_room_kind;
    printf("appearance_index: %d\n", appearance_index);
    RoomAppearanceTemplate fateful_room_appearance = room_kind_appearance_templates[appearance_index];
    printf("Room Name: %s\n", fateful_room_appearance.name);
    strcpy(new_room->name, fateful_room_appearance.name);
    strcpy(new_room->description, fateful_room_appearance.description);

    RoomContentsTemplate fateful_room_contents = room_kind_contents_templates[0];
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
  new_room->id = player->visited_rooms->count + 1;
  new_room->visited = 0;
  return new_room;
}

int explore(Player *player) {
  print_text(PRINT_FAST3,
             "[1] Go north\n"
             "[2] Go east\n"
             "[3] Go west\n"
             "[4] Go south\n"
             );

  char choice[32];
  read_input(choice, sizeof(choice));

  int choice_int = atoi(choice);
  if (choice_int >= 1 && choice_int <= 4) {
    explore_room(player, choice_int);
  } else if (strcmp(choice, "quit") == 0) {
    print_text(PRINT_NORMAL5, "You open your eyes and realize it was just a dream.\n");
    return 1;
  } else {
    print_text(PRINT_NORMAL5, "You stare off into the distance...\n");
  }
  return 0;
}

