#pragma once

#include "entities.h"

#define MAX_AREAS 12
#define MAX_SAFE_AREAS 1
#define MAX_EASY_AREAS 3
#define MAX_NORMAL_AREAS 5
#define MAX_HARD_AREAS 3
#define MAX_AREA_ITEMS 3

typedef struct AreaKindCounter {
  int safe;
  int easy;
  int normal;
  int hard;
} AreaKindCounter;

typedef struct AreaKindLimits {
  int safe;
  int easy;
  int normal;
  int hard;
} AreaKindLimits;

typedef struct Area {
  EntityKind entity_kind;
  AreaKind area_kind;
  int id;
  char name[50];
  char description[256];
  struct Area *north;
  struct Area *east;
  struct Area *west;
  struct Area *south;
  Enemy *enemy;
  Item *items[MAX_AREA_ITEMS];
  int items_count;
  int visited;
} Area;

typedef struct AreaAppearanceTemplate {
  char *name;
  char *description;
  AreaKind kind;
} AreaAppearanceTemplate;

typedef struct AreaContentsTemplate {
  char *enemy_name;
  AreaKind kind;
  int enemy_max_health;
  int enemy_min_health;
  int enemy_max_attack;
  int enemy_min_attack;
  int enemy_max_defense;
  int enemy_min_defense;
} AreaContentsTemplate;

typedef struct VisitedAreas {
  Area *visited[MAX_AREAS];
  int count;
} VisitedAreas;

extern char *directions[];

void explore_area(Player *player, int choice);
Area *generate_area(Player *player, int choice);
int add_item_to_area(Area *area, Item *item);
int remove_item_from_area(Area *area, Item *item);
void view_map(Player *player);
