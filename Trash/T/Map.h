#pragma once
#include"Enemy.h"
#include"Player.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Map
{
    protected:
    vector<vector<char>> grid; //Vector of vector or in other words a 2d matrix of vector of type char (Vector^2)
    vector<Enemy*> enemies;
    int width;
    int height;
    int currentFloor = 1;
    int static const MAX_FLOORS = 4; 
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
    pair<int, int> getRandomEmptyPosition() const {
    vector<pair<int, int>> emptyPositions;
        
        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                if (grid[y][x] == '.' && 
                    !(player && x == player->getX() && y == player->getY())) {
                    emptyPositions.emplace_back(x, y);
                }
            }
        }
        
        if (emptyPositions.empty()) {
            return make_pair(-1, -1);
        }
        return emptyPositions[rand()%emptyPositions.size()]; // No empty positions
    }

    public:
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    char getTile(int x, int y) const { return grid[y][x]; }
    int getFloor() const { return currentFloor; }

    // Default constructor
    Map() : width(10), height(10), currentTurn(0), PlayerTurn(true), player(nullptr)
    {
        // Initialize grid with '.' (empty spaces)
        grid.resize(height, vector<char>(width, '.'));
        
        // Add some basic walls around the edges
        for (int i = 0; i < height; i++) {
            grid[i][0] = '#';       // Left wall
            grid[i][width-1] = '#'; // Right wall
        }
        for (int j = 0; j < width; j++) {
            grid[0][j] = '#';        // Top wall
            grid[height-1][j] = '#'; // Bottom wall
        }
        
        // Player in the middle of the map
        int centerX = width / 2;
        int centerY = height / 2;
        player = new Player(centerX, centerY);
        grid[centerY][centerX] = player->getSymbol();
    }
    
    Map(int x, int y) : width(x), height(y), currentTurn(0), PlayerTurn(true), player(nullptr) {
        // Basic validation (minimum size 3x3)
        if (x < 3) width = 3;
        if (y < 3) height = 3;
        
        // Initialize grid with '.' (empty spaces)
        grid.resize(height, vector<char>(width, '.'));
        
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
    }
    
    // Assignment operator
    Map& operator=(const Map& other) {
        if (this != &other) {
            // Clean up existing resources
            for (Enemy* e : enemies) delete e;
            enemies.clear();
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
        }
        return *this;
    }

    Enemy* getEnemyAt(int x, int y) const;
    bool hasEnemyAt(int x, int y) const;
    Player* getPlayer() const { return player; }
    void updatePlayerPosition(int oldX, int oldY, int newX, int newY); 
    bool handlePlayerMove(char input);
    void display() const;
    void spawnRandomEnemies(int count);
    void loadNextFloor();

    //Turn management
    void startNewTurn();
    int getCurrentTurn() const;

    //Enemy turn handling (placeholder)
    void processEnemyTurns();
    void removeEnemy(Enemy* enemy);
    
    ~Map() {
        for (Enemy* e : enemies)
            delete e;
        enemies.clear();
        delete player;
    }
};