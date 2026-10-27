#pragma once
#include <string>
#include <vector>

#include "Character.h"

struct Monster : Character {
    int goldReward = 0;
    int xpReward = 0;
};

// A blueprint for creating monsters.
struct MonsterType {
    std::string name;
    int health;
    int attack;
    int defense;
    int gold;
    int xp;
    int minLevel;     // player level needed before this monster can appear
    int spawnWeight;  // higher number = appears more often
};

// Every monster in the dungeon. To add a new monster, just add a line here.
inline const std::vector<MonsterType> MONSTER_TYPES = {
    //  name             HP  ATK DEF  gold  XP  minLvl  weight
    {"Giant Rat",        20,   6,  0,    5, 10,      1,     40},
    {"Skeleton",         35,   9,  2,   12, 20,      1,     30},
    {"Goblin Thief",     30,  11,  1,   25, 25,      2,     20},
    {"Cave Troll",       70,  14,  4,   40, 50,      3,     10},
    {"Shadow Wraith",    55,  18,  3,   60, 70,      4,      8},
};

// Picks a random monster suited to the player's level and makes it a bit
// stronger for every level the player has gained.
Monster spawnMonster(int playerLevel);
