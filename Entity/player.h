#pragma once
#include "Inventory.h"
#include "Entity.h"
#include <vector>
#include <string>
#include <memory>

class Player {
protected:
    Inventory inventory;
    int x, y;
    int maxHealth;
    int currentHealth;
    int attackDamage;
    int defense;
    int gold;
    int exp;                // Total experience
    int level;              // Player level (0-5)
    char player_symbol = '@';

public:
    // Constructor
    Player(int startX, int startY, int inventoryCapacity = 10)
      : x(startX), y(startY), inventory(inventoryCapacity),
        maxHealth(20), currentHealth(20), attackDamage(7),
        defense(0), gold(0), exp(0), level(0) {}

    // Copy constructor
    Player(const Player& other)
      : x(other.x), y(other.y), inventory(other.inventory),
        maxHealth(other.maxHealth), currentHealth(other.currentHealth),
        attackDamage(other.attackDamage), defense(other.defense),
        gold(other.gold), exp(other.exp), level(other.level),
        player_symbol(other.player_symbol) {}

    // Getters
    int getLevel() const { return level; }
    int getExp() const { return exp; }
    int getHealth() const { return currentHealth; }
    int getMaxHealth() const { return maxHealth; }
    int getAttackDamage() const { return attackDamage; }
    int getDefense() const { return defense; }
    int getGold() const { return gold; }
    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return player_symbol; }
    Inventory& getInventory() { return inventory; }

    bool getIsAlive() const { return currentHealth > 0; }

    // Setters (for movement)
    void SetPosition(int newX, int newY) { x = newX; y = newY; }
    void SetPlayerX(int startX) { x = startX; }
    void SetPlayerY(int startY) { y = startY; }

    // Combat and stats
    void heal(int amount);
    void takeDamage(int amount);
    void attack(Entity& target);

    // Gold management
    void addGold(int amount);
    bool spendGold(int amount);

    // Stat bonuses
    void addAttackDamage(int bonus);
    void addDefense(int bonus);

    // Inventory
    bool useItem(int index);
    void addToInventory(std::unique_ptr<Item> item);
    void listInventory() const;

    // Experience and leveling
    void addExp(int amount);
};
