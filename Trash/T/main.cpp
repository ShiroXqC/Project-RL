#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <conio.h> // For _getch() keyboard input
#include "Item.h"
#include "Entity.h"
#include "player.h"
#include "Map.h"
#include "Enemy.h"

// Function to display the main menu
void displayMenu() {
    std::cout << "==== ROGUELIKE GAME ====\n";
    std::cout << "1. Start New Game\n";
    std::cout << "2. Instructions\n";
    std::cout << "3. Quit\n";
    std::cout << "=====================\n";
    std::cout << "Enter your choice: ";
}

// Function to display game instructions
void displayInstructions() {
    std::cout << "\n==== GAME INSTRUCTIONS ====\n";
    std::cout << "Controls:\n";
    std::cout << "  W - Move up\n";
    std::cout << "  A - Move left\n";
    std::cout << "  S - Move down\n";
    std::cout << "  D - Move right\n";
    std::cout << "  Space - Wait a turn\n";
    std::cout << "  I - Open Inventory (not implemented yet)\n";
    std::cout << "  Q - Quit game\n\n";
    
    std::cout << "Symbols:\n";
    std::cout << "  @ - You (the player)\n";
    std::cout << "  G - Goblin enemy\n";
    std::cout << "  S - Slime enemy or Sword item\n";
    std::cout << "  # - Wall\n";
    std::cout << "  . - Empty floor\n";
    std::cout << "  H - Health potion\n";
    std::cout << "  U/I/O/B - Other enemy types\n\n";
    
    std::cout << "Press any key to continue...";
    _getch(); // Wait for any key press
    system("cls"); // Clear screen
}

// Function to display gameplay HUD
 void displayHUD(const Map& gameMap) {
    Player* player = gameMap.getPlayer();
    
    std::cout << "Turn: " << gameMap.getCurrentTurn() << "\n";
    
    // Display player health with health bar
    std::cout << "HP: " << player->getHealthBar() << " " 
              << player->getHp() << "/" << player->getMaxHp() << "\n";
    
    // Attack power
    std::cout << "Attack: " << player->getAttackpower() << "\n";
    
    std::cout << "Position: (" << player->getX() << ", " << player->getY() << ")\n";
    std::cout << "Controls: [W]Up [A]Left [S]Down [D]Right [Space]Wait [Q]Quit\n";
}

// Function to run the game loop
void runGame() {
    // Initialize game
    srand(static_cast<unsigned int>(time(0))); // Seed random generator
    Map gameMap(20, 15); // Create a 20x15 map
    
    // Spawn items and enemies
    gameMap.spawnRandomItems(8);
    gameMap.spawnRandomEnemies(6);
    
    // Start the game's turn counter
    gameMap.startNewTurn();
    
    bool running = true;
    
    // Game loop
    while (running) {
        // Clear screen (Windows specific - replace with appropriate command for other OS)
        system("cls");
        
        // Display the map
        gameMap.display();
        
        // Display HUD
        displayHUD(gameMap);
        
        // Check if player is dead
        if (!gameMap.getPlayer()->getIsAlive()) {
            std::cout << "\n===== GAME OVER =====\n";
            std::cout << "You have been defeated!\n";
            std::cout << "Press any key to return to main menu...\n";
            _getch();
            return;
        }
        
        // Get player input (without requiring Enter key)
        char input = _getch();
        
        // Process input
        switch (tolower(input)) {
            case 'q': // Quit game
                running = false;
                break;
                
            case 'w': // Up
            case 'a': // Left
            case 's': // Down
            case 'd': // Right
            case ' ': // Wait/skip turn
                if (!gameMap.handlePlayerMove(input)) {
                    // If handlePlayerMove returns false, either the move was invalid
                    // or the player died during the move
                    if (!gameMap.getPlayer()->getIsAlive()) {
                        continue; // This will trigger the game over check next loop
                    } else {
                        std::cout << "\nInvalid move! Press any key to continue...";
                        _getch();
                    }
                }
                break;
                
            case 'i': // Inventory (placeholder)
                std::cout << "\nInventory not implemented yet. Press any key to continue...";
                _getch();
                break;
                
            default:
                std::cout << "\nUnknown command. Press any key to continue...";
                _getch();
                break;
        }
    }
}
int main() {
    int choice;
    bool exit = false;
    
    while (!exit) {
        system("cls"); // Clear screen
        displayMenu();
        std::cin >> choice;
        
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
                std::cout << "Invalid choice. Press any key to continue...";
                _getch();
                break;
        }
    }
    
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}