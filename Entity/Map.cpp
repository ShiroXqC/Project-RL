#include "Map.h"
#include <cstdlib>
#include "Player.h"
#include "Entity.h"

//To update player position 
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

//To start a new turn 
void Map::startNewTurn() 
{
    currentTurn++;
    PlayerTurn = true;
    std::cout << "===Turn "<< currentTurn <<" ===\n";
}

//To get current turn
int Map::getCurrentTurn() const {
    return currentTurn;
}

// Check if there's an item at a location
bool Map::hasItemAt(int x, int y) const {
    for (const Item* item : items) {
        if (item && item->getX() == x && item->getY() == y) {
            return true;
        }
    }
    return false;
}

// Check if there's an enemy at a location
bool Map::hasEnemyAt(int x, int y) const {
    for (const Enemy* enemy : enemies) {
        if (enemy && enemy->getX() == x && enemy->getY() == y) {
            return true;
        }
    }
    return false;
}

// Get item at the given position
Item* Map::getItemAt(int x, int y) const {
    for (Item* item : items) {
        if (item && item->getX() == x && item->getY() == y) {
            return item;
        }
    }
    return nullptr;
}

// Get enemy at the given position
Enemy* Map::getEnemyAt(int x, int y) const {
    for (Enemy* enemy : enemies) {
        if (enemy && enemy->getX() == x && enemy->getY() == y) {
            return enemy;
        }
    }
    return nullptr;
}

// Remove item from game
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

//To handle player movement
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
                removeItem(item);
            }
            
            // Update player position
            grid[player->getY()][player->getX()] = '.';
            player->SetPosition(newX, newY);
            grid[newY][newX] = player->getSymbol();
            moved = true;
        }
        // Check for enemy at destination
        else if (hasEnemyAt(newX, newY)) {
            Enemy* enemy = getEnemyAt(newX, newY);
            handleCombat(enemy); // new combat interaction
            moved = true;
        }        
        // Empty space, just move there
        else if (grid[newY][newX] == '.') {
            // Update player position on grid
            grid[player->getY()][player->getX()] = '.';
            player->SetPosition(newX, newY);
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

//To process enemy turn 
void Map::processEnemyTurns() {
    // Simple enemy movement - random walk
    for (Enemy* enemy : enemies) {
        // Get current position
        int oldX = enemy->getX();
        int oldY = enemy->getY();
        
        // Generate random direction (-1, 0, or 1)
        int dx = rand() % 3 - 1; // -1, 0, or 1
        int dy = rand() % 3 - 1; // -1, 0, or 1
        
        int newX = oldX + dx;
        int newY = oldY + dy;
        
        // Check if moving toward player for a basic "AI"
        if (player) {
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
        if (player && 
            abs(newX - player->getX()) <= 1 && 
            abs(newY - player->getY()) <= 1) {
            // Attack player logic would go here
            std::cout << "Enemy attacks you!\n";
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

void Map::handleCombat(Enemy* enemy) {
    Player* player = getPlayer();
    bool inCombat = true;

    while (inCombat && player->getIsAlive() && enemy->getIsAlive()) {
        system("cls");
        std::cout << "===== COMBAT =====\n";
        std::cout << "You encountered a " << enemy->getSymbol() << "!\n";
        std::cout << "Your HP: " << player->getHealth() << "/" << player->getMaxHealth() << "\n";
        std::cout << enemy->getSymbol() << " HP: " << enemy->getHp() << "\n";
        std::cout << "==================\n";
        std::cout << "[A]ttack  [I]nventory  [R]un\n";
        std::cout << "Choose action: ";

        char input = _getch();
        switch (tolower(input)) {
            case 'a': {
                std::cout << "You attack!\n";
                player->attack(*enemy);
                if (enemy->getHp() <= 0) {
                    std::cout << "Enemy defeated!\n";
                    // Determine drop by symbol:
                    int goldDrop = 0, expDrop = 0;
                    switch (enemy->getSymbol()) {
                      case 'S': goldDrop = 10; expDrop = 5;  break; // Slime
                      case 'G': goldDrop = 15; expDrop = 10; break; // Goblin
                      case 'Z': goldDrop = 24; expDrop = 15; break; // Zombie
                      case 'V': goldDrop = 30; expDrop = 20; break; // Vampire
                      case 'K': goldDrop = 40; expDrop = 30; break; // Death Knight
                      default:  goldDrop = 0;  expDrop = 0;  break;
                    }
                    player->addGold(goldDrop);
                    player->addExp(expDrop);
                    std::cout << "You gained " << goldDrop << " gold and "
                              << expDrop  << " EXP!\n";
                    grid[enemy->getY()][enemy->getX()] = '.';
                    auto it = std::find(enemies.begin(), enemies.end(), enemy);
                    if (it != enemies.end()) enemies.erase(it);
                    delete enemy;
                    inCombat = false;
                    _getch();
                } else {
                    std::cout << "Enemy attacks back!\n";
                    enemy->attack(*player);
                    if (!player->getIsAlive()) {
                        std::cout << "You died!\n";
                        inCombat = false;
                        _getch();
                    }
                }
                break;
            }
            case 'i':
                showInventoryScreen(*player);
                break;
            case 'r':
                std::cout << "You ran away!\n";
                inCombat = false;
                _getch();
                break;
            default:
                std::cout << "Invalid action. Try again.\n";
                _getch();
                break;
        }
    }
}

// Handle items spawning
void Map::spawnRandomItems(int count) {
    **REMOVED**
}

// Implement spawnRandomEnemies
void Map::spawnRandomEnemies(int count) {
    std::vector<std::string> enemyTypes = {"Goblin", "Slime", "Vampire", "Death Knight", "Zombie"};
    
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
    for (int x = 0; x < width; ++x) }
