#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include "HelpingMethods.h"

// Display the main menu
void displayMenu(int score, std::string place) {
    std::cout << "Score: " + std::to_string(score) + "\n\n\n";
    std::cout << "1. Travel to " + place + "\n";
    std::cout << "2. Map\n";
    std::cout << "3. Backpack\n";
    std::cout << "4. Skills\n";
    std::cout << "5. Save\n";
    std::cout << "6. Goal\n";
    std::cout << "7. Exit\n\n";
}

// Display the fight menu
std::string fightMenu() {
    return "1. Equipment\n2. Skill\n3. Surrender\nChoice: ";
}

// Convert a string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Wait for Enter key press
void waitForEnter() {
    std::cout << "\n\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Wait for Enter key press twice
void waitForEnterSec() {
    std::cout << "\n\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Display text slowly
void displayTextSlowly(const std::string& text, int delay_ms) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

// Choose between two options
int choice2Options(std::string text) {
    std::string userInput;
    int choice;

    // Choose 1 or 2
    while (true) {
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choice && (choice == 1 || choice == 2) && ss.eof()) {
            clearScreen();   // Clear screen
            break;
        }
        else {
            clearScreen(); // Clear screen
            std::cout << text;
        }
    }
    return choice;
}

// Choose between three options
int choice3Options(std::string text) {
    std::string userInput;
    int choice;

    // Choose 1, 2, or 3
    while (true) {
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choice && (choice == 1 || choice == 2 || choice == 3) && ss.eof()) {
            clearScreen(); // Clear screen
            break;
        }
        else {
            clearScreen(); // Clear screen
            std::cout << text;
        }
    }
    return choice;
}

// Description of the game objective
void target() {
    // Description of the game objective
    std::string gameGoal = "The goal of the game is to collect items and skills useful in fighting "
        "dragons and helping\nvarious people. The game consists of five different locations, each with its own\n"
        "lore and tasks to complete. During gameplay, the player can encounter various side missions and interact with NPCs,\n"
        "which can affect the storyline and character development. After completing all five locations, the player will face\n"
        "the final boss, the Lord of Embers, to restore peace in Pyroklas.";
    std::cout << gameGoal;
    waitForEnterSec();  // Wait for Enter key press
    clearScreen();   // Clear screen
}

// Description of the locations the user can visit
void showMap() {
    // Description of the map
    std::string map =
        "----------------------------------------\n"
        "1. Central Park\n"
        "----------------------------------------\n"
        "The green heart of the city, where residents escape from the hustle and bustle of daily life.\n"
        "Here you will find numerous walking paths, a playground, and picturesque ponds.\n"
        "----------------------------------------\n"
        "2. Museum of Technology\n"
        "----------------------------------------\n"
        "A fascinating place where you can see exhibits related to the history of technology,\n"
        "from ancient inventions to modern scientific achievements.\n"
        "----------------------------------------\n"
        "3. City Library\n"
        "----------------------------------------\n"
        "An oasis of knowledge and peace. In its collection, you will find both ancient prints and the latest bestsellers.\n"
        "An ideal place for study and reflection.\n"
        "----------------------------------------\n"
        "4. Old Town\n"
        "----------------------------------------\n"
        "The historic part of the city full of charming streets, historic townhouses, and cozy cafes.\n"
        "Here you can feel the spirit of the past.\n"
        "----------------------------------------\n"
        "5. Citadel\n"
        "----------------------------------------\n"
        "A powerful fortress that has guarded the city from external dangers for centuries. "
        "Its walls hide stories of heroic defenses and bravery.\n"
        "----------------------------------------\n"
        "6. Final (Cathedral)\n"
        "----------------------------------------\n"
        "A monumental cathedral, the symbol of the city. Its interiors hide magnificent stained glass windows and beautiful sculptures,\n"
        "and the atmosphere of this place is filled with peace and majesty.\n"
        "----------------------------------------\n";
    std::cout << map;
    waitForEnterSec(); // Wait for Enter key press
}
