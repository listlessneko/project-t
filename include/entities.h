#pragma once

#define MAX_NAME_LEN 128
#define MAX_DESCRIPTION_LEN 512
#define MAX_STATS_LEN 512

typedef struct Player Player;
typedef struct Enemy Enemy;
typedef struct Room Room;
typedef struct Item Item;

typedef enum EntityKind {
  ENTITY_PLAYER,
  ENTITY_ENEMY,
  ENTITY_ROOM,
  ENTITY_ITEM,
  ENTITY_UNKNOWN,
} EntityKind;

typedef enum PlayerKind {
  PLAYER_ADVENTURER,
  PLAYER_UNKNOWN,
} PlayerKind;

typedef enum EnemyKind {
  ENEMY_EASY,
  ENEMY_NORMAL,
  ENEMY_HARD,
  ENEMY_UNKNOWN,
} EnemyKind;

typedef enum EnemyBehaviorKind {
  BEHAVIOR_COWARDLY,
  BEHAVIOR_AGGRESSIVE,
  BEHAVIOR_MIXED,
  BEHAVIOR_UNKNOWN
} EnemyBehaviorKind;

typedef enum RoomKind {
  ROOM_BARRIER,
  ROOM_SAFE,
  ROOM_EASY,
  ROOM_NORMAL,
  ROOM_HARD,
  ROOM_UNKNOWN,
} RoomKind;

typedef enum ItemKind {
  ITEM_WEAPON,
  ITEM_SHIELD,
  ITEM_ACCESSORY,
  ITEM_POTION,
  ITEM_UNKNOWN,
} ItemKind;

typedef struct BaseEntity {
  EntityKind entity_kind;
  int id;
  char name[MAX_NAME_LEN];
  char description[MAX_DESCRIPTION_LEN];
} BaseEntity;
