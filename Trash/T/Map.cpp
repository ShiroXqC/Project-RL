    #include "Map.h"
    #include "HealthPotion.h"
    #include <cstdlib>
    #include "Enemy.h"
    #include "Combat.h"
    #include <conio.h> // For _getch()
    #include <algorithm> // For remove_if
    #include <string>
    #include <iostream>


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
        cout << "===Turn "<< currentTurn <<" ===\n";
    }

    //To get current turn
    int Map::getCurrentTurn() const {
        return currentTurn;
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
    if (enemy) {
        int x = enemy->getX();
        int y = enemy->getY();
        if (isInBounds(x, y)) {
            grid[y][x] = '.';  
        }
    }

    enemies.erase(remove_if(enemies.begin(), enemies.end(),
        [&](Enemy* e) {
            return e == enemy;
        }), enemies.end());

    delete enemy;
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
            default:
                return false; // Invalid input
        }
        Enemy* enemy = getEnemyAt(newX, newY);
        if (enemy) {
        Combat::startCombat(*player, *enemy);
        if (!enemy->getIsAlive()) {
            removeEnemy(enemy);
        if (enemies.empty()){
            cout << "\n=== You have cleared the floor [Press] any key to continue ===\n";
            _getch();
            loadNextFloor();
        }
        }
            return true;
        }
             // Check if move is valid
        if (isInBounds(newX, newY)) {
            // Empty space, just move there
            if (grid[newY][newX] == '.') {
                // Update player position on grid
                grid[player->getY()][player->getX()] = '.';
                player->setPosition(newX, newY);
                grid[newY][newX] = player->getSymbol();
                moved = true;
            }
            // Wall or other obstacle
            else {
                cout << "You can't move there.\n";
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
            // Make the boss stay still
            if (enemy->getSymbol() == 'D') continue;
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
                cout << "Enemy attacks you!\n";
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

    // Implement spawnRandomEnemies
    void Map::spawnRandomEnemies(int count) {
        vector<string> enemyTypes = {"Goblin", "Slime", "Vampire", "Death Knight", "Zombie"};
        if (currentFloor == MAX_FLOORS) {
        auto [x, y] = getRandomEmptyPosition();
        if (x != -1) {
            Enemy* boss = new Enemy(x, y, "Dragon", 0);
            enemies.push_back(boss);
            grid[y][x] = boss->getSymbol();
            cout << "\n!!! The Final Boss has appeared !!!\n";
        }
        return;
    }
        for (int i = 0; i < count; ++i) {
            // Get random empty location
            pair<int, int> pos = getRandomEmptyPosition();
            if (pos.first == -1) break; // No space left

            // Choose a random enemy type
            string type = enemyTypes[rand() % enemyTypes.size()];
            Enemy* enemy = new Enemy(pos.first, pos.second, type, 5);
            enemies.push_back(enemy);
            grid[pos.second][pos.first] = enemy->getSymbol();
        }
    }

    void Map::display() const {
        // First print top border with column numbers (tens digit)
        cout << "   ";
        for (int x = 0; x < width; ++x) {
            cout << (x / 10);
        }
        cout << endl;

     
        // Print column numbers (ones digit)
        cout << "   ";
        for (int x = 0; x < width; ++x) {
            cout << (x % 10);
        }
        cout << endl;

        // Print the grid with row numbers
        for (int y = 0; y < height; ++y) {
            cout << y / 10 << y % 10 << " "; // Row number
            for (int x = 0; x < width; ++x) {
                cout << grid[y][x];
            }
            cout << endl;
        }
    }
 void Map::loadNextFloor() {
    if (currentFloor >= MAX_FLOORS) {
        system("cls");
    cout << "\nYou have cleared Floor " << currentFloor << ", the final challenge!\n";
    cout << "Sadly the smoking hot babe is in another dungeon!\n";
    cout << "\nPress any key to exit...\n";
        _getch();
        exit(0);
    return;
    }
    currentFloor++;
    cout << "\n--- Descending to Floor " << currentFloor << " ---\n";

    // Clear enemies 
    for (Enemy* e : enemies) delete e;
    enemies.clear();

    // Reset grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x] = '.';
        }
    }

    // Re-add walls
    for (int i = 0; i < height; i++) {
        grid[i][0] = '#';
        grid[i][width - 1] = '#';
    }
    for (int j = 0; j < width; j++) {
        grid[0][j] = '#';
        grid[height - 1][j] = '#';
    }

    // Move player to center
    int centerX = width / 2;
    int centerY = height / 2;
    player->setPosition(centerX, centerY);
    grid[centerY][centerX] = player->getSymbol();

    // Spawn stronger enemies (optional scaling)
    int enemyCount = 5 + (currentFloor - 1) * 2;
    spawnRandomEnemies(enemyCount);

    startNewTurn();
}
