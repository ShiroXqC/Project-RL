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
    // Map variable
    std::vector<std::vector<char>> grid; // 2D grid of chars
    std::vector<Enemy*> enemies;          // Enemy pointers
    std::vector<Item*> items;             // Item pointers
    int width;
    int height;
    Player *player;

    // Check if coordinates are within map boundaries
    bool isInBounds(int x, int y) const {
        return (x >= 0 && x < width && y >= 0 && y < height);
    }

    int currentTurn;
    bool PlayerTurn;

    // Helper to find empty positions
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
            int idx = rand() % emptyPositions.size();
            return emptyPositions[idx];
        }
        return {-1, -1};
    }

public:
    // Default constructor
    Map() : width(10), height(10), currentTurn(0), PlayerTurn(true), player(nullptr) {
        grid.resize(height, std::vector<char>(width, '.'));
        // Walls
        for (int i = 0; i < height; i++) {
            grid[i][0] = '#';
            grid[i][width-1] = '#';
        }
        for (int j = 0; j < width; j++) {
            grid[0][j] = '#';
            grid[height-1][j] = '#';
        }
        // Player in center
        int centerX = width / 2;
        int centerY = height / 2;
        player = new Player(centerX, centerY);
        grid[centerY][centerX] = player->getSymbol();
    }

    // Parameterized constructor
    Map(int x, int y) : width(x), height(y), currentTurn(0), PlayerTurn(true), player(nullptr) {
        if (x < 3) width = 3;
        if (y < 3) height = 3;
        grid.resize(height, std::vector<char>(width, '.'));
        // Walls
        for (int i = 0; i < height; i++) {
            grid[i][0] = '#';
            grid[i][width-1] = '#';
        }
        for (int j = 0; j < width; j++) {
            grid[0][j] = '#';
            grid[height-1][j] = '#';
        }
        // Player in center
        int centerX = width / 2;
        int centerY = height / 2;
        player = new Player(centerX, centerY);
        grid[centerY][centerX] = player->getSymbol();
    }

    // Copy constructor
    Map(const Map& other)
        : grid(other.grid), width(other.width), height(other.height),
          currentTurn(other.currentTurn), PlayerTurn(other.PlayerTurn) {
        if (other.player) player = new Player(*other.player);
        else player = nullptr;
        enemies.reserve(other.enemies.size());
        for (auto e : other.enemies) enemies.push_back(new Enemy(*e));
        items.reserve(other.items.size());
        for (auto it : other.items) items.push_back(new Item(*it));
    }

    // Assignment operator
    Map& operator=(const Map& other) {
        if (this != &other) {
            for (auto e : enemies) delete e;
            for (auto it : items) delete it;
            delete player;
            grid = other.grid;
            width = other.width;
            height = other.height;
            currentTurn = other.currentTurn;
            PlayerTurn = other.PlayerTurn;
            if (other.player) player = new Player(*other.player);
            else player = nullptr;
            enemies.clear(); enemies.reserve(other.enemies.size());
            for (auto e : other.enemies) enemies.push_back(new Enemy(*e));
            items.clear(); items.reserve(other.items.size());
            for (auto it : other.items) items.push_back(new Item(*it));
        }
        return *this;
    }

    // Interactions
    Item* getItemAt(int x, int y) const;
    Enemy* getEnemyAt(int x, int y) const;
    bool hasItemAt(int x, int y) const;
    bool hasEnemyAt(int x, int y) const;
    void removeItem(Item* item);

    Player* getPlayer() const { return player; }
    void updatePlayerPosition(int oldX, int oldY, int newX, int newY);
    bool handlePlayerMove(char input);

    void startNewTurn();
    int getCurrentTurn() const;

    void processEnemyTurns();

    // Items disabled for now
    void spawnRandomItems(int count);

    void spawnRandomEnemies(int count);
    void display() const;

    ~Map() {
        for (auto e : enemies) delete e;
        for (auto it : items) delete it;
        delete player;
    }
};
