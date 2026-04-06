#pragma once

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

typedef enum RoomKind {
  ROOM_SAFE,
  ROOM_EASY,
  ROOM_NORMAL,
  ROOM_HARD,
  ROOM_UNKNOWN,
} RoomKind;

typedef enum ItemKind {
  ITEM_WEAPON,
  ITEM_SHIELD,
  ITEM_POTION,
  ITEM_ACCESSORY,
  ITEM_UNKNOWN,
} ItemKind;

typedef struct BaseEntity {
  EntityKind entity_kind;
  int id;
  char *name;
  char *description;
} BaseEntity;
