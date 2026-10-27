#include "Monster.h"

#include "Utils.h"

Monster spawnMonster(int playerLevel) {
    // 1. Keep only the monsters allowed at this level, and add up their weights.
    std::vector<const MonsterType*> allowed;
    int totalWeight = 0;
    for (const MonsterType& type : MONSTER_TYPES) {
        if (playerLevel >= type.minLevel) {
            allowed.push_back(&type);
            totalWeight += type.spawnWeight;
        }
    }

    // 2. Weighted random pick ("roulette wheel"): roll a number, then walk the
    //    list subtracting weights until the roll runs out. A monster with
    //    weight 40 is four times as likely as one with weight 10.
    int roll = utils::randomInt(1, totalWeight);
    const MonsterType* picked = allowed.back();
    for (const MonsterType* type : allowed) {
        roll -= type->spawnWeight;
        if (roll <= 0) {
            picked = type;
            break;
        }
    }

    // 3. Build the monster, adding 10% to its stats per player level above 1.
    int bonusPercent = (playerLevel - 1) * 10;
    auto scale = [bonusPercent](int value) { return value + value * bonusPercent / 100; };

    Monster monster;
    monster.name = picked->name;
    monster.maxHealth = scale(picked->health);
    monster.health = monster.maxHealth;
    monster.attack = scale(picked->attack);
    monster.defense = picked->defense;
    monster.goldReward = scale(picked->gold);
    monster.xpReward = picked->xp;
    return monster;
}
