#pragma once
#include <string>
#include <vector>

enum class ItemType {
    Heal,      // restores `power` health
    Strength,  // permanently adds `power` attack
};

struct Item {
    std::string name;
    ItemType type;
    int power;
    int price;
};

inline const std::vector<Item> ITEM_CATALOG = {
    //  name             type               power  price
    {"Small Potion",   ItemType::Heal,      30,    15},
    {"Large Potion",   ItemType::Heal,      70,    35},
    {"Strength Tonic", ItemType::Strength,   2,    60},
};

inline std::string describeItem(const Item& item) {
    switch (item.type) {
        case ItemType::Heal:     return "heals " + std::to_string(item.power) + " HP";
        case ItemType::Strength: return "+" + std::to_string(item.power) + " attack forever";
    }
    return "";
}
