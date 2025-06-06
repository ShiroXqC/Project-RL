#include <ctime>
#include <cstdlib>
#include <conio.h> // This is for _getch() keyboard input
#include "Item.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "Combat.h"
#include "Inventory.h"
#include "UI.h"
#include "Shop.h" 
#include <iostream>
using namespace std;

void handleInventory(Player* player);
void displayMenu();
void displayInstructions();
void runGame();

// Function to display inventory
void handleInventory(Player* player) {
    cout << "\n==== INVENTORY ====\n";
    player->getInventory().listItems();
    
    cout << "\nEnter item number to use (or 0 to exit): ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= player->getInventory().getItemCount()) {
        player->getInventory().useItem(choice - 1, *player);
    } else if (choice == 0) {
        return;
    } else { 
        cout << "Invalid choice!\n";
    }
}

// Function to display the main menu
void displayMenu() {
    cout << "==== ROGUELIKE GAME ====\n";
    cout << "1. Start New Game\n";
    cout << "2. Instructions\n";
    cout << "3. Quit\n";
    cout << "=====================\n";
    cout << "Enter your choice: ";
}

// Function to display game instructions
void displayInstructions() {
    cout << "\n==== GAME INSTRUCTIONS ====\n";
    cout << "Controls:\n";
    cout << "  w - Move up\n";
    cout << "  a - Move left\n";
    cout << "  s - Move down\n";
    cout << "  d - Move right\n";
    cout << "  i - Open Inventory\n";
    cout << "  p - Open Shop\n";
    cout << "  q - Quit game\n\n";
    
    cout << "Symbols:\n";
    cout << "  @ - You (the player)\n";
    cout << "  G - Goblin\n";
    cout << "  S - Slime\n";
    cout << "  V - Vampire\n";
    cout << "  K - Death knight\n";
    cout << "  Z - Zombie\n";
    cout << "  # - Wall\n";
    cout << "  . - Empty floor\n\n";
    cout << "Press any key to continue...";

    _getch();
    system("cls");

}

// Function to run the game loop
void runGame() {

    // Seed random generator
    srand(static_cast<unsigned int>(time(0))); 

    // Create a 20x15 map
    Map gameMap(20, 15); 
    
    // Randomly spawn enemies
    gameMap.spawnRandomEnemies(6);
    
    // Start the game's turn counter
    gameMap.startNewTurn();
    
    bool running = true;
    
    // Game loop
    while (running) {

        system("cls");
        
        // Display HUD
        UI::drawMainUI(gameMap);

        // Check if player is dead
        if (!gameMap.getPlayer()->getIsAlive()) {
            cout << "\n===== GAME OVER =====\n";
            cout << "You have been defeated!\n";
            cout << "Press any key to return to main menu...\n";
            _getch();
            return;
        }
        
        // Get player input
        char input = _getch();
        
        // Process input
        switch (tolower(input)) {
            case 'q':
                running = false;
                break;

            case 'w':
            case 'a':
            case 's':
            case 'd':
            case ' ': 
                if (!gameMap.handlePlayerMove(input)) {
                    if (!gameMap.getPlayer()->getIsAlive()) {
                        continue;
                    } else {
                        cout << "\nInvalid move! Press any key to continue...";
                        _getch();
                    }
                }
                break;

            case 'i':
                handleInventory(gameMap.getPlayer());
                break;

            case 'p': 
                {
                Shop shop(gameMap.getPlayer());  
                shop.DisplayShop();
                shop.Choices();   
                break;
                }
                
            default:
                cout << "\nUnknown command. Press any key to continue...";
                _getch();
                break;
        }
    }
}

int main() {
    int choice;
    bool exit = false;
    
    while (!exit) {
        system("cls");
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: // Start game
                runGame();
                break;
                
            case 2: // Instructions
                displayInstructions();
                break;
                
            case 3: // Quit
                exit = true;
                break;
                
            default:
                cout << "Invalid choice. Press any key to continue...";
                _getch();
                break;
        }
    }
    
    cout << "Thanks for playing!" << endl;
    return 0;
}