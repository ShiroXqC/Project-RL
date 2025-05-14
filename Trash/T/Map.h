#pragma once
#include"Item.h"
#include"Enemy.h"
#include"Entity.h"
#include"Player.h"
#include <iostream>
#include <string>
#include <vector>

class Map
{
    private:
    //Map variable
    std::vector<std::vector<char>> grid; //Vector of vector or in other words a 2d matrix of vector of type char (Vector^2)
    std::vector<Enemy*> enemies; //Vector containing Enemy pointer
    std::vector<std::unique_ptr<Item>> items; //Vector containing Item pointer 
    int width;
    int height;
    Player *player;

    //Check if coordinates are within map boundaries
    bool isInBounds(int x, int y) const
    {
        return (x >= 0 && x<width && y >=0 && y<height);
    }
    
    //For Player turn based movement
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
    //Default Constructor
    // Default constructor - creates a small empty map
    Map() : width(10), height(10), currentTurn(0), PlayerTurn(true), player(nullptr)
    {
        // Initialize grid with '.' (empty spaces) by setting the number of rows and column and filling them with _
        grid.resize(height, std::vector<char>(width, '.'));
        
        // Add some basic walls around the edges
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
    
    // Parameterized constructor - creates map with specified dimensions
    Map(int x, int y) : width(x), height(y), currentTurn(0), PlayerTurn(true), player(nullptr) {
        // Basic validation (minimum size 3x3)
        if (x < 3) width = 3;
        if (y < 3) height = 3;
        
        // Initialize grid with '.' (empty spaces)
        grid.resize(height, std::vector<char>(width, '.'));
        
        // Add some basic walls around the edges
        for (int i = 0; i < height; i++) {
            grid[i][0] = '#';       // Left wall
            grid[i][width-1] = '#'; // Right wall
        }
        for (int j = 0; j < width; j++) {
            grid[0][j] = '#';        // Top wall
            grid[height-1][j] = '#'; // Bottom wall
        }

        //Generate player in the middle of the map 
        int centerX = width / 2;
        int centerY = height / 2;
        player = new Player(centerX, centerY);
        grid[centerY][centerX] = player->getSymbol();
    }
    
    // Copy constructor
    Map(const Map& other) : 
        grid(other.grid),
        width(other.width),
        height(other.height),
        currentTurn(other.currentTurn),
        PlayerTurn(other.PlayerTurn)
    {
        // Deep copy player
        if (other.player) {
            player = new Player(*(other.player));
        } else {
            player = nullptr;
        }
        
        // Deep copy enemies
        enemies.reserve(other.enemies.size());
        for (const Enemy* e : other.enemies) {
            if (e) {
                enemies.push_back(new Enemy(*e)); // Assuming Enemy has a copy constructor
            }
        }
        
        // Deep copy items
        items.reserve(other.items.size());
        for (const auto& ptr: other.items) {
            const Item* i = ptr.get();
            if (i) {
                items.push_back(i->clone()); // Using Item's copy constructor
            }
        }
    }
    
    // Assignment operator
    Map& operator=(const Map& other) {
        if (this != &other) {
            // Clean up existing resources
            for (Enemy* e : enemies) delete e;
            enemies.clear();
            items.clear();
            delete player;
            
            // Copy simple members
            grid = other.grid;
            width = other.width;
            height = other.height;
            currentTurn = other.currentTurn;
            PlayerTurn = other.PlayerTurn;
            
            // Deep copy player
            if (other.player) {
                player = new Player(*(other.player));
            } else {
                player = nullptr;
            }
            
            // Deep copy enemies
            enemies.clear();
            enemies.reserve(other.enemies.size());
            for (const Enemy* e : other.enemies) {
                if (e) {
                    enemies.push_back(new Enemy(*e));
                }
            }
            
            // Deep copy items
            items.clear();
            items.reserve(other.items.size());
            for (const auto& ptr : other.items) {
                const Item* i = ptr.get();
                if (i) {
                    items.push_back(i->clone());
                }
            }
        }
        return *this;
    }

    // Item and entity interaction
    Item* getItemAt(int x, int y) const;
    Enemy* getEnemyAt(int x, int y) const;
    bool hasItemAt(int x, int y) const;
    bool hasEnemyAt(int x, int y) const;
    void removeItem(Item* item);

    // Add method to get player
    Player* getPlayer() const { return player; }

    // Add method to update player position on grid
    void updatePlayerPosition(int oldX, int oldY, int newX, int newY); 

    //Turn base movement method
    bool handlePlayerMove(char input);

    //Turn management
    void startNewTurn();
    int getCurrentTurn() const;

    //Enemy turn handling (placeholder)
    void processEnemyTurns();
    void removeEnemy(Enemy* enemy);

    //Handle item spawning
    void spawnRandomItems(int count);
    void display() const;

    //To spawn random enemies
    void spawnRandomEnemies(int count);

    //Destructor
    ~Map() {
        for (Enemy* e : enemies)
            delete e;
            enemies.clear();
            items.clear();
        delete player;
    }
};