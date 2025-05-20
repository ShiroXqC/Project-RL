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
    int level = 1;
    int gold = 0;
    int defense = 2;


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
    : Entity(other), inventory(other.inventory) {
      player_symbol = other.player_symbol;
      maxHealth = other.maxHealth;
      currentHealth = other.currentHealth;
      experience = other.experience;
      level = other.level;
      gold = other.gold;
      defense = other.defense;
}
    
    // Getters
    char getSymbol() const { return player_symbol; }
    Inventory& getInventory() { return inventory; }
    const Inventory& getInventory() const { return inventory; }
    bool isAlive() const { return getHp() > 0; }
    int getMaxHealth() const { return maxHealth; }
    int getHealth() const { return currentHealth; }
    int getAttackpower() const { return attackpower; }
    int getExperience() const { return experience; }
    int getLevel() const { return level; }
    int getXP() const { return experience; }
    int getXPToNextLevel() const { return level * 100; } // XP required increases per level
    int getDefense() const { return defense; }
    int getGold() const { return gold; }
    int getBlock() const { return 0; }

    //Actions
    bool useItem(int index);
    void gainExperience(int exp_);
    void heal(int amount);
    void takeDamage(int amount) override;
    void attack(Entity& target) override;

    // Inventory
    void addToInventory(std::unique_ptr<Item> item);
    void listInventory() const;
    void showInventory() const;

    // New Modifier Methods 
    void addGold(int amount) { gold += amount; }
    void spendGold(int amount) { if (gold >= amount) gold -= amount; }

    void levelUp() {
    level++;
    defense += 1;
    maxHealth += 5;
    setHp(maxHealth); // Heal to full
}

    ~Player() = default;
};