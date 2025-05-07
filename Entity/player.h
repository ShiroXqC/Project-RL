#pragma once
#include "entity.h"
#include <vector>
#include <string>
#include "Inventory.h"
#include "Item.h"

class Player: public Entity
{
    protected:
    Inventory inventory;
    int x; // Position X
    int y; // Position Y
    int Health;
    int maxHealth;
    int attackpower;
    int currentHealth;
    int attackDamage;
    char player_symbol = '@';

   
    // std::vector<Item*> inventory;

    public:
    // Constructor
    Player(int startX, int startY, int inventoryCapacity = 10) : x(startX), y(startY), inventory(inventoryCapacity){}
    
    // Copy constructor
    Player(const Player& other) : x(other.x), y(other.y), player_symbol(other.player_symbol) {}
    
    // Getters
    int getHealth() const;
    int getMaxHealth() const;
    int getAttackPower() const;
    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return player_symbol; }
    Inventory& getInventory() { return inventory; }
    bool useItem(int index);
    bool IsAlive() const;
    int getCurrentHealth() const { return Health; }
    int getAttackDamage() const;
    bool getIsAlive() const { return true; } 

    //Item 
    void addToInventory(std::unique_ptr<Item> item);
    void listInventory() const;
    bool hasItem(const std::string& itemName) const;
    void equipWeapon(std::unique_ptr<Item> weapon);


    // Setters (for movement)
    void SetPosition(int newX, int newY) { x = newX; y = newY; }
    void SetPlayerX(int startX) { x = startX; }
    void SetPlayerY(int startY) { y = startY; }
    // Setters for health and attack
    void heal(int amount);
    void takeDamage(int amount);
};