#pragma once
#include "entity.h"
#include <vector>
#include <string>
#include "Inventory.h"

class Player
{
    protected:
    Inventory inventory;
    int x; // Position X
    int y; // Position Y
    char player_symbol = '@';
    // In the future, you could add:
    // int health;
    // int maxHealth;
    // std::vector<Item*> inventory;

    public:
    // Constructor
    Player(int startX, int startY, int inventoryCapacity = 10) : x(startX), y(startY), inventory(inventoryCapacity){}
    
    // Copy constructor
    Player(const Player& other) : x(other.x), y(other.y), player_symbol(other.player_symbol) {}
    
    // Getters
    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return player_symbol; }
    Inventory& getInventory();
    bool useItem(int index);

    // Setters (for movement)
    void SetPosition(int newX, int newY) { x = newX; y = newY; }
    void SetPlayerX(int startX) { x = startX; }
    void SetPlayerY(int startY) { y = startY; }
};