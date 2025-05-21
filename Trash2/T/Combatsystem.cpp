#include "CombatSystem.h"
#include <iostream>

void CombatSystem::startCombat(Player* player, Enemy* enemy) {
    playerTurn = true; // Player goes first
    std::cout << "\n=== Combat Started ===" << std::endl;
}

bool CombatSystem::processTurn(Player* player, Enemy* enemy) {
    if (!player || !enemy) return true; // End combat if either is null
    
    if (playerTurn) {
        // Player's turn
        std::cout << "\nYour turn:" << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Use Item" << std::endl;
        std::cout << "Choose action: ";
        
        int choice;
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                player->attack(*enemy);
                std::cout << "You dealt " << player->getAttackpower() 
                          << " damage to the enemy!" << std::endl;
                break;
            case 2:
                // Show inventory and let player choose item
                player->listInventory();
                std::cout << "Choose item (0 to cancel): ";
                int itemIndex;
                std::cin >> itemIndex;
                if (itemIndex > 0) {
                    player->useItem(itemIndex - 1);
                }
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                return false;
        }
    } else {
        // Enemy's turn
        std::cout << "\nEnemy's turn:" << std::endl;
        enemy->attack(*player);
        std::cout << "The enemy dealt " << enemy->getAttackpower() 
                  << " damage to you!" << std::endl;
    }
    
    // Check if combat should end
    if (!enemy->getIsAlive()) {
        std::cout << "\nYou defeated the enemy!" << std::endl;
        return true;
    }
    if (!player->getIsAlive()) {
        std::cout << "\nYou have been defeated!" << std::endl;
        return true;
    }
    
    // Switch turns
    playerTurn = !playerTurn;
    return false;
}