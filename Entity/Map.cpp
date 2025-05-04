#include "Map.h"
#include "HealthPotion.h"
#include "Sword.h"
#include <cstdlib> 

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
    if (isInBounds(newX, newY) && grid[newY][newX] == '.') 
    {
        // Update player position on grid
        grid[player->getY()][player->getX()] = '.';
        player->SetPosition(newX, newY);
        grid[newY][newX] = player->getSymbol();
        moved = true;
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
    std::cout << "Enemies are moving...\n";
    for (Enemy* enemy : enemies) {
        // Get current position
        int oldX = enemy->getX();
        int oldY = enemy->getY();
        
        // Generate random direction (-1, 0, or 1)
        int dx = rand() % 3 - 1; // -1, 0, or 1
        int dy = rand() % 3 - 1; // -1, 0, or 1
        
        int newX = oldX + dx;
        int newY = oldY + dy;
        
        // Validate move
        if (isInBounds(newX, newY) && grid[newY][newX] == '.') {
            grid[oldY][oldX] = '.';
            enemy->setPosition(newX, newY);
            grid[newY][newX] = enemy->getSymbol();
        }
    }
}

// Handle items spawning - Fixed: moved out of processEnemyTurns
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
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << grid[y][x];
        }
        std::cout << std::endl;
    }
}