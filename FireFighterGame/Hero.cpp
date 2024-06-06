#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <limits>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include "Hero.h"
#include "HelpingMethods.h"

Firefighter::Firefighter(int initialScore) : score(initialScore) {}

// Damage caused by items
int dmgByItem(int id) {
    int dmg = 0;
    switch (id) {
    case 1: // Fire extinguisher
        dmg = 30;
        break;
    case 2: // Water bomb
        dmg = 45;
        break;
    case 3: // Bucket
        dmg = 0;
        break;
    case 4: // Water blower
        dmg = 10;
        break;
    case 5: // Snake hose
        dmg = 75;
        break;
    }
    return dmg;
}

// Creating an ability structure
void addAbilityToBackpack(Firefighter& firefighter, const std::string& name, const std::string& description, int id) {
    Abilities abili = { name, description, id, true };
    firefighter.abilities.push_back(abili); // Adding to the list
}

// Creating an item structure
void addItemToBackpack(Firefighter& firefighter, const std::string& name, const std::string& description, int id) {
    BackpackItem newItem = { name, description, id };
    firefighter.backpack.push_back(newItem); // Adding to the list
}

// Adding abilities to the character
void addAbilities(int item, Firefighter& firefighter) {
    switch (item) {
    case 1:
        addAbilityToBackpack(firefighter, "Dragon deterrent", "Deter a dragon while extinguishing a fire", 0);
        break;
    case 2:
        addAbilityToBackpack(firefighter, "Rain invocation", "Rain will extinguish 10 fire points throughout the battle", 1);
        break;
    case 3:
        addAbilityToBackpack(firefighter, "Extinguishing reinforcement", "Strengthens each attack by 10 points", 2);
        break;
    }
}

// Adding items to the backpack
void addItems(int item, Firefighter& firefighter) {
    switch (item) {
    case 1:
        addItemToBackpack(firefighter, "Fire extinguisher", "Useful for all fires", 1);
        break;
    case 2:
        addItemToBackpack(firefighter, "Water bomb", "Special bomb for special fires", 2);
        break;
    case 3:
        addItemToBackpack(firefighter, "Bucket", "Puts out fire by 50%", 3);
        break;
    case 4:
        addItemToBackpack(firefighter, "Water blower", "Inflicts minor damage but the next attack is stronger", 4);
        break;
    case 5:
        addItemToBackpack(firefighter, "Snake hose", "Useful for all fires", 5);
        break;
    }
}

// Using a given item
double usingItem(Firefighter& firefighter, double fire, bool crit, bool lastStage, bool& blow) {
    std::string items;
    int num = 0;

    // Displaying items
    for (const auto& item : firefighter.backpack) {
        num += 1;
        items += std::to_string(num) + ". " + item.name + ": " + item.description + "\n";
    }

    items += "\nChoice: ";
    std::cout << items;  // Displaying text

    std::string userInput;
    int choice;
    // Choosing the item and assigning the damage caused by the item
    while (true) {
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choice && (choice >= 1 && choice <= num) && ss.eof()) {

            BackpackItem selectedItem = firefighter.backpack[choice - 1]; // Selecting the item
            displayTextSlowly(std::to_string(selectedItem.id), 5);
            firefighter.backpack.erase(firefighter.backpack.begin() + (choice - 1)); // Removing the item from the backpack
            double dmg = dmgByItem(selectedItem.id); // Setting the damage caused by the item

            // For water bomb
            if (lastStage && selectedItem.id == 2)
            {
                dmg *= 2;
            }

            // Critical hit
            if (crit)
            {
                dmg *= 1.5;
            }

            // Using the water bucket
            if (selectedItem.id == 3)
            {
                fire /= 2;
            }

            // Using the water blower
            if (selectedItem.id == 4)
            {
                blow = true;
                dmg = 10;
            }
            return fire - dmg; // Returns the remaining fire after reducing the damage
        }
        else {
            clearScreen(); // Clearing the screen
            std::cout << items;
        }

    }
}
// Using a specific ability
int usingAbility(Firefighter& firefighter) {
    std::string items;
    int num = 0;
    std::vector<Abilities> abilitiesCopy; // Creating a copy of the list with active abilities

    // Showing active abilities
    for (const auto& item : firefighter.abilities) {
        if (item.active == true) {
            abilitiesCopy.push_back(item);
            num += 1;
            items += std::to_string(num) + ". " + item.name + ": " + item.description + "\n";
        }
    }

    // When there are no active abilities, returns -1
    if (num == 0) {
        return -1;
    }

    items += "\nChoice: ";
    std::cout << items; // Displaying text

    while (true) {
        // Choosing from the list
        int choice;
        std::string userInput;
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choice && (choice >= 1 && choice <= num) && ss.eof()) {
            int out = choice - 1;
            return abilitiesCopy[out].id;
        }
        else {
            clearScreen(); // Clearing the screen
            std::cout << items;
        }
    }
}

// Combat engine
void fightEngine(double hpFire, int stage, Firefighter& firefighter) {
    // Checking if it's not the final stage
    bool lastStage = false;
    if (stage == 4) {
        lastStage = true;
    }

    // Basic statistics and variables
    double fire = hpFire;
    std::string yt = "Your turn\n\n";
    std::string at = "Opponent's turn";
    bool lose = false;
    bool blow = false;
    bool drakeActive = true;
    bool rainActive = false;
    int specialFinal = 1;

    // Combat engine loop
    while (true) {
        // Basic statistics and variables
        fire = round(fire * 100) / 100;
        bool critActive = false;
        int ability = -2;
        bool returnToMenu = false;
        std::string message = "";
        double dm;
        std::ostringstream oss;

        oss << std::fixed << std::setprecision(2) << fire; // Trimming fire points
        std::string menu = yt + "\nFire: " + oss.str() + " Pkn\n\n" + fightMenu(); // Description of user's turn, fire points, and menu
        displayTextSlowly(menu, 5); // Displaying text
        int choice = choice3Options(menu); // Method for choosing one of the 3 options

        // User's turn
        switch (choice) {
        case 1:
            // Using an item
            if (firefighter.backpack.empty()) {
                message = "EMPTY BACKPACK";
                returnToMenu = true;
                break;
            }
            else if (drakeActive && stage == 2) {
                dm = usingItem(firefighter, fire, critActive, lastStage, blow);  // Setting damage for the second fire battle
                fire -= ((fire - dm) / 2);
            }
            else {
                fire = usingItem(firefighter, fire, critActive, lastStage, blow); // Setting fire points
            }
            critActive = false;
            break;
        case 2:
            // Using an ability
            if (firefighter.abilities.empty()) {
                message = "NO ABILITIES";
                returnToMenu = true;
                break;
            }
            ability = usingAbility(firefighter); // Using a specific ability
            break;
        case 3:
            lose = true;
            break;
        }

        if (ability == -1) {
            continue;
        }

        // Using an ability
        if (ability >= 0) {
            firefighter.abilities[ability].active = false; // Setting the ability to inactive

            switch (ability) {
            case 0:
                drakeActive = false;
                break;
            case 1:
                rainActive = true;
                break;
            case 2:
                critActive = true;
                break;
            default:
                break;
            }
        }

        // Returning to the start of the turn
        if (returnToMenu) {
            displayTextSlowly(message, 5); // Displaying text
            waitForEnter();// Waiting for Enter press
            clearScreen();// Clearing the screen
            continue;
        }

        // Using ability if active
        if (rainActive) {
            fire -= 10;
        }

        // Checking parameters
        if (lose) {
            firefighter.score += hpFire - fire;
            break;
        }
        else if (fire <= 0) {
            firefighter.score += hpFire;
            break;
        }

        fire = round(fire * 100) / 100;

        // Opponent's turn
        clearScreen(); // Clearing the screen
        std::cout << at;
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Pausing the screen

        // Statistics for
        if (stage == 1) {
            // Fire regeneration
            if (fire + 5 >= 100) {
                fire = 100;
            }
            else {
                fire += 5;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));// Pausing the screen 
            if (fire + 15 >= 100 && drakeActive) {
                fire = 100;
                std::cout << "\n\nThe dragon regenerated fire!";
            }
            else if (fire + 15 <= 100 && drakeActive) {
                fire += 15;
                std::cout << "\n\nThe dragon regenerated fire!";
            }
        }
        else if (stage == 2) {
            if (fire + 8 >= 250) {
                fire = 250;

            }
            else {
                fire += 8;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));// Pausing the screen 
            if (drakeActive) {
                std::cout << "\n\nThe dragon reduced your damage!";
            }
        }
        else if (stage == 3) {
            if (fire + 8 >= 450) {
                fire = 450;
            }
            else {
                fire += 8;
            }
        }
        else if (stage == 4) {
            if (fire + 10 >= 700) {
                fire = 700;
            }
            else {
                fire += 10;
            }

            // Fire regeneration
            std::this_thread::sleep_for(std::chrono::milliseconds(50));// Pausing the screen 
            if (fire + 30 >= 700 && drakeActive) {
                fire == 700;
                std::cout << "\n\nThe emerald dragon regenerated fire!";
            }
            else if (fire + 30 <= 700 && drakeActive) {
                fire += 30;
                std::cout << "\n\nThe emerald dragon regenerated fire!";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));// Pausing the screen 
            srand(time(0));
            int randomNumber = rand() % 10;
            if ((randomNumber >= 0 || randomNumber <= 1) && specialFinal != 0) {
                specialFinal -= 1;
                fire = hpFire;
                std::cout << "\n\nThe sapphire dragon reignited the fire";
            }
        }

        std::cout << "\n\nThe fire has regenerated!";
        std::ostringstream osss;
        osss << std::fixed << std::setprecision(2) << fire;
        std::cout << "\n\nFire: " + osss.str() + "pkn";
        waitForEnter();// Waiting for Enter press
        clearScreen();// Clearing the screen
    }
    clearScreen();// Clearing the screen

    // Checking the result
    if (lose && stage != 4) {
        // Description of the battle result
        std::string info = "Unfortunately, you failed to defeat the fire.\n"
            "But don't worry, your adventure doesn't end with a lost battle.\n"
            "There are still a few duels ahead of you.";
        displayTextSlowly(info, 5);// Displaying text
    }
    else if (lose && stage == 4) {
        std::string info = "Unfortunately, you failed to defeat the fire.\n";
    }
    else {
        // Description of the battle result
        std::string info = "BRAVO!, you managed to defeat the fire.";
        displayTextSlowly(info, 5); // Displaying text
    }
    waitForEnter();// Waiting for Enter press
    clearScreen();// Clearing the screen
}
