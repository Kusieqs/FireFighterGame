#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

// Display the main menu
void displayMenu(int score, std::string place);

// Display the fight menu
std::string fightMenu();

// Convert a string to lowercase
std::string toLowerCase(const std::string& str);

// Clear the console screen
void clearScreen();

// Wait for the user to press Enter
void waitForEnter();

// Wait for the user to press Enter twice
void waitForEnterSec();

// Display text slowly
void displayTextSlowly(const std::string& text, int delay_ms);

// Choose between two options
int choice2Options(std::string text);

// Choose between three options
int choice3Options(std::string text);

// Description of the game objective
void target();

// Description of the locations the user can visit
void showMap();

