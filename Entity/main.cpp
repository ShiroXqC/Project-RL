#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <conio.h> // For _getch() keyboard input
#include "Item.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "Inventory.h"

// Function to display the main menu
void displayMenu() {
    std::cout << "==== ROGUELIKE GAME ====" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. Instructions" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to display game instructions
void displayInstructions() {
    std::cout << "\n==== GAME INSTRUCTIONS ====" << std::endl;
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
    std::cout << "  U/I/O/B - Other enemy types\n\n";
    std::cout << "Press any key to continue...";
    _getch(); // Wait for any key press
    system("cls"); // Clear screen
}

// Function to display gameplay HUD
void displayHUD(const Map& gameMap) {
    Player* player = gameMap.getPlayer();
    std::cout << "Turn: " << gameMap.getCurrentTurn() << std::endl;
    std::cout << "Position: (" << player->getX() << ", " << player->getY() << ")" << std::endl;
    std::cout << "Controls: [W]Up [A]Left [S]Down [D]Right [Space]Wait [Q]Quit [I]Inventory" << std::endl;
}

// Inventory screen
void showInventoryScreen(Player& player) {
    system("cls");
    player.getInventory().listItems();
    std::cout << "\nSelect item to use (1-" << player.getInventory().getItemCount()
              << "), [E] to equip, or any other key to return: ";
    char input = _getch();
    if (isdigit(input)) {
        int index = input - '1';
        if (index >= 0 && index < player.getInventory().getItemCount()) {
            player.useItem(index);
        }
    }
}

// Shop menu (basic stats adjustments)
void shopMenu(Player* player) {
    int potionsBought = 0;
    while (true) {
        system("cls");
        std::cout << "===== SHOP =====" << std::endl;
        std::cout << "Gold: " << player->getGold() << std::endl;
        std::cout << "1. Health Potion (+10 HP) - 20g  (" << potionsBought << "/10)" << std::endl;
        std::cout << "2. Sword (+3 ATK) - 50g" << std::endl;
        std::cout << "3. Greatsword (+6 ATK) - 100g" << std::endl;
        std::cout << "4. Excalibur (+9 ATK) - 200g" << std::endl;
        std::cout << "5. Shield (reduce dmg by 2) - 30g" << std::endl;
        std::cout << "6. Knight's Shield (reduce dmg by 4) - 70g" << std::endl;
        std::cout << "7. Hero's Shield (reduce dmg by 6) - 175g" << std::endl;
        std::cout << "8. Exit Shop" << std::endl;
        std::cout << "Choose option: ";
        char choice = _getch();
        switch (choice) {
            case '1':
                if (potionsBought >= 10) {
                    std::cout << "Cannot buy more than 10 potions this floor!" << std::endl;
                } else if (player->spendGold(20)) {
                    player.addToInventory(std::make_unique<HealthPotion>(0,0));
                    potionsBought++;
                    std::cout << "Bought 1 Health Potion." << std::endl;
                }
                break;
            case '2': if (player->spendGold(50)) player->addAttackDamage(3); break;
            case '3': if (player->spendGold(100)) player->addAttackDamage(6); break;
            case '4': if (player->spendGold(200)) player->addAttackDamage(9); break;
            case '5': if (player->spendGold(30)) player->addDefense(2); break;
            case '6': if (player->spendGold(70)) player->addDefense(4); break;
            case '7': if (player->spendGold(175)) player->addDefense(6); break;
            case '8': return;
            default: break;
        }
        _getch();
    }
}

// Main game loop with floors
void runGame() {
    srand(static_cast<unsigned>(time(0)));
    const int MAX_FLOORS = 5;
    int baseEnemies = 6;

    for (int floor = 1; floor <= MAX_FLOORS; ++floor) {
        Map gameMap(20, 15);
        gameMap.spawnRandomEnemies(baseEnemies + (floor - 1) * 2);
        gameMap.startNewTurn();

        while (true) {
            system("cls");
            gameMap.display();
            std::cout << "Floor: " << floor << " / " << MAX_FLOORS
                      << "    Turn: " << gameMap.getCurrentTurn() << std::endl;
            std::cout << "Position: (" << gameMap.getPlayer()->getX()
                      << ", " << gameMap.getPlayer()->getY() << ")" << std::endl;
            std::cout << "[WASD] Move  [Space] Wait  [I] Inventory  [Q] Quit" << std::endl;

            char input = _getch();
            if (tolower(input) == 'q') return;
            gameMap.handlePlayerMove(input);
            if (gameMap.getEnemyCount() == 0) {
                std::cout << "\nAll enemies defeated on Floor " << floor << "!" << std::endl;
                _getch();
                shopMenu(gameMap.getPlayer());
                break;
            }
        }
    }
}

int main() {
    int choice;
    bool exit = false;

    while (!exit) {
        system("cls");
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: runGame(); break;
            case 2: displayInstructions(); break;
            case 3: exit = true; break;
            default:
                std::cout << "Invalid choice. Press any key to continue..." << std::endl;
                _getch();
                break;
        }
    }

    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}