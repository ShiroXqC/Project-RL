    #include "Map.h"
    #include "HealthPotion.h"
    #include "Sword.h"
    #include <cstdlib>
    #include "Combat.h"
    #include <algorithm> // For std::remove_if

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
        for (const auto& ptr : items) {
            const Item* item = ptr.get();
            if (item->getX() == x && item->getY() == y) {
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
        for (auto& ptr : items) {
            const Item* item = ptr.get();
            if (item->getX() == x && item->getY() == y) {
                return const_cast<Item*>(ptr.get()); 
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
    // Remove enemy from game
    void Map::removeEnemy(Enemy* enemy) {
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [&](Enemy* e) {
                return e == enemy;
            }), enemies.end());
}
    int Map::getWidth() const { return width; }
    int Map::getHeight() const { return height; }

  char Map::getTile(int x, int y) const {
    // First, check if any enemy is at (x, y)
    for (const Enemy* enemy : enemies) {
        if (enemy->getX() == x && enemy->getY() == y) {
            return '!';  // Enemy symbol
        }
    }

    return grid[y][x];  
}

    // Remove item from game
    void Map::removeItem(Item* item) {
        if (!item) return;
        
        // Find and remove from grid
        grid[item->getY()][item->getX()] = '.';
        
        // Find and remove from items vector
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->get () == item) {
                items.erase(it);  // Remove from vector
                break;
            }
        }
    }

    //To handle player movement
    bool Map::handlePlayerMove(char input) {
        if (!PlayerTurn) return false;
        
        int oldX = player->getX();
        int oldY = player->getY();
        int newX = oldX;
        int newY = oldY;
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
        Enemy* enemy = getEnemyAt(newX, newY);
        if (enemy) {
        Combat::startCombat(*player, *enemy);
        if (!enemy->isAlive()) {
            removeEnemy(enemy); // You'll need to implement this
            updatePlayerPosition(oldX, oldY, newX, newY);
        }
        return true;
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
                player->setPosition(newX, newY);
                grid[newY][newX] = player->getSymbol();
                moved = true;
            }
            // Check for enemy at destination
            else if (hasEnemyAt(newX, newY)) {
                Enemy* enemy = getEnemyAt(newX, newY);
                std::cout << "You attack the " << enemy->getSymbol() << "!\n";
                // Combat logic would go here in a more complete game
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
                    int oldX = player->getX();
                    int oldY = player->getY();
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

    // Handle items spawning
    void Map::spawnRandomItems(int count) {
        for (int i = 0; i < count; ++i) {
            auto pos = getRandomEmptyPosition();
            if (pos.first == -1) break; // no space left
    
            Item* item = Item::createRandomItem(pos.first, pos.second);
            items.push_back(std::unique_ptr<Item>(item));
            grid[pos.second][pos.first] = item->getDisplayChar();
        }
    }
    
    // Implement spawnRandomEnemies
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
 
