#include "Combat.h"
#include <iostream>

void Combat::startCombat(Player& player, Enemy& enemy) {
    std::cout << "A wild " << enemy.getSymbol() << " appears!\n";

    while (player.isAlive() && enemy.isAlive()) {
        std::cout << "\nPlayer HP: " << player.getHp() << " | Enemy HP: " << enemy.getHp() << "\n";
        std::cout << "Choose an action:\n1. Attack\n2. Use Item\n3. Run\n> ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                enemy.takeDamage(player.getAttackpower());
                std::cout << "You dealt " << player.getAttackpower() << " damage!\n";
                break;
            }
           case 2: {
                player.showInventory();  // Optional: Display inventory to player
                std::cout << "Enter item index to use: ";
                int itemIndex;
                std::cin >> itemIndex;
                if (!player.useItem(itemIndex)) {
                std::cout << "Failed to use item!\n";
                }
                break;
            }
            case 3: {
                std::cout << "You ran away!\n";
                return;
            }
            default:
                std::cout << "Invalid choice.\n";
                continue;
        }

        if (enemy.isAlive()) {
            player.takeDamage(enemy.getAttackpower());
            std::cout << "Enemy dealt " << enemy.getAttackpower() << " damage!\n";
        }
    }

    if (!player.isAlive()) 
        std::cout << "You have been defeated.\n";
    else {
        std::cout << "Enemy has been defeated!\n";
        player.gainExperience(enemy.getExperience());
    }
}
