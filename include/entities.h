#pragma once

typedef enum EntityKind {
  ENTITY_PLAYER,
  ENTITY_ENEMY,
  ENTITY_ITEM,
  ENTITY_ROOM,
  ENTITY_UNKNOWN,
} EntityKind;

typedef enum PlayerKind {
  ADVENTURER,
} PlayerKind;

typedef enum EnemyKind {
  ENEMY_EASY,
  ENEMY_NORMAL,
  ENEMY_HARD,
  ENEMY_UNKNOWN,
} EnemyKind;

typedef enum ItemKind {
  WEAPON,
  SHIELD,
  POTION,
  ACCESSORY
} ItemKind;

typedef enum RoomKind {
  ROOM_SAFE,
  ROOM_EASY,
  ROOM_NORMAL,
  ROOM_HARD,
} RoomKind;

typedef struct Player Player;
typedef struct Enemy Enemy;
typedef struct Item Item;
typedef struct Room Room;
