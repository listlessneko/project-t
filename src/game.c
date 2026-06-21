#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entities.h"
#include "menu.h"
#include "items.h"
#include "inventory.h"
#include "terminal.h"
#include "game.h"
#include "utils.h"
#include "rooms.h"

Player *create_player() {
  Player *player = malloc(sizeof(Player));
  if (player == NULL) {
    return NULL;
  }
  player->level = 1;
  player->exp = 0;
  player->health = 24;
  player->max_health = 30;
  player->attack = 5;
  player->defense = 3;
  player->accuracy = 75;
  player->dodge = 20;
  player->gold = 0;
  player->inventory_count = 0;

  Item *sword = create_item(ITEM_WEAPON, "Sword", 0, 1, 0);
  equip_item(player, sword);

  Item *shield = create_item(ITEM_SHIELD, "Shield", 0, 0, 1);
  equip_item(player, shield);

  Item *axe = create_item(ITEM_WEAPON, "Axe", 0, 1, 0);
  add_item_to_player_inventory(player, axe);

  Item *round_shield = create_item(ITEM_SHIELD, "Round Shield", 0, 0, 1);
  add_item_to_player_inventory(player, round_shield);

  Item *dagger = create_item(ITEM_WEAPON, "Dagger", 0, 1, 0);
  add_item_to_player_inventory(player, dagger);

  Item *rectangle_shield = create_item(ITEM_SHIELD, "Rectangle Shield", 0, 0, 1);
  add_item_to_player_inventory(player, rectangle_shield);

  Item *short_sword = create_item(ITEM_WEAPON, "Short Sword", 0, 1, 0);
  add_item_to_player_inventory(player, short_sword);

  Item *square_shield = create_item(ITEM_SHIELD, "Square Shield", 0, 0, 1);
  add_item_to_player_inventory(player, square_shield);

  Item *long_sword = create_item(ITEM_WEAPON, "Long Sword", 0, 1, 0);
  add_item_to_player_inventory(player, long_sword);

  Item *triangle_shield = create_item(ITEM_SHIELD, "Triangle Shield", 0, 0, 1);
  add_item_to_player_inventory(player, triangle_shield);

  player->current_room = NULL;
  player->map = NULL;

  initialize_visited_rooms(player);

  player->current_menu = &main_menu;

  return player;
};

void initialize_visited_rooms(Player *player) {
  player->visited_rooms = malloc(sizeof(VisitedRooms));
  if (player->visited_rooms == NULL) {
    return;
  }
  player->visited_rooms->count = 0;
  return;
}

Enemy *create_enemy(char *name, EnemyBehaviorKind behavior, int max_health, int attack, int defense, int accuracy, int dodge) {
  Enemy *enemy = malloc(sizeof(Enemy));
  if (enemy == NULL) {
    return NULL;
  }
  enemy->entity_kind = ENTITY_ENEMY;
  strcpy(enemy->name, name);
  enemy->behavior = behavior;
  enemy->max_health = max_health;
  enemy->health = max_health;
  enemy->attack = attack;
  enemy->defense = defense;
  enemy->accuracy = accuracy;
  enemy->dodge = dodge;
  return enemy;
};

void destroy_enemy(Enemy *enemy) {
  free(enemy);
}

void start_game(Player *player) {
  srand(time(NULL));
  print_text(PRINT_NORMAL5, "What is your name, traveler?\n");

  read_input(player->name, 32, INPUT_STR);

  print_text(PRINT_NORMAL5, "Hello, %s. It is time to continue your journey.\n", player->name);
  print_text(PRINT_VERY_SLOW50, "...\n");
  print_text(PRINT_NORMAL5, "You find yourself sitting in the middle of a forest.\n");
  print_text(PRINT_NORMAL5, "You've been resting your strained back against a large tree while letting your mind wander off.\n");
  print_text(PRINT_NORMAL5, "The breaking sound of a distant tree branch snaps you back to reality.\n");
  print_text(PRINT_NORMAL5, "You have to keep moving before the sun sets.\n");

  player->map = NULL;
  player->current_room = NULL;
  player->current_room = build_room(player, DIRECTION_NONE);
  player->current_room->visited = 1;
  player->visited_rooms->visited[0] = player->current_room;
  player->visited_rooms->count = 1;
  print_text(PRINT_NORMAL5, "[Entered %s]\n", player->current_room->name);
  print_text(PRINT_NORMAL5, "%s\n", player->current_room->description);
}

void game_loop(Player *player) {
  while(playing(player)) {}
}

int combat_ensues(Player *player, Enemy *enemy) {
  return player->health > 0 && enemy->health > 0;
}

int clamp(int value, int min, int max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

int hit_chance(int base, int accuracy, int dodge) {
  int value = base + accuracy - dodge;
  return clamp(value, MIN_HIT_CHANCE, MAX_HIT_CHANCE);
}

int attack_lands(int chance) {
  int r = rand() % 100;

  return r < chance;
}

int damage_dealt(Player *player, Enemy *enemy, int player_is_attacker, int defense_mode) {
  if (player == NULL || enemy == NULL) {
    return 0;
  }

  int attack = 0;
  int defense = 0;
  int damage = 0;

  if (player_is_attacker) {
    attack = player->attack;
    defense = defense_mode ? enemy->defense : (int)(enemy->defense * PARTIAL_DEFENSE_FRACTION);
  } else {
    attack = enemy->attack;
    defense = defense_mode ? player->defense : (int)(player->defense * PARTIAL_DEFENSE_FRACTION);
  }
  damage = attack - defense;
  damage = damage < 1 ? 0 : damage;
  return damage;
}

void deal_damage(EntityKind entity_kind, void *entity, int damage) {
  switch (entity_kind) {
    case ENTITY_PLAYER: {
      Player *player = (Player *)(entity);
      int health = player->health - damage;
      player->health = health < 0 ? 0 : health;
      return;
    }
    case ENTITY_ENEMY: {
      Enemy *enemy = (Enemy *)(entity);
      int health = enemy->health - damage;
      enemy->health = health < 0 ? 0 : health;
      return;
    }
    default:
      return;
  }
}

void combat(Player *player, Enemy *enemy) {
  if (player == NULL || enemy == NULL) {
    return;
  }

  // roll for initiative
  int initiative = rand() % 2;

  while(combat_ensues(player, enemy)) {
    player->current_menu = &combat_menu;
    display_menu(player);
    char choice[2];
    read_input(choice, sizeof(choice), INPUT_CHAR);
    MenuNode *menu_node = parse_player_choice(player, choice);

    if (menu_node == NULL) {
      print_text(PRINT_NORMAL5, "Focus!\n");
      continue;
    }

    int player_defense_mode = 0;
    int player_attempted_to_flee = 0;
    int enemy_defense_mode = rand() % 2 ? 1 : 0;

    switch (menu_node->node_kind) {
      case NODE_ACTION: {
        switch (menu_node->data_kind.action_kind) {
          case ACTION_ATTACK: {
            break;
          }
          case ACTION_DEFEND: {
            player_defense_mode = 1;
            break;
          }
          case ACTION_USE_INVENTORY_ITEM:
          case ACTION_FLEE: {
            player_attempted_to_flee = 1;
            print_text(PRINT_NORMAL5, "You cannot run from this challenge...\n");
            break;
          }
          default:
            break;
        }
      }
      default:
        break;
    }

    if (!player_attempted_to_flee) {
      if (initiative) {
        if (!player_defense_mode) {
          if (enemy_defense_mode) {
            print_text(PRINT_NORMAL5, "The %s shifts into a defensive stance...\n", enemy->name);
          }
          int player_chance_to_hit = hit_chance(BASE_HIT_CHANCE, player->accuracy, enemy->dodge);
          int player_hit_landed = attack_lands(player_chance_to_hit);
          if (player_hit_landed) {
            int damage = damage_dealt(player, enemy, 1, enemy_defense_mode);
            if (damage > 0) {
              deal_damage(ENTITY_ENEMY, enemy, damage);
              print_text(PRINT_NORMAL5, "You land an attack! (-%d)\n", damage);
              if (enemy->health <= 0) {
                print_text(PRINT_NORMAL5, "You kill the %s.\n", enemy->name);
                break;
              }
            } else {
              print_text(PRINT_NORMAL5, "You barely left a scratch... (0)\n");
            }
          } else {
            print_text(PRINT_NORMAL5, "You missed! (0)\n");
          }
        } else {
          print_text(PRINT_NORMAL5, "You brace for impact...\n");
        }
        if (!enemy_defense_mode) {
          int enemy_chance_to_hit = hit_chance(BASE_HIT_CHANCE, enemy->accuracy, player->dodge);
          int enemy_hit_landed = attack_lands(enemy_chance_to_hit);
          if (enemy_hit_landed) {
            int damage = damage_dealt(player, enemy, 0, player_defense_mode);
            if (damage > 0) {
              deal_damage(ENTITY_PLAYER, player, damage);
              print_text(PRINT_NORMAL5, "You take a hit! (-%d)\n", damage);
            } else {
              print_text(PRINT_NORMAL5, "You deflected their attack! (0)\n");
            }
          } else {
            print_text(PRINT_NORMAL5, "You dodged their attack! (0)\n");
          }
        } else {
          print_text(PRINT_NORMAL5, "The %s shifts into a defensive stance...\n", enemy->name);
        }
      } else {
        if (!enemy_defense_mode) {
          if (player_defense_mode) {
            print_text(PRINT_NORMAL5, "You brace for impact...\n");
          }
          int enemy_chance_to_hit = hit_chance(BASE_HIT_CHANCE, enemy->accuracy, player->dodge);
          int enemy_hit_landed = attack_lands(enemy_chance_to_hit);
          if (enemy_hit_landed) {
            int damage = damage_dealt(player, enemy, 0, player_defense_mode);
            if (damage > 0) {
              deal_damage(ENTITY_PLAYER, player, damage);
              print_text(PRINT_NORMAL5, "You take a hit! (-%d)\n", damage);
            } else {
              print_text(PRINT_NORMAL5, "You deflected their attack! (0)\n");
            }
          } else {
            print_text(PRINT_NORMAL5, "You dodged their attack! (0)\n");
          }
        } else {
          print_text(PRINT_NORMAL5, "The %s shifts into a defensive stance...\n", enemy->name);
        }
        if (!player_defense_mode) {
          int player_chance_to_hit = hit_chance(BASE_HIT_CHANCE, player->accuracy, enemy->dodge);
          int player_hit_landed = attack_lands(player_chance_to_hit);
          if (player_hit_landed) {
            int damage = damage_dealt(player, enemy, 1, enemy_defense_mode);
            if (damage > 0) {
              deal_damage(ENTITY_ENEMY, enemy, damage);
              print_text(PRINT_NORMAL5, "You land an attack! (-%d)\n", damage);
              if (enemy->health <= 0) {
                print_text(PRINT_NORMAL5, "You kill the %s.\n", enemy->name);
                break;
              }
            } else {
              print_text(PRINT_NORMAL5, "You barely left a scratch... (0)\n");
            }
          } else {
            print_text(PRINT_NORMAL5, "You missed! (0)\n");
          }
        }
      }
    }
    print_text(PRINT_NORMAL5, "%s's HP: %d/%d\n", player->name, player->health, player->max_health);
    print_text(PRINT_NORMAL5, "%s's HP: %d/%d\n", enemy->name, enemy->health, enemy->max_health);
  }
}
