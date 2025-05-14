#pragma once
#include "Entity.h"
#include <memory>
#include <string>
#include "Inventory.h"


class Player: public Entity
{
    private:
    Inventory inventory;
    char player_symbol = '@';
    int maxHealth;
    int currentHealth;
    int experience = 0;


    public:
    // Constructor that properly initializes the base class
    Player(int startX, int startY, int inventoryCapacity = 10) 
        : Entity(20, 7, 0, startX, startY), // hp=20, attackpower=5, exp=0
          inventory(inventoryCapacity),
          maxHealth(20),
          currentHealth(20)
    {
        // Any additional Player-specific initialization
    }
    
    // Copy constructor - calls base class constructor
    Player(const Player& other) 
        : Entity(other),
          inventory(other.inventory),
          player_symbol(other.player_symbol),
          maxHealth(other.maxHealth),
          currentHealth(other.currentHealth),
          experience(other.experience){}
    
    // Getters
    char getSymbol() const { return player_symbol; }
    Inventory& getInventory() { return inventory; }
    const Inventory& getInventory() const { return inventory; }
    bool isAlive() const { return getHp() > 0; }
    int getMaxHealth() const { return maxHealth; }
    int getHealth() const { return currentHealth; }
    int getAttackpower() const { return attackpower; }
    int getExperience() const { return experience; }

    //Actions
    bool useItem(int index);
    void gainExperience(int exp_);
    void heal(int amount);
    /*void takeDamage(int amount) override;
    void attack(Entity& target) override;*/

    // Inventory
    void addToInventory(std::unique_ptr<Item> item);
    void listInventory() const;
    void showInventory() const;

    ~Player() = default;
};