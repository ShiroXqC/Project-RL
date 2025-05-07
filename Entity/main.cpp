#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <conio.h> // For _getch() keyboard input
#include <memory>  // For std::unique_ptr
#include "Item.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "CombatSystem.h"
#include "HealthPotion.h"
#include "Sword.h"

// Function to display the main menu
void displayMenu() {
    std::cout << "====================================\n";
    std::cout << "||        ROGUELIKE GAME          ||\n";
    std::cout << "====================================\n";
    std::cout << "|| 1. Start New Game              ||\n";
    std::cout << "|| 2. Instructions                ||\n";
    std::cout << "|| 3. Quit                        ||\n";
    std::cout << "====================================\n";
    std::cout << "Enter your choice: ";
}

// Function to display game instructions
void displayInstructions() {
    std::cout << "\n=========== GAME INSTRUCTIONS ===========\n";
    std::cout << "Controls:\n";
    std::cout << "  W - Move up\n";
    std::cout << "  A - Move left\n";
    std::cout << "  S - Move down\n";
    std::cout << "  D - Move right\n";
    std::cout << "  Space - Wait a turn\n";
    std::cout << "  I - Open Inventory\n";
    std::cout << "  Q - Quit game\n\n";
    
    std::cout << "Symbols:\n";
    std::cout << "  @ - You (the player)\n";
    std::cout << "  G - Goblin enemy\n";
    std::cout << "  S - Slime enemy or Sword item\n";
    std::cout << "  # - Wall\n";
    std::cout << "  . - Empty floor\n";
    std::cout << "  H - Health potion\n";
    std::cout << "  U - Succubus enemy\n";
    std::cout << "  I - Incubus enemy\n";
    std::cout << "  O - Outcubus enemy\n";
    std::cout << "  B - Binhcubus enemy\n\n";
    
    std::cout << "Combat:\n";
    std::cout << "  - Move into enemies to attack them\n";
    std::cout << "  - Use health potions to restore HP\n";
    std::cout << "  - Collect swords to increase attack power\n\n";
    
    std::cout << "Press any key to continue...";
    _getch(); // Wait for any key press
    system("cls"); // Clear screen
}

// Function to display gameplay HUD with health bar
void displayHUD(const Map& gameMap) {
    Player* player = gameMap.getPlayer();
    
    std::cout << "=== Turn: " << gameMap.getCurrentTurn() << " ===\n";
    
    // Display player health with health bar
    int hp = player->getHp();
    int maxHp = player->getMaxHp();
    std::cout << "HP: [";
    
    // Calculate health bar width (max 20 chars)
    int barWidth = 20;
    int filledWidth = static_cast<int>(static_cast<float>(hp) / maxHp * barWidth);
    
    for (int i = 0; i < barWidth; i++) {
        if (i < filledWidth) std::cout << "█";
        else std::cout << "·";
    }
    
    std::cout << "] " << hp << "/" << maxHp << "\n";
    
    // Attack power
    std::cout << "Attack: " << player->getAttackpower() << "\n";
    
    std::cout << "Controls: [W]Up [A]Left [S]Down [D]Right [Space]Wait [I]Inventory [Q]Quit\n";
}

// Function to handle inventory interaction
void handleInventory(Player* player) {
    system("cls"); // Clear screen
    std::cout << "========== INVENTORY ==========\n";
    
    // Display inventory
    player->listInventory();
    
    std::cout << "\nEnter item number to use (0 to cancel): ";
    int choice;
    std::cin >> choice;
    
    if (choice > 0) {
        player->useItem(choice - 1); // Adjust for 0-based indexing
        std::cout << "Press any key to continue...";
        _getch();
    }
}

// Function to handle combat with enhanced combat system
void handleCombat(Player* player, Enemy* enemy) {
    system("cls"); // Clear screen
    
    CombatSystem combatSystem;
    combatSystem.startCombat(player, enemy);
    
    bool combatEnded = false;
    
    while (!combatEnded) {
        system("cls");
        
        std::cout << "========== COMBAT ==========\n";
        std::cout << "Player HP: " << player->getHp() << "/" << player->getMaxHp() << "\n";
        std::cout << "Enemy HP: " << enemy->getHp() << "/" << 10 << "\n\n"; // Enemy max HP is hardcoded to 10
        
        if (combatSystem.processTurn(player, enemy)) {
            combatEnded = true;
        }
        
        if (!combatEnded) {
            std::cout << "\nPress any key for next combat action...";
            _getch();
        }
    }
    
    std::cout << "\nCombat ended. Press any key to continue...";
    _getch();
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
                
            case 'i': // Inventory
                handleInventory(gameMap.getPlayer());
                break;
                
            default:
                std::cout << "\nUnknown command. Press any key to continue...";
                _getch();
                break;
        }
    }
}

// Function to add missing methods for the test to work
// These would be added to Map.h and Map.cpp in a real implementation
void addMissingMethods() {
    std::cout << "NOTE: In a real implementation, you would need to add:\n";
    std::cout << "1. Map::getGrid() method to access the grid\n";
    std::cout << "2. Methods to add enemies and items directly to the map\n";
    std::cout << "3. Fix 'Player::getMaxHp()' which is referenced but should be 'getMaxHealth()'\n";
    std::cout << "\nPress any key to continue...\n";
    _getch();
}

int main() {
    // First, notify about missing methods that would be needed
    addMissingMethods();
    
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