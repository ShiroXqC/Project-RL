#include "Map.h"
#include "HealthPotion.h"
#include "Sword.h"
#include <cstdlib>

// Add the missing removeEnemy function
void Map::removeEnemy(Enemy* enemy) {
    if (!enemy) return;
    
    // Find and remove from grid
    grid[enemy->getY()][enemy->getX()] = '.';
    
    // Find and remove from enemies vector
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        if (*it == enemy) {
            delete *it;  // Free memory
            enemies.erase(it);  // Remove from vector
            break;
        }
    }
}

void Map::updatePlayerPosition(int oldX, int oldY, int newX, int newY) 
{
    if (isInBounds(oldX, oldY)) 
    {
        grid[oldY][oldX] = '.'; // Clear old position
    }
    if (isInBounds(newX, newY)) 
    {
        grid[newY][newX] = player->getSymbol(); // Set new position
    }
}

void Map::startNewTurn() 
{
    currentTurn++;
    PlayerTurn = true;
    std::cout << "===Turn "<< currentTurn <<" ===\n";
}

int Map::getCurrentTurn() const {
    return currentTurn;
}

bool Map::hasItemAt(int x, int y) const {
    for (const Item* item : items) {
        if (item && item->getX() == x && item->getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::hasEnemyAt(int x, int y) const {
    for (const Enemy* enemy : enemies) {
        if (enemy && enemy->getX() == x && enemy->getY() == y) {
            return true;
        }
    }
    return false;
}

Item* Map::getItemAt(int x, int y) const {
    for (Item* item : items) {
        if (item && item->getX() == x && item->getY() == y) {
            return item;
        }
    }
    return nullptr;
}

Enemy* Map::getEnemyAt(int x, int y) const {
    for (Enemy* enemy : enemies) {
        if (enemy && enemy->getX() == x && enemy->getY() == y) {
            return enemy;
        }
    }
    return nullptr;
}

void Map::removeItem(Item* item) {
    if (!item) return;
    
    // Find and remove from grid
    grid[item->getY()][item->getX()] = '.';
    
    // Find and remove from items vector
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (*it == item) {
            delete *it;  // Free memory
            items.erase(it);  // Remove from vector
            break;
        }
    }
}

bool Map::handlePlayerMove(char input) {
    if (!PlayerTurn) return false;

    int newX = player->getX();
    int newY = player->getY();
    bool moved = false;
    
    switch(tolower(input))
    {
        case 'w': // Up
            newY--;
            break;
        case 's': // Down
            newY++;
            break;
        case 'a': // Left
            newX--;
            break;
        case 'd': // Right
            newX++;
            break;
        case ' ': // Wait/skip turn
            moved = true;
            break;
        default:
            return false; // Invalid input
    }

    // Check if move is valid
    if (isInBounds(newX, newY)) {
        // Check for item at destination
        if (hasItemAt(newX, newY)) {
            Item* item = getItemAt(newX, newY);
            std::cout << "You found a " << item->getName() << "!\n";
            
            // If it's consumable, use it and remove
            if (item->isConsumable()) {
                // In a more complete game, apply item effects here
                std::cout << "You used the " << item->getName() << "!\n";
                
                // Health potion logic
                if (item->getName() == "Health Potion") {
                    player->heal(5); // Heal by 5 points
                }
                
                removeItem(item);
            }
            
            // Update player position
            grid[player->getY()][player->getX()] = '.';
            player->setPosition(newX, newY);
            grid[newY][newX] = player->getSymbol();
            moved = true;
        }
        // Check for enemy at destination
        else if (hasEnemyAt(newX, newY)) {
            Enemy* enemy = getEnemyAt(newX, newY);
            std::cout << "You attack the enemy!\n";
            
            // Implement combat logic
            player->attack(*enemy);
            std::cout << "You dealt " << player->getAttackpower() << " damage!\n";
            
            // Check if enemy died
            if (!enemy->getIsAlive()) {
                std::cout << "You defeated the enemy!\n";
                removeEnemy(enemy);
                
                // Move to the position
                grid[player->getY()][player->getX()] = '.';
                player->setPosition(newX, newY);
                grid[newY][newX] = player->getSymbol();
            } else {
                // Enemy survives and counter-attacks
                enemy->attack(*player);
                std::cout << "The enemy counter-attacks for " << enemy->getAttackpower() << " damage!\n";
            }
            
            moved = true;
        }
        // Empty space, just move there
        else if (grid[newY][newX] == '.') {
            // Update player position on grid
            grid[player->getY()][player->getX()] = '.';
            player->setPosition(newX, newY);
            grid[newY][newX] = player->getSymbol();
            moved = true;
        }
        // Wall or other obstacle
        else {
            std::cout << "You can't move there.\n";
        }
    }
    
    if (moved) {
        PlayerTurn = false; // End player's turn
        processEnemyTurns(); // Let enemies move
        startNewTurn(); // Start next turn
    }
    
    return moved;
}

void Map::processEnemyTurns() {
    // Simple enemy movement - random walk
    for (Enemy* enemy : enemies) {
        // Skip if enemy no longer exists
        if (!enemy || !enemy->getIsAlive()) continue;
        
        // Get current position
        int oldX = enemy->getX();
        int oldY = enemy->getY();
        
        // Generate random direction (-1, 0, or 1)
        int dx = rand() % 3 - 1; // -1, 0, or 1
        int dy = rand() % 3 - 1; // -1, 0, or 1
        
        int newX = oldX + dx;
        int newY = oldY + dy;
        
        // Check if moving toward player for a basic "AI"
        if (player && player->getIsAlive()) {
            // Calculate distance to player
            int currentDist = abs(oldX - player->getX()) + abs(oldY - player->getY());
            int newDist = abs(newX - player->getX()) + abs(newY - player->getY());
            
            // 70% chance to move toward player if possible
            if (rand() % 10 < 7 && newDist > currentDist) {
                // Try to move toward player instead
                if (oldX < player->getX()) dx = 1;
                else if (oldX > player->getX()) dx = -1;
                else dx = 0;
                
                if (oldY < player->getY()) dy = 1;
                else if (oldY > player->getY()) dy = -1;
                else dy = 0;
                
                // Recalculate new position
                newX = oldX + dx;
                newY = oldY + dy;
            }
        }
        
        // Check if can attack player (adjacent)
        if (player && player->getIsAlive() && 
            abs(newX - player->getX()) <= 1 && 
            abs(newY - player->getY()) <= 1) {
            
            // Attack player
            enemy->attack(*player);
            std::cout << "Enemy attacks you for " << enemy->getAttackpower() << " damage!\n";
            
            continue; // Skip movement after attack
        }
        
        // Validate move
        if (isInBounds(newX, newY) && grid[newY][newX] == '.') {
            grid[oldY][oldX] = '.';
            enemy->setPosition(newX, newY);
            grid[newY][newX] = enemy->getSymbol();
        }
    }
}

void Map::spawnRandomItems(int count) {
    for (int i = 0; i < count; ++i) {
        // Get random empty location
        std::pair<int, int> pos = getRandomEmptyPosition();
        if (pos.first == -1) break; // No space

        // Alternate between HealthPotion and Sword
        Item* item;
        if (i % 2 == 0)
            item = new HealthPotion(pos.first, pos.second);
        else
            item = new Sword(pos.first, pos.second);

        items.push_back(item);
        grid[pos.second][pos.first] = item->getDisplayChar();
    }
}

void Map::spawnRandomEnemies(int count) {
    std::vector<std::string> enemyTypes = {"Goblin", "Slime", "Succubus", "Incubus", "Outcubus", "Binhcubus"};
    
    for (int i = 0; i < count; ++i) {
        // Get random empty location
        std::pair<int, int> pos = getRandomEmptyPosition();
        if (pos.first == -1) break; // No space left

        // Choose a random enemy type
        std::string type = enemyTypes[rand() % enemyTypes.size()];
        Enemy* enemy = new Enemy(pos.first, pos.second, type);
        enemies.push_back(enemy);
        grid[pos.second][pos.first] = enemy->getSymbol();
    }
}

void Map::display() const {
    // First print top border with column numbers (tens digit)
    std::cout << "   ";
    for (int x = 0; x < width; ++x) {
        std::cout << (x / 10);
    }
    std::cout << std::endl;
    
    // Print column numbers (ones digit)
    std::cout << "   ";
    for (int x = 0; x < width; ++x) {
        std::cout << (x % 10);
    }
    std::cout << std::endl;

    // Print the grid with row numbers
    for (int y = 0; y < height; ++y) {
        std::cout << y / 10 << y % 10 << " "; // Row number
        for (int x = 0; x < width; ++x) {
            std::cout << grid[y][x];
        }
        std::cout << std::endl;
    }
}

// Combat system functions
void Map::startCombat(Enemy* enemy) {
    if (!enemy || !player) return;
    
    inCombat = true;
    currentEnemy = enemy;
    std::cout << "\n=== Combat Started ===" << std::endl;
}

void Map::endCombat() {
    inCombat = false;
    currentEnemy = nullptr;
    std::cout << "\n=== Combat Ended ===" << std::endl;
}

void Map::processCombatTurn(int playerChoice) {
    if (!inCombat || !currentEnemy || !player) return;
    
    static bool playerTurn = true;
    
    if (playerTurn) {
        switch(playerChoice) {
            case 1: // Attack
                player->attack(*currentEnemy);
                std::cout << "You dealt " << player->getAttackpower() 
                          << " damage!" << std::endl;
                break;
            case 2: // Use Item
                // Implement item usage from inventory
                break;
            default:
                return;
        }
    } else {
        // Enemy's turn
        currentEnemy->attack(*player);
        std::cout << "The enemy dealt " << currentEnemy->getAttackpower() 
                  << " damage!" << std::endl;
    }
    
    // Check if combat ended
    if (!currentEnemy->getIsAlive()) {
        std::cout << "Enemy defeated!" << std::endl;
        removeEnemy(currentEnemy);
        endCombat();
        return;
    }
    if (!player->getIsAlive()) {
        std::cout << "You were defeated!" << std::endl;
        // Handle game over
        endCombat();
        return;
    }
    
    // Switch turns
    playerTurn = !playerTurn;
    
    if (playerTurn) {
        std::cout << "\nYour turn. Choose action:\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Use Item\n";
    }
}