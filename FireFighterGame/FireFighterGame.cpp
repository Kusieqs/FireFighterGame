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
#include "HelpingMethods.h"
#include "Hero.h"


// Game Introduction
void intro()
{
    // Description
    std::string intro = "Welcome to Pyroklas, a city where everyday life mingles with horror. Dragons are a reality here,\n"
        "bringing fire and destruction. As a new member of the Fire Wing Brigade, you step up to fight\n"
        "the flames and protect the inhabitants.";

    displayTextSlowly(intro, 5);   // Display text slowly
    waitForEnter();  // Wait for Enter key press
    clearScreen();   // Clear the screen

    // Description
    intro = "Recently, dragon attacks have become more organized and frequent, as if directed by the mysterious Lord of Embers,\n"
        "a legendary dragon hidden in the volcanic mountains. Your task is not only to fight the fire but also to uncover\n"
        "the truth behind this threat.";

    displayTextSlowly(intro, 5);   // Display text slowly
    waitForEnter();  // Wait for Enter key press
    clearScreen();   // Clear the screen
}
// User's First Quest
int firstQuest(Firefighter& firefighter)
{
    // Description
    std::string quest = "After a strenuous day of fighting fires in the city of Pyroklas, a firefighter from the Fire Wing Brigade\n"
        "finally gets a moment of respite. When looking up at the sky among the smoldering ruins,\n"
        "they notice three plumes of smoke rising in the distance. In the heart of this desperate situation,\n"
        "they must make one of three decisions, each leading to a different danger and challenge.\n"
        "\n1. Abandoned Warehouse\n2. Chemical Depot\n3. Shoe Store\nChoice: ";

    displayTextSlowly(quest, 5);   // Display text slowly

    std::string item;
    std::string place;
    int choice = choice3Options(quest); // Choosing between 3 options

    // Assign which option the user has chosen
    if (choice == 1) {
        place = "abandoned warehouse";
        item = "+2 Extinguisher";
    }
    else if (choice == 2) {
        place = "chemical depot";
        item = "+1 Water Bomb\n+2 Extinguisher";
    }
    else if (choice == 3) {
        place = "shoe store";
        item = "+3 Extinguisher";
    }

    // Task description
    quest = "You head towards the " + place + ". When you arrive, you see that the " + place + " \n"
        "is engulfed in darkness and devastation. Your firefighting instincts suggest that there might be \n"
        "someone or something that needs your help. During the search, you discover a hidden door leading to the basement.\n"
        "Entering the basement, you hear a muffled voice calling for help. As you reach the end of the corridor,\n"
        "you see a trapped person behind a door. You need a special code to open the door.\n"
        "On the wall, you see an inscription: ";
    displayTextSlowly(quest, 5);   // Display text slowly
    waitForEnter();  // Wait for Enter key press
    clearScreen();   // Clear the screen

    // Task description
    quest = "I have four digits. My first digit is even and the second is the same as the first.\n"
        "The third digit is 3 less than the second digit and the fourth digit is 7 more than the third digit.\n"
        "What number am I?\n\nCode: ";
    displayTextSlowly(quest, 5);

    // Guessing the number as a code
    int code = 4429; // Code
    std::string userInput;
    int choiceCode;
    while (true) {
        std::getline(std::cin, userInput);
        std::stringstream ss(userInput);
        if (ss >> choiceCode && (code == choiceCode) && ss.eof()) {
            clearScreen(); // Clear the screen
            break;
        }
        else {
            clearScreen(); // Clear the screen
            std::cout << quest;
        }
    }

    // Description of the result
    quest = "CONGRATULATIONS! You guessed the code and freed the trapped person.";
    displayTextSlowly(quest, 5);   // Display text slowly
    waitForEnter();  // Wait for Enter key press
    clearScreen();   // Clear the screen

    // Description of the dialogue
    std::string specItem = "\n\n" + item; // Description of adding a new item to the inventory
    std::string dial = "Person: Thank you for saving me! But what I discovered during my captivity is terrifying.\nI know who is behind these dragon attacks.\n\n"
        "Hero: Who is it? We must stop them before they cause more destruction!\n\n"
        "Person: The one they call 'Lord of Embers'. It is a legendary dragon directing the dragon attacks on the city.\n"
        "To stop him, you must extinguish the 5 nearest fires and complete certain side missions\nthat will help you reach him.\n\n"
        "Hero: I will do everything in my power to restore peace to Pyroklas. Thank you for this information.\n\n"
        "Person: As a reward for saving me, I give you special items. They will surely be useful in the future!\n" + specItem;
    displayTextSlowly(dial, 5); // Display text slowly
    waitForEnter();  // Wait for Enter key press
    clearScreen();   // Clear the screen
    firefighter.score += 10;
    return choice;
}

// Level - Central Park and Random Events
void centralParkEventItems(int randomEvent, Firefighter& firefighter)
{
    if (randomEvent == 2)
    {
        // Event description
        std::string event = "While on your way to Central Park, you suddenly hear strange voices coming from behind the trees. "
            "\nTo get there, you'll need to use one of the extinguishers you have with you. "
            "Do you want to do that?\nThis might be a crucial moment, so the decision is up to you."
            "\n\n1. Yes\n2. No\nChoice: ";
        displayTextSlowly(event, 5); // Display text slowly

        int choice = choice2Options(event); // Choose whether to proceed or help

        // Exit random event if choice is 2
        if (choice == 2)
        {
            return;
        }

        // Iterate through the list to find and remove an extinguisher
        for (auto it = firefighter.backpack.begin(); it != firefighter.backpack.end(); ++it) {
            if (it->name == "Extinguisher") {
                firefighter.backpack.erase(it);
                break; // Break the loop after finding and removing the item
            }
        }

        clearScreen(); // Clear the screen

        // Dialogue description
        std::string dia = "Stranger: Thank you for extinguishing our path, we couldn't get out of here.\n\n"
            "Hero: Can I know what brought you here?\n\n"
            "Stranger: No, but in return for your help, we offer you an extinguisher and a water bomb that might\nprove useful in your journey.\n\n"
            "Hero: Thank you for the offer. I accept it gratefully.\n\n\n-1 Extinguisher\n+1 Extinguisher\n+1 Water Bomb";

        displayTextSlowly(dia, 5); // Display text slowly
        addItems(1, firefighter); // Add extinguisher to the list
        addItems(2, firefighter); // Add water bomb to the list
        waitForEnter(); // Wait for Enter key press
        firefighter.score += 20;

    }
    else
    {
        // Event description
        std::string event = "While on your way to Central Park, you suddenly notice a figure standing behind a tree, staring at you from a distance.\n"
            "Do you want to approach and talk to this stranger?"
            "\n\n1. Yes\n2. No\nChoice: ";
        displayTextSlowly(event, 5); // Display text slowly

        int choice = choice2Options(event); // Choose whether to proceed or talk to the character

        if (choice == 2)
        {
            return;
        }

        // Options description
        event = "1. Hello, do you need help?\n2. Hello, who are you?\n3. Stop staring at me!\nChoice: ";
        displayTextSlowly(event, 5); // Display text slowly

        choice = choice3Options(event); // Choose between the 3 options listed above
        clearScreen(); // Clear the screen

        if (choice == 1) {

            // Dialogue description
            std::string dial = "Hero: Hello, do you need help?\n\n"
                "Stranger: No, I don't need help. Sorry for the trouble.";
            displayTextSlowly(dial, 5); // Display text slowly
        }
        else if (choice == 2) {

            // Dialogue description
            std::string dial = "Hero: Hello, who are you?\n\n"
                "Stranger: I'm a traveler looking for lost treasures. And who are you?\n\n"
                "Hero: I'm an ember firefighter, trying to get to Central Park. Do you have any information on what happened there?\n\n"
                "Stranger: Yes, a dragon recently flew there and trapped several people in a tree.\n\n"
                "Hero: Thank you very much for the information. Could you help me get to Central Park?\n\n"
                "Stranger: Unfortunately, I have other matters to attend to. But I wish you good luck.";
            displayTextSlowly(dial, 5); // Display text slowly
        }
        else if (choice == 3) {
            // Dialogue description
            std::string dial = "Hero: Stop staring at me!\n\n"
                "Stranger: Sorry if I offended you. I didn't mean to bother you. Allow me to leave.";
            displayTextSlowly(dial, 5); // Display text slowly
        }
        waitForEnter(); // Wait for Enter key press
        firefighter.score += 10;
    }

    clearScreen(); // Clear the screen
}
void centralPark(Firefighter& firefighter)
{
    // Number of random events to occur
    int itRand = 2;

    // Initial story description
    std::string hist = "After saving the last person you barely managed to rescue, you notice something unusual in the scorched area.\n"
        "Among the remnants of the burnt place, you see tracks - tracks that don't seem to be caused by fire. "
        "These are unusual tracks, as if left by something large and heavy, something unlike any known animal or creature.\n"
        "These mysterious tracks lead straight to the central area of the park.\n"
        "Without hesitation and resolutely, you set off.";
    displayTextSlowly(hist, 5);   // Display text slowly
    waitForEnterSec();  // Wait for Enter key press
    clearScreen();  // Clear the screen

    // Graphically show the path
    std::string text = "##################################";
    std::string road = "Road - ";
    srand(time(0));

    // Graphically show the path progress and random events
    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
        int randomNumber = rand() % 51; // Generate a random number between 0 and 50

        if ((itRand == 1 || itRand == 2) && randomNumber >= 0 && randomNumber <= 4)
        {
            clearScreen(); // Clear the screen
            centralParkEventItems(itRand, firefighter); // Call random event method
            itRand -= 1;
        }
        clearScreen(); // Clear the screen
    }

    // Continue story description
    hist = "Upon reaching the place, you notice in the distance a majestic dragon named Aethraxis,\n"
        "rising above the ancient ruins. Its powerful wings spread wide,\n"
        "and its claws gleam in the sunlight, resembling shiny steel. Its skin is covered with scales\n"
        "of a golden-brown hue that glisten in the sun's rays.";
    displayTextSlowly(hist, 5);   // Display text slowly
    waitForEnter();  // Wait for Enter key press
    clearScreen();  // Clear the screen

    // Continue story description
    hist = "After a moment, the majestic dragon soaring above the ruined ruins suddenly flew towards the Museum of Technology.\n"
        "At the same time, without a moment's hesitation, you ran towards the tree where two people were trapped.\n"
        "Your task will be to guess the correct angle at which you will climb the tree.";
    displayTextSlowly(hist, 5);   // Display text slowly
    waitForEnter();  // Wait for Enter key press
    clearScreen();  // Clear the screen

    // Math riddle description
    hist = "Find the angle which is equal to one-third of a right angle,\nmultiplied by 2, "
        "and then subtracted from the sum of 120 degrees.\n\nAngle: ";
    displayTextSlowly(hist, 5);   // Display text slowly

    // Guessing the angle as the solution
    int angle = 60; // The correct angle
    std::string userInput1;
    int choiceCode;
    while (true) {
        std::getline(std::cin, userInput1);
        std::stringstream ss(userInput1);
        if (ss >> choiceCode && (angle == choiceCode) && ss.eof()) {
            clearScreen(); // Clear the screen
            break;
        }
        else {
            clearScreen(); // Clear the screen
            std::cout << hist;
        }
    }

    // Correct angle guessed
    hist = "CONGRATULATIONS! You guessed the correct angle. You saved two people from death.\n\n"
        "While climbing the tree, you came across an undetonated water bomb.\n"
        "You decided to place it in your backpack.\n";
    displayTextSlowly(hist, 5); // Display text slowly
    waitForEnter();  // Wait for Enter key press
    clearScreen();  // Clear the screen
    addItems(2, firefighter); // Add water bomb to the backpack
    firefighter.score += 60;

    // Dialogue with the rescued person
    std::string dial = "Person: Thank you for saving us! We are very grateful.\n\n";
    std::string que = "1. What happened? \n2. Can I help you in any way?\nChoice: ";
    displayTextSlowly(dial + que, 5);
    int choice = choice2Options(dial + que); // Choose between the first or second option
    std::cout << dial;

    if (choice == 1)
    {
        // Dialogue description
        dial = "Hero: What happened? \n\n"
            "Person: Our group was being chased by that dragon. We are extremely grateful for your help. "
            "In return for your rescue, we would like to give you a special ability to fight dragons. "
            "We grant you the \"Dragon Frighten\" ability. It is only active when a dragon interferes with you extinguishing a fire.\n\n"
            "Hero: Thank you for the ability. It is an honor to possess such an ability. I am very happy that everyone is safe.";
        displayTextSlowly(dial, 5); // Display text slowly
    }
    else
    {
        // Dialogue description
        dial = "Hero: Can I help you in any way?\n\n"
            "Person: No, thank you. We are extremely grateful for your help. "
            "In return for your rescue, we would like to give you a special ability to fight dragons. "
            "We grant you the \"Dragon Frighten\" ability. It is only active when a dragon interferes with you extinguishing a fire.\n\n"
            "Hero: Thank you for the ability. It is an honor to possess such an ability.";
        displayTextSlowly(dial, 5);    // Display text slowly
    }

    std::string abi = "\n\n\n+1 Dragon Frighten";
    addAbilities(1, firefighter); // Add ability to the list
    displayTextSlowly(abi, 5); // Display the addition of the ability
    waitForEnter();  // Wait for Enter key press
    clearScreen();  // Clear the screen
}

// Level - Museum and random events
void museumOfTechnicEventItems(int randomEvent, Firefighter& firefighter)
{
    // Description of the random task
    std::string quest = "During the journey towards the museum, you notice the ruins of an old hospital.\n"
        "You stop for a moment to take a closer look at what remains of the building. \nDo you want to search this building?\n\n"
        "1. Yes\n2. No\nChoice: ";

    displayTextSlowly(quest, 5); // Displaying text
    int choice = choice2Options(quest); // Choosing between two options

    // Exit
    if (choice == 2)
    {
        return;
    }

    // Graphic representation of searching
    std::string seak = "##############################";
    std::cout << "Searching - ";
    displayTextSlowly(seak, 5); // Displaying text
    clearScreen(); // Clearing the screen

    srand(time(0));
    int randomNumber = rand() % 51; // Random number from 0 to 50
    if (randomNumber <= 50 && randomNumber >= 25)
    {
        std::string info = "Unfortunately, you found nothing.";
        displayTextSlowly(info, 5); // Displaying text
    }
    else
    {
        std::string info = "You found two fire extinguishers!\n\n\n+2 Fire Extinguisher";
        displayTextSlowly(info, 5); // Displaying text
        addItems(1, firefighter); // Adding fire extinguisher to the list
        addItems(1, firefighter); // Adding fire extinguisher to the list
        firefighter.score += 10;
    }
    waitForEnter(); // Waiting for Enter press
    clearScreen(); // Clearing the screen
}
void museumOfTechnic(Firefighter& firefighter)
{
    // Saving 1 random event
    int itRand = 1;

    // Story description
    std::string hist = "After rescuing people from the tree and acquiring a special ability, you feel like your mission\n"
        "is far from over. You know you must follow the dragon, whom you managed to scare away only for a moment.\n"
        "You're now heading towards the Museum of Technology, a place that was once a symbol of progress and human achievement,\n"
        "now lying in ruins, shrouded in flames and smoke. You believe that's where you'll find the dragon and confront it.";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnterSec(); // Waiting for Enter press
    clearScreen(); // Clearing the screen

    // Story description
    hist = "With every step, you feel the adrenaline pumping through your veins, and every sound\n"
        "makes you more alert. As you approach the museum, you see its silhouette on the horizon - destroyed buildings,\n"
        "shattered exhibits, and the pervasive smell of smoke. You know it's going to be a tough fight,\n"
        "but you're determined to drive away Aethraxis and restore peace to the city.";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnter(); // Waiting for Enter press
    clearScreen(); // Clearing the screen

    // Graphic representation of the road
    std::string text = "#####################";
    std::string road = "Road - ";
    srand(time(0));

    // Displaying the graphical representation of the road and random events
    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pausing iteration for 50 milliseconds
        int randomNumber = rand() % 51; // Random number from 0 to 50
        if ((itRand == 1) && randomNumber >= 0 && randomNumber <= 6)
        {
            clearScreen(); // Clearing the screen
            museumOfTechnicEventItems(itRand, firefighter); // Method for random events
            itRand -= 1;
        }
        clearScreen(); // Clearing the screen
    }

    // Story description
    hist = "Upon arrival, you see that the museum is in a deplorable state. Thick smoke hangs in the air,\n"
        "making it difficult to breathe. Suddenly, among the ruins, you spot the powerful silhouette of Aethraxis.\n"
        "The dragon breathes fire, destroying the remnants of the museum. You must act quickly and effectively\n"
        "to extinguish the fire and confront the dragon at the same time.";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnter(); // Waiting for Enter press
    clearScreen(); // Clearing the screen

    // Task description
    hist = "Your task will be to extinguish the fire as quickly as possible by using items from your inventory.\n"
        "If you fail to extinguish it, it will affect the final result of the game.";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnter(); // Waiting for Enter press
    clearScreen(); // Clearing the screen

    fightEngine(100, 1, firefighter);

    hist = "After an exhausting battle, when Aethraxis, though undefeated, was driven out of the city, you saw something unusual.\n"
        "On the hill overlooking the city library, dragons circled, their presence heralding something ominous.\n"
        "Warning growls and flashes of fire in the sky made the atmosphere tense and uncertain.\n"
        "Realizing that the situation in the city was still critical, you decided to investigate what was happening in the library,\n"
        "hoping to find answers to this mysterious phenomenon.";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnter(); // Waiting for Enter press
    clearScreen(); // Clearing the screen
}

// Level - Library and random events
void libraryEventItems(int randomEvent, Firefighter& firefighter)
{
    if (randomEvent == 1)
    {
        // Event description
        std::string event = "While traveling towards the library, you notice the ruins of a school.\n"
            "You stop for a moment to take a closer look at what remains of the building.\nWould you like to search this building?\n\n"
            "1. Yes\n2. No\nChoice: ";
        displayTextSlowly(event, 5); // Displaying text

        int choice = choice2Options(event); // Choosing one of two options

        // Visualization of searching
        std::string seak = "##############################";
        std::cout << "Searching - ";
        displayTextSlowly(seak, 5); // Displaying text
        clearScreen(); // Clearing the screen

        srand(time(0));
        int randomNumber = rand() % 51;
        if (randomNumber <= 50 && randomNumber >= 25)
        {
            std::string info = "Unfortunately, you found nothing.";
            displayTextSlowly(info, 5); // Displaying text
        }
        else
        {
            std::string info = "You found a bucket and a fire extinguisher!\n\n\n+1 Fire Extinguisher\n+1 Bucket";
            displayTextSlowly(info, 5); // Displaying text
            addItems(1, firefighter); // Adding fire extinguisher to the backpack
            addItems(3, firefighter); // Adding bucket to the backpack
            firefighter.score += 20;
        }
        waitForEnter(); // Waiting for Enter press
        clearScreen(); // Clearing the screen
    }
    else if (randomEvent == 2)
    {
        // Event description
        std::string event = "While traveling towards the library, you notice a strange place.\n"
            "You stop for a moment to take a closer look at what remains of the building.\nWould you like to search this building?\n\n"
            "1. Yes\n2. No\nChoice: ";
        displayTextSlowly(event, 5); // Displaying text

        int choice = choice2Options(event); // Choosing one of two options

        // Exiting the event
        if (choice == 2)
        {
            return;
        }

        // Event description
        std::string fail = "Unfortunately, you got caught in a fiery cage. You had to use the first item from the list!";

        // Removing item from the backpack
        if (!firefighter.backpack.empty()) {
            firefighter.backpack.erase(firefighter.backpack.begin());
        }

        displayTextSlowly(fail, 5); // Displaying text
        waitForEnter(); // Waiting for Enter press
        clearScreen(); // Clearing the screen
    }
    else if (randomEvent == 3)
    {
        // Event description
        std::string event = "While on the way to the Library, you suddenly notice a firefighter.\n"
            "Do you want to approach and talk to the firefighter?\n\n"
            "1. Yes\n2. No\nChoice: ";
        displayTextSlowly(event, 5); // Displaying text

        int choice = choice2Options(event); // Choosing one of two options

        // Exiting the event
        if (choice == 2)
        {
            return;
        }

        // Choosing an option
        std::string quest = "1. Hello, do you know what's happening at the library?\n2. Hello, can you help me?\nChoice: ";
        displayTextSlowly(quest, 5); // Displaying text

        choice = choice2Options(quest); // Choosing one of two options

        clearScreen(); // Clearing the screen
        if (choice == 1) {
            std::string dial = "Hero: Hello, do you know what's happening in the library area?\n\n"
                "Firefighter: Sorry, I don't have time for chit-chat.";
            displayTextSlowly(dial, 5); // Displaying text
        }
        else if (choice == 2) {
            std::string dial = "Hero: Hello, can you help me?\n\n"
                "Firefighter: Go ahead.\n\n"
                "Hero: I need equipment to fight fires and dragons, do you have anything that could help me?\n\n"
                "Firefighter: I can lend you a bucket of water.\n\n"
                "Hero: Thank you very much for the offer. Could you help me get to the library?\n\n"
                "Firefighter: Unfortunately, I have other matters to attend to. But I wish you good luck.\n\n+1 Bucket";
            displayTextSlowly(dial, 5); // Displaying text
            addItems(3, firefighter); // Adding bucket to the backpack
            firefighter.score += 10;
        }
        waitForEnter(); // Waiting for Enter press
    }
}
void library(Firefighter& firefighter)
{
    // Saving 3 random events
    int itRand = 3;

    // Story description
    std::string hist = "You immediately headed to the library to investigate the situation. The atmosphere in the library was one of focus,\n"
        "and people were feverishly searching for information. Among them, you too, hoping to find clues about\n"
        "the presence of dragons and how to stop them.";
    displayTextSlowly(hist, 5);   // Displaying text
    waitForEnterSec();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    // Graphic display of the road
    std::string text = "#########################################";
    std::string road = "Road - ";
    srand(time(0));

    // Displaying the graphical path and random events
    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pausing iteration for 50 milliseconds
        int randomNumber = rand() % 51; // Random number generation from 0 to 50
        if ((itRand == 1 || itRand == 2 || itRand == 3) && randomNumber >= 0 && randomNumber <= 5)
        {
            clearScreen(); // Clearing the screen
            libraryEventItems(itRand, firefighter);// Method for random events
            itRand -= 1;
        }
        clearScreen(); // Clearing the screen
    }

    // Story description
    hist = "Upon reaching the library, you notice that people are trapped in a strange cage-like structure.\n"
        "Shouts and cries for help fill the air, and panic begins to spread. You must find a way\n"
        "to free the trapped before it's too late. While scanning the area, your attention is caught by a magical note with a lock cipher.\n"
        "Your task will be to decipher the lock code.";
    displayTextSlowly(hist, 5);   // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    // Puzzle description
    hist = "uasfhajskfhajksh2akslfkaaslf\n"
        "sadkj1fjasfhajksfhjaksfhasfa\n"
        "kiwoeqiweqruy8jqrhjhjsdhasds\n"
        "asdhajskh1ajshdjakdhajksdask\n\n"
        "This cipher contains the code to the lock. Find and enter it to release the people.\n\nLock Code: ";
    displayTextSlowly(hist, 5);// Displaying text

    int code = 2181; // Code to guess
    std::string userInput1;
    int choiceCode;
    while (true) {
        std::getline(std::cin, userInput1);
        std::stringstream ss(userInput1);
        if (ss >> choiceCode && (code == choiceCode) && ss.eof()) {
            clearScreen(); // Clearing the screen
            break;
        }
        else {
            clearScreen(); // Clearing the screen
            std::cout << hist;
        }
    }

    // Story description
    hist = "BRAVO! You guessed the correct code. You have saved many lives from death.\n"
        "\nIn gratitude, the library residents have given you a new skill - summoning rain and two water bombs\n\n\n+1 Summoning Rain\n+2 Water Bombs";

    displayTextSlowly(hist, 5);   // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen
    addAbilities(2, firefighter); // Adding abilities to the list
    addItems(2, firefighter); // Adding water bomb
    addItems(2, firefighter); // Adding water bomb

    // Story description
    hist = "As you left the library, you heard terrifying roars coming from the Old Town.\n"
        "You knew that meant only one thing - another dragon had appeared in the area, spreading destruction.";
    displayTextSlowly(hist, 5);   // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen
    firefighter.score += 50;
}

// Level - Old town and random events
void oldTownEventItems(Firefighter& firefighter)
{
    std::string event = "On your way to the old town, you found a special water pump\n"
        "that will be useful in fighting fires\n\n+1 Water Pump";
    displayTextSlowly(event, 5); // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen
    addItems(4, firefighter); // Adding the water pump to the backpack
}
void oldTown(Firefighter& firefighter)
{
    // Saving 1 random event
    int itRand = 1;

    // Story description
    std::string hist = "You immediately headed to the Old Town to assess the situation.";

    displayTextSlowly(hist, 5);   // Displaying text
    waitForEnterSec();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    // Displaying the road graphically and randomly selecting events
    std::string text = "#############################################";
    std::string road = "Road - ";
    srand(time(0));

    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pausing iteration for 50 milliseconds
        int randomNumber = rand() % 51; // Random number from 0 to 50
        if ((itRand == 1) && randomNumber >= 0 && randomNumber <= 5)
        {
            clearScreen(); // Clearing the screen
            oldTownEventItems(firefighter); // Random event selection
            itRand -= 1;
        }
        clearScreen(); // Clearing the screen
    }

    // Story description
    hist = "When you arrived, you were met with an atmosphere of panic. People were frantically trying to escape the fire and destruction\n"
        "caused by another dragon. In the sky, a giant silver-blue dragon named Syltherion hovered.\n"
        "Its presence emanated cold, and each beat of its wings extinguished the flames on the streets,\n"
        "only for them to reappear with renewed strength. Syltherion had the ability to weaken your attacks\n"
        "with each subsequent clash. You must find a way to defeat this powerful opponent and save the Old Town.";

    displayTextSlowly(hist, 5);   // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    // Task description
    hist = "Your task will be to extinguish the fire as quickly as possible by using items from your backpack.\n"
        "If you fail to extinguish it, it will affect the final result of the game.";

    displayTextSlowly(hist, 5);   // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    fightEngine(250, 2, firefighter);

    // Story description
    hist = "After a fierce battle with Syltherion, the Old Town was destroyed, but at least its inhabitants\n"
        "were safe. Among the survivors, you noticed a group of people who looked at you with gratitude and relief.\n"
        "You now have the opportunity to talk to one of these people. Perhaps you will learn more about the situation\n"
        "or gain valuable insights for the journey ahead.\n\n"
        "Do you want to talk to a random person?\n\n1. Yes\n2. No\nChoice: ";

    displayTextSlowly(hist, 5); // Displaying text

    int choice = choice2Options(hist); // Choosing one of the two options

    if (choice == 1)
    {
        std::string dial = "Hero: Can I help you with something?\n\n"
            "Elderly Man: You've already helped us by saving our city from that terrible dragon.\n"
            "In gratitude, we want to give you some items.\n\n"
            "Hero: Thank you, it will surely be very useful.\n\n\n+1 Fire Extinguisher\n+2 Water Bombs\n+1 Bucket";
        displayTextSlowly(dial, 5); // Displaying text
        waitForEnter(); // Waiting for Enter press
        clearScreen(); // Clearing the screen
        addItems(1, firefighter); // Adding a fire extinguisher to the inventory
        addItems(2, firefighter); // Adding water bombs to the inventory
        addItems(2, firefighter); // Adding water bombs to the inventory
        addItems(3, firefighter); // Adding a bucket to the inventory
        firefighter.score += 10;
    }

    // Story description
    hist = "The next place indicated by the clues is the ancient Citadel, located on the hill.\n"
        "It's a former fortress that once served as the main defense line of the city. Now, its walls are covered in moss,\n"
        "and the once majestic towers now look abandoned and neglected.";

    displayTextSlowly(hist, 5); // Displaying text
    waitForEnter(); // Waiting for Enter press
    clearScreen(); // Clearing the screen

    // Story description
    hist = "While gathering for the expedition to the Citadel, you found an important fire hose and a water pump\n"
        "which will be useful in fighting fires!\n\n+1 Fire Hose\n+1 Bucket";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnter(); // Waiting for Enter press
    clearScreen(); // Clearing the screen
    addItems(5, firefighter); // Adding a fire hose to the inventory
    addItems(4, firefighter); // Adding a water pump to the inventory
}

// Level - Citadel and random events
void citadelEventItems(int randomEvent, Firefighter& firefighter)
{
    if (randomEvent == 4)
    {
        // Event description
        std::string event = "On your way to the citadel, you suddenly notice a firefighter.\n"
            "Do you want to approach and talk to this stranger?"
            "\n\n1. Yes\n2. No\nChoice: ";
        displayTextSlowly(event, 5); // Displaying text

        int choice = choice2Options(event); // Choosing one of the two options

        // Exit from the event
        if (choice == 2)
        {
            return;
        }

        clearScreen(); // Clearing the screen
        std::string dial = "Hero: Hi, are you coming back from the citadel?\n\n"
            "Firefighter: Can't you see? The Citadel is in a lamentable state, and on top of that, there's a dragon roaming there!\n\n"
            "Hero: Do you have any tips on how to get there and pass safely?\n\n"
            "Firefighter: Take this map; it will help you find a safe path. Take care of yourself! And remember, water bombs work best on fire in the citadel.\n\n";
        displayTextSlowly(dial, 5); // Displaying dialogue
        waitForEnter(); // Waiting for Enter press
        clearScreen(); // Clearing the screen
        firefighter.score += 10;
    }
    else if (randomEvent == 3)
    {
        // Event description
        std::string event = "During the journey towards the citadel, you notice an abandoned fire station. "
            "You stop for a moment to take a closer look at what remains of the building. Do you want to search this building?"
            "\n\n1. Yes\n2. No\nChoice: ";

        displayTextSlowly(event, 5);// Displaying text

        int choice = choice2Options(event); // Choosing one of the two options

        // Visualizing search
        std::string search = "##############################";
        std::cout << "Searching - ";
        displayTextSlowly(search, 5);// Displaying text
        clearScreen(); // Clearing the screen

        srand(time(0));
        int randomNumber = rand() % 51; // Random number from 0 to 50
        if (randomNumber <= 50 && randomNumber >= 25)
        {
            // Event description
            event = "You found a bucket, 3 fire extinguishers, and two water bombs.\n\n\n+1 Bucket\n+2 Water Bomb\n+3 Fire Extinguisher";
            displayTextSlowly(event, 5);// Displaying text
            addItems(3, firefighter); // Adding fire extinguishers
            addItems(2, firefighter); // Adding water bombs
            addItems(2, firefighter); // Adding water bombs
            addItems(1, firefighter); // Adding fire extinguishers
            addItems(1, firefighter); // Adding fire extinguishers
            addItems(1, firefighter); // Adding fire extinguishers
        }
        else
        {
            // Event description
            event = "You found two fire extinguishers and three fire hoses!\n\n\n+2 Fire Extinguisher\n+3 Fire Hose";
            displayTextSlowly(event, 5);// Displaying text
            addItems(1, firefighter); // Adding fire extinguishers
            addItems(1, firefighter); // Adding fire extinguishers
            addItems(5, firefighter); // Adding fire hoses
            addItems(5, firefighter); // Adding fire hoses
            addItems(5, firefighter); // Adding fire hoses
        }
        waitForEnterSec(); // Waiting for Enter press
        clearScreen(); // Clearing the screen
        firefighter.score += 10;
    }
    else if (randomEvent == 2)
    {
        // Event description
        std::string event = "During the journey to the citadel, random people ask you to extinguish their house\n"
            "You will need to use one fire hose you have with you to extinguish a huge fire. Do you want to do this? This could be a crucial moment, so the decision is yours."
            "\n\n1. Yes\n2. No\nChoice: ";

        displayTextSlowly(event, 5); // Displaying text

        int choice = choice2Options(event); // Choosing one of the two options

        // Exiting
        if (choice == 2)
        {
            return;
        }

        clearScreen(); // Clearing the screen

        // Dialogue description
        std::string dia = "Stranger: Thank you for extinguishing our house.\n\n"
            "Hero: No problem.\n\n"
            "Stranger: Here, as a thank you for your help, we offer you a fire extinguisher, which may be useful on your journey.\n\n"
            "Hero: Thank you for the offer. I accept it with gratitude.\n\n\n-1 Fire Hose\n+1 Fire Extinguisher\n+1 Water Bomb";

        // Removing the fire hose
        for (auto it = firefighter.backpack.begin(); it != firefighter.backpack.end(); ++it) {
            if (it->name == "Fire Hose") {
                firefighter.backpack.erase(it);
                break; // Breaking the loop after finding and removing the item
            }
        }
        addItems(1, firefighter); // Adding a fire extinguisher to the inventory
        addItems(2, firefighter);// Adding a water bomb to the inventory
        displayTextSlowly(dia, 5); // Displaying text
        waitForEnter(); // Waiting for Enter press
        clearScreen(); // Clearing the screen
        firefighter.score += 30;
    }
    else if (randomEvent == 1)
    {
        // Event description
        std::string event = "During the journey to the citadel, you suddenly notice a figure standing in the middle of the road. "
            "Do you want to approach and talk to this stranger?"
            "\n\n1. Yes\n2. No\nChoice: ";
        displayTextSlowly(event, 5); // Displaying text

        int choice = choice2Options(event); // Choosing one of the two options

        if (choice == 2)
        {
            return;
        }

        // Option selection description
        event = "Choose one of the options\n\n1. Hello, who are you?\n2. Leave!\nChoice: ";
        displayTextSlowly(event, 5); // Displaying text

        choice = choice2Options(event); // Choosing one of the two options

        clearScreen(); // Clearing the screen

        if (choice == 1) {

            // Dialogue description
            std::string dial = "Hero: Hello, who are you?\n\n"
                "Witch: I am the guardian of this land. Your presence here is not coincidental.\n\n"
                "Hero: Can you help me? I'm looking for clues on how to defeat dragons and extinguish fires.\n\n"
                "Witch: I can help you. But you must answer the riddle I have prepared for you, you have 3 attempts.\n\n";
            displayTextSlowly(dial, 5);// Displaying text
            waitForEnter(); // Waiting for Enter press
            clearScreen(); // Clearing the screen

            // Riddle description
            dial = "It flows, but is not a river.\n"
                "It stands, but is not a person.\n"
                "Sometimes you count with it.\n"
                "It is always with you.\n\nAnswer: ";
            displayTextSlowly(dial, 5);// Displaying text
            waitForEnter(); // Waiting for Enter press
            clearScreen(); // Clearing the screen

            // Checking if the user correctly guessed the answer
            bool accept = false;
            int attempt = 3;
            while (true)
            {
                clearScreen();// Clearing the screen
                std::string ans;
                std::cin >> ans;
                if (toLowerCase(ans) == "time") {
                    accept = true;
                    break;
                }
                else if (attempt == 0)
                {
                    break;
                }
                attempt -= 1;
                std::cout << dial;
            }
            clearScreen(); // Clearing the screen

            // Checking if the user guessed the riddle
            if (accept)
            {
                // Guessing description
                dial = "Well done! The answer is correct, you get a new ability!\n\n+1 Fire Extinguishing Enhancement.";
                addAbilities(3, firefighter); // Adding abilities to the list
                firefighter.score += 30;
            }
            else
            {
                // Guessing description
                dial = "Unfortunately, the answer is incorrect. You do not receive an additional ability.";
                firefighter.score += 10;
            }
            displayTextSlowly(dial, 5);// Displaying text
        }
        else if (choice == 2) {
            std::string dial = "Hero: Leave!\n\n"
                "Stranger: You'll lose this fight...";
            displayTextSlowly(dial, 5);// Displaying text
        }
        waitForEnter();// Waiting for Enter press
        clearScreen();// Clearing the screen
        }
}
void citadel(Firefighter& firefighter)
{
    // Saving 4 random events
    int itRand = 4;

    // Story description
    std::string hist = "After completing the rescue mission in the Old Town, you directed your steps towards the Citadel.\n"
        "The clues gathered from the townspeople led you right there. The Citadel, towering over the city,\n"
        "was once a symbol of power and protection. Today its walls are covered with ivy, and the towers seem to almost touch the sky.\n"
        "You know that inside awaits a new challenge, perhaps even another dragon.\n"
        "Your mission is clear - you must uncover the secrets of the Citadel and do everything to save the city.";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnterSec();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    // Graphical representation of the road
    std::string text = "######################################################################";
    std::string road = "Road - ";
    srand(time(0));

    // Displaying the graphical path and random event generation
    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));// Pausing iteration for 50 milliseconds
        int randomNumber = rand() % 51;  // Generating a random number from 0 to 50
        if ((itRand <= 4 && itRand >= 1) && randomNumber >= 0 && randomNumber <= 5)
        {
            clearScreen(); // Clearing the screen
            citadelEventItems(itRand, firefighter); // Generating a random event
            itRand -= 1;
        }
        clearScreen(); // Clearing the screen
    }

    // Story description
    hist = "Upon arrival at the citadel, you encountered a massive special fire, which will require a lot of effort to extinguish. Additionally, you notice that the dragon, which previously wreaked havoc, lies with a mighty wound.\n"
        "It is Pyroskryt, a dragon capable of speaking in a human voice. Now you face a difficult battle with fire\n"
        "and an attempt to communicate with the wounded dragon to understand what caused its aggression.";

    // Story description
    hist = "Your task will be to extinguish the fire as quickly as possible by using items from your inventory.\n"
        "If you fail to extinguish it, it will affect the final outcome of the game.";
    displayTextSlowly(hist, 5);   // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    fightEngine(450, 3, firefighter);

    hist = "After extinguishing the fire, the hero managed to reach the injured dragon. The dragon, named Pyroskryt.";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    // Dialogue description
    std::string dial = "Hi, Pyroskryt. How are you feeling?\n\n"
        "Poorly, but I'll survive. Thanks for intervening.\n\n"
        "It's good that I managed to arrive in time. What caused your wounds?\n\n"
        "It's the Lord of Ember. He attacks dragons, provoking them to aggression, and their aggressive behavior leads to fires.\n\n"
        "Lord of Ember? Where can we find him?\n\n"
        "You must go to the hill. That's where he lives. Be careful, as he's a powerful opponent.\n\n"
        "Thanks for the warning. I'm setting off. Thanks, Pyroskryt.";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen
}

// Final of the game and random event
void finalEvent(Firefighter& firefighter)
{
    // Story description
    std::string hist = "You traversed a narrow, winding path through the dark forest. Every step was a challenge,\n"
        "and the dense underbrush made the path even more perilous. Suddenly, in the middle of the road,\n"
        "you spotted the silhouette of an older man leaning on a staff. His white beard and deeply set\n"
        "eyes spoke of great wisdom and experience.\n\n";
    displayTextSlowly(hist, 5); // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    // Dialogue
    std::string dial = "Guardian: Welcome, young warrior, you look like someone with an important task ahead.'\n\n";
    std::string que = "1. Who are you?\n2. How do you know about my task?\n3. Can you help me?\nChoice: ";

    int choice = choice3Options(dial + que); // Choosing one of 3 options
    clearScreen(); // Clearing the screen
    displayTextSlowly(dial, 5); // Displaying text
    if (choice == 1)
    {
        // Dialogue description
        dial += "Hero: Who are you?\n\n"
            "Guardian: I am Althar, the ancient guardian of these forests, responsible. I've been protecting this place and its inhabitants for many years.\n\n"
            "Hero: Why are you here?\n\n"
            "Guardian: I knew someone like you would come. Your heart is pure, and your mission is noble. You need help, and I can provide it.\n\n"
            "Hero: How can you help me?\n\n"
            "Guardian: You've regained some of your abilities, but you're still weaker than you should be. Let me restore your full strength.\n\n"
            "Hero: Thank you, Althar. Now I'm ready to face the Lord of Ember.\n\n"
            "Guardian: Go and fulfill your destiny.";

    }
    else if (choice == 2)
    {
        // Dialogue description
        dial += "Hero: How do you know about my task?\n\n"
            "Guardian: I am Althar, the ancient guardian of these forests. I knew that someone would try to stop the Lord of Ember.\n\n"
            "Hero: How can you help me?\n\n"
            "Guardian: Your determination is admirable, but I see that you are weakened. Let me restore your full strength.\n\n"
            "Hero: Thank you, Althar. Now I'm ready to face the Lord of Ember.\n\n"
            "Guardian: Go and fulfill your destiny.";
    }
    else
    {
        // Dialogue description
        dial += "Hero: Can you help me?\n\n"
            "Guardian: I am Althar, the ancient guardian of these forests. I see that your heart is full of courage, but your body is weakened. "
            "Your task is extremely important. You must be at full strength to face the Lord of Ember.\n\n"
            "Hero: How can you help me?\n\n"
            "Guardian: I can restore your full strength. Let me use my magic to help you regain all your abilities.\n\n"
            "Hero: Thank you, Althar. Now I'm ready to face the Lord of Ember.\n\n"
            "Guardian: Go and fulfill your destiny.";
    }
    displayTextSlowly(dial, 5); // Displaying text
    waitForEnter();  // Waiting for Enter press
    clearScreen();  // Clearing the screen

    // Activating all abilities
    for (auto& item : firefighter.abilities) {
        item.active = true;
    }
}
void final(Firefighter& firefighter)
{
    // Saving 1 random event
    int itRand = 1;

    // History description
    std::string hist = "You took a deep breath and looked towards the hill.\n"
        "Before you stretched a long path, winding through the forest and rising towards dark, stormy clouds gathering over the hilltop. Each step towards the hill seemed heavier,\n"
        "as if the air itself was saturated with danger and mystery.\n"
        "The path was difficult and rugged. Sometimes you had to push through dense thickets,\n"
        "other times you had to bypass fallen trees and cross raging streams. The forest around you was silent,\n"
        "too silent for normal conditions. Even the birds seemed to avoid this place.\n\n";

    displayTextSlowly(hist, 5); // Display text
    waitForEnterSec();  // Wait for Enter press
    clearScreen();  // Clear the screen

    // Graphical representation of the path
    std::string text = "##############################";
    std::string road = "Path - ";
    srand(time(0));

    for (char c : text)
    {
        std::cout << road;
        road += c;
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        int randomNumber = rand() % 51;
        if ((itRand == 1) && randomNumber >= 0 && randomNumber <= 2)
        {
            clearScreen(); // Clear the screen
            finalEvent(firefighter); // Event
            itRand -= 1;
        }
        clearScreen(); // Clear the screen
    }

    // History description
    hist = "You finally reached the foot of the hill. Before you lay steep stairs carved into the rock,\n"
        "leading to the very top. You knew that the Lord of Zaru awaited you at the top, ready for battle. With full determination\n"
        "you began the climb, each step bringing you closer to a confrontation with the mighty opponent.\n\n";
    displayTextSlowly(hist, 5); // Display text
    waitForEnter();  // Wait for Enter press
    clearScreen();  // Clear the screen

    // History description
    hist = "After a long and exhausting climb, you finally reached the top of the hill. Before your eyes appeared the Lord of Zaru\n"
        "in all his glory. He was a mighty dragon with scales like lava, and his breath ignited\n"
        "the air to redness. His eyes burned with sinister intelligence, and around him circled two\n"
        "other dragons - one with sapphire scales, and the other with emerald eyes, both ready to defend their master.\n\n ";

    displayTextSlowly(hist, 5); // Display text
    waitForEnter();  // Wait for Enter press
    clearScreen();  // Clear the screen

    // History description
    hist = "Lord Zaru: Fool, do you think you can defeat me?"
        "You don't know who you're dealing with. I am the lord of fire and destruction!'\n\n"
        "Hero: I'm not afraid of you, Lord Zaru, your wounds on my friend Pyroskryt"
        "will be avenged, and I will put an end to your destructive plans.'\n\n"
        "Lord Zaru: Pyroskryt was weak, and you will share his fate. My servants and I will crush you to dust, and your city will flow with blood!'\n\n";

    displayTextSlowly(hist, 5); // Display text
    waitForEnterSec();  // Wait for Enter press
    clearScreen();  // Clear the screen

    fightEngine(1000, 4, firefighter);

}

// choosing level
int level(int stage, Firefighter& firefighter)
{
    switch (stage)
    {
    case 0:
        centralPark(firefighter);
        break;
    case 1:
        museumOfTechnic(firefighter);
        break;
    case 2:
        library(firefighter);
        break;
    case 3:
        oldTown(firefighter);
        break;
    case 4:
        citadel(firefighter);
        break;
    case 5:
        final(firefighter);
        break;
    }

    return 0;
}

int main() {

    // Create firefighter object
    Firefighter firefighter(0);

    intro(); // Introduction to the game
    int firstItem = firstQuest(firefighter); // First quest

    // Add initial items
    switch (firstItem)
    {
    case 1:
        addItems(1, firefighter); // Add fire extinguisher to inventory
        addItems(1, firefighter); // Add fire extinguisher to inventory
        break;
    case 2:
        addItems(1, firefighter);// Add fire extinguisher to inventory
        addItems(1, firefighter); // Add fire extinguisher to inventory
        addItems(2, firefighter);// Add water bomb to inventory
        break;
    case 3:
        addItems(1, firefighter);// Add fire extinguisher to inventory
        addItems(1, firefighter); // Add fire extinguisher to inventory
        addItems(1, firefighter); // Add fire extinguisher to inventory
        break;
    default:
        break;
    }

    // Array with all locations
    std::string tablica[6] = {
    "Central Park",
    "Museum of Technic",
    "City Library",
    "Old Town",
    "Citadel",
    "Realm of Fire", };


    int stage = 0; // Current level
    int choice;
    while (true) {
        clearScreen(); // Clear the screen
        displayMenu(firefighter.score, tablica[stage]); // Display menu
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::string items;
        int num = 0;
        clearScreen(); // Clear the screen

        switch (choice) {
        case 1:
            level(stage, firefighter); // Start current level
            stage += 1;
            break;
        case 2:
            showMap(); // Show all locations
            break;
        case 3:
            // Check inventory
            if (firefighter.backpack.empty()) {
                items = "NO ITEMS\n";
            }
            else {
                for (const auto& item : firefighter.backpack) {
                    num += 1;
                    items += std::to_string(num) + ". " + item.name + ": " + item.description + "\n";
                }
            }
            displayTextSlowly(items, 5); // Display inventory
            waitForEnterSec(); // Wait for Enter press
            break;
        case 4:
            // Check abilities
            if (firefighter.abilities.empty()) {
                items = "NO ABILITIES\n";
            }
            else {
                for (const auto& item : firefighter.abilities) {
                    num += 1;
                    items += std::to_string(num) + ". " + item.name + ": " + item.description;
                    if (item.active == true)
                    {
                        items += " - Active\n";
                    }
                    else
                    {
                        items += " - Inactive\n";
                    }
                }
            }
            displayTextSlowly(items, 5);// Display all abilities
            waitForEnterSec();// Wait for Enter press
            break;
        case 5:
            // Save (not implemented)
            break;
        case 6:
            target(); // Game goal
            break;
        case 7:
            return 0; // Exit
        default:
            continue;
        }

        // Exit after final stage
        if (stage == 6)
        {
            break;
        }
    }

    std::string finalStage;
    if (firefighter.score >= 0 && firefighter.score <= 1300)
    {
        finalStage = "Unfortunately, you failed to defeat the Realm of Fire. Its power proved too great, and your efforts were insufficient.\n"
            "The city will be burned, and the people will remain defenseless against the dragon attacks. Your defeat will be remembered for ages.\n"
            "Do you gather strength and try again? It's up to you...\n\nScore - " + std::to_string(firefighter.score);

        displayTextSlowly(finalStage, 5); // Display text
        waitForEnterSec();  // Wait for Enter press
        clearScreen();  // Clear the screen
    }
    else if (firefighter.score >= 1300 && firefighter.score <= 1900)
    {
        /// Final riddle
        finalStage = "Your fate is incredibly uncertain. You failed to defeat the Realm of Fire, but you were not completely defeated.\n"
            "Instead, you have one last chance to turn the tide of victory. You must solve one important riddle that will decide your fate.\n\n"
            "To find the right path, you must solve an ancient riddle:\n\n";

        displayTextSlowly(finalStage, 5); // Display text
        waitForEnterSec();  // Wait for Enter press
        clearScreen();  // Clear the screen

        finalStage = "You always come into contact with it, regardless of where you are.\n"
            "Without it, you won't survive, although it can take many forms.\n"
            "It can be cold or hot, calm or stormy.\n"
            "What is it?\n\n"
            "Enter your answer: ";


        displayTextSlowly(finalStage, 5); // Display text
        waitForEnterSec();  // Wait for Enter press
        clearScreen();  // Clear the screen

        std::string userAnswer;
        std::cout << "Enter your answer: ";
        std::cin >> userAnswer;

        if (toLowerCase(userAnswer) == "water") {
            finalStage = "Congratulations! Your courage and determination have allowed you to defeat the Realm of Fire and save the Old Town from destruction.\n"
                "People applaud you, and your name will be remembered with admiration for many years.\n"
                "Your victory brings hope and rebirth to the land. The world awaits your next adventures...\n\nScore - " + std::to_string(firefighter.score);

            displayTextSlowly(finalStage, 5); // Display text
            waitForEnterSec();  // Wait for Enter press
            clearScreen();  // Clear the screen
        }
        else {
            finalStage = "Unfortunately, you failed to defeat the Realm of Fire. Its power proved too great, and your efforts were insufficient.\n"
                "The city will be burned, and the people will remain defenseless against the dragon attacks. Your defeat will be remembered for ages.\n"
                "Do you gather strength and try again? It's up to you...\n\nScore - " + std::to_string(firefighter.score);

            displayTextSlowly(finalStage, 5); // Display text
            waitForEnterSec();  // Wait for Enter press
            clearScreen();  // Clear the screen
        }
    }
    else
    {
        finalStage = "Congratulations! Your courage and determination have allowed you to defeat the Realm of Fire and save the Old Town from destruction.\n"
            "People applaud you, and your name will be remembered with admiration for many years.\n"
            "Your victory brings hope and rebirth to the land. The world awaits your next adventures...\n\nScore - " + std::to_string(firefighter.score);

        displayTextSlowly(finalStage, 5); // Display text
        waitForEnterSec();  // Wait for Enter press
        clearScreen();  // Clear the screen
    }

    return 0;
}




