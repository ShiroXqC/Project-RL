#pragma once
#include "entity.h"
#include <vector>
#include <string>
#include "Item.h"
#include "Inventory.h"


class Player: public Entity
{
    private:
    Inventory inventory;
    char player_symbol = '@';
    int maxHealth;
    int currentHealth;
    int experience = 0;
    int level;
    int xp;
    int xpToNextLevel;
    int defense;
    int block;
    int minAttack;
    int maxAttack;
    int gold;


    public:
    // Constructor that properly initializes the base class
    Player(int startX, int startY, int inventoryCapacity = 10) 
        : Entity(20, 5, 0, startX, startY), // hp=20, attackpower=5, exp=0
          inventory(inventoryCapacity),
          maxHealth(20),
          currentHealth(20),
          xp(0),
          level(1)
    {
        // Any additional Player-specific initialization
    }
    
    // Copy constructor - calls base class constructor
    Player(const Player& other) 
        : Entity(other),
          inventory(other.inventory),
          player_symbol(other.player_symbol),
          maxHealth(other.maxHealth),
          currentHealth(other.currentHealth)
    {
    }
    
    // Getters
    char getSymbol() const { return player_symbol; }
    Inventory& getInventory() { return inventory; }
    const Inventory& getInventory() const { return inventory; }
    bool useItem(int index);
    int getMaxHealth() const;
    int getHealth() const;
    int getLevel() const;
    int getXP() const;
    int getXPToNextLevel() const;
    int getDefense() const;
    int getBlock() const;
    int getMinAtk() const;
    int getMaxAtk() const;
    int getGold() const;
    void gainExperience(int exp);
    void showInventory() const;


    // Override virtual methods from Entity
    void attack(Entity& target) override;
    
    // Item management
    void addToInventory(std::unique_ptr<Item> item);
    void listInventory() const;
    bool hasItem(const std::string& itemName) const;
    
    // Health management
    void heal(int amount);
    void takeDamage(int amount);
};