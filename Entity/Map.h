#pragma once
#include "Item.h"
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

class Map
{
    private:
    // Map variables
    std::vector<std::vector<char>> grid;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    int width;
    int height;
    Player* player;
    
    // Combat variables
    bool inCombat;
    Enemy* currentEnemy;

    // Check if coordinates are within map boundaries
    bool isInBounds(int x, int y) const
    {
        return (x >= 0 && x < width && y >= 0 && y < height);
    }
    
    // For Player turn based movement
    int currentTurn;
    bool PlayerTurn;

    // Helper method to find empty positions
    std::pair<int, int> getRandomEmptyPosition() const {
        std::vector<std::pair<int, int>> emptyPositions;
        
        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                if (grid[y][x] == '.' && 
                    !(player && x == player->getX() && y == player->getY())) {
                    emptyPositions.emplace_back(x, y);
                }
            }
        }
        
        if (!emptyPositions.empty()) {
            int index = rand() % emptyPositions.size();
            return emptyPositions[index];
        }
        return {-1, -1}; // No empty positions
    }

public:
    // Default Constructor
    Map() : width(10), height(10), currentTurn(0), PlayerTurn(true), 
            player(nullptr), inCombat(false), currentEnemy(nullptr)
    {
        // Initialize grid with '.' (empty spaces)
        grid.resize(height, std::vector<char>(width, '.'));
        
        // Add basic walls around the edges
        for (int i = 0; i < height; i++) {
            grid[i][0] = '#';       // Left wall
            grid[i][width-1] = '#'; // Right wall
        }
        for (int j = 0; j < width; j++) {
            grid[0][j] = '#';        // Top wall
            grid[height-1][j] = '#'; // Bottom wall
        }
        
        // Create player in the middle of the map
        int centerX = width / 2;
        int centerY = height / 2;
        player = new Player(centerX, centerY);
        grid[centerY][centerX] = player->getSymbol();
    }
    
    // Parameterized constructor
    Map(int x, int y) : width(x), height(y), currentTurn(0), PlayerTurn(true), 
                        player(nullptr), inCombat(false), currentEnemy(nullptr) {
        // Basic validation (minimum size 3x3)
        if (x < 3) width = 3;
        if (y < 3) height = 3;
        
        // Initialize grid with '.' (empty spaces)
        grid.resize(height, std::vector<char>(width, '.'));
        
        // Add walls around the edges
        for (int i = 0; i < height; i++) {
            grid[i][0] = '#';       // Left wall
            grid[i][width-1] = '#'; // Right wall
        }
        for (int j = 0; j < width; j++) {
            grid[0][j] = '#';        // Top wall
            grid[height-1][j] = '#'; // Bottom wall
        }

        // Generate player in the middle of the map 
        int centerX = width / 2;
        int centerY = height / 2;
        player = new Player(centerX, centerY);
        grid[centerY][centerX] = player->getSymbol();
    }
    
    // Item and entity interaction
    Item* getItemAt(int x, int y) const;
    Enemy* getEnemyAt(int x, int y) const;
    bool hasItemAt(int x, int y) const;
    bool hasEnemyAt(int x, int y) const;
    void removeItem(Item* item);
    void removeEnemy(Enemy* enemy);

    // Player accessor
    Player* getPlayer() const { return player; }

    // Update player position on grid
    void updatePlayerPosition(int oldX, int oldY, int newX, int newY);

    // Turn-based movement method
    bool handlePlayerMove(char input);

    // Turn management
    void startNewTurn();
    int getCurrentTurn() const;

    // Enemy turn handling
    void processEnemyTurns();

    // Handle item spawning
    void spawnRandomItems(int count);
    void display() const;

    // Spawn random enemies
    void spawnRandomEnemies(int count);

    // Combat system
    void startCombat(Enemy* enemy);
    void endCombat();
    void processCombatTurn(int playerChoice);

    // Destructor
    ~Map() {
        for (Enemy* e : enemies)
            delete e;
        for (Item* i : items)
            delete i;
        delete player;
    }
};