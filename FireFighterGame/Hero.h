#pragma once

// Structure for items
struct BackpackItem {
    std::string name;
    std::string description;
    int id;
};

// Structure for abilities
struct Abilities {
    std::string name;
    std::string description;
    int id;
    bool active;
};

// Firefighter class
class Firefighter {
public:
    int score;
    std::vector<BackpackItem> backpack;
    std::vector<Abilities> abilities;

    Firefighter(int initialScore);
};

// Damage from items
int dmgByItem(int id);
// Creating an ability structure
void addAbilityToBackpack(Firefighter& firefighter, const std::string& name, const std::string& description, int id);
// Creating an item structure
void addItemToBackpack(Firefighter& firefighter, const std::string& name, const std::string& description, int id);
// Adding abilities to the character
void addAbilities(int item, Firefighter& firefighter);
// Adding items to the backpack
void addItems(int item, Firefighter& firefighter);
// Using a given item
double usingItem(Firefighter& firefighter, double fire, bool crit, bool lastStage, bool& blow);
// Using a given ability
int usingAbility(Firefighter& firefighter);
// Fight engine
void fightEngine(double hpFire, int stage, Firefighter& firefighter);
