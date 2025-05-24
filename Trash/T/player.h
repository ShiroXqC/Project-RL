#pragma once
#include "Entity.h"
#include <memory>
#include <string>
#include "Inventory.h"
#include "Item.h"
using namespace std;

class Player : public Entity {
private:
    Inventory inventory;
    char player_symbol = '@';
    int maxHealth;
    int currentHealth;
    int experience;
    int level;
    int xpToNextLevel = 50;
    int gold;
    int defense;

public:
    Player(int startX = 20, int startY = 7, int inventoryCapacity = 10,
           int hp = 20, int attackpower = 10000, int exp = 0,
           int currentHealth = 20, int maxHealth = 20,
           int level = 1, int gold = 50, int defense = 2)
        : Entity(hp, attackpower, exp, startX, startY),
          inventory(inventoryCapacity),
          player_symbol('@'),
          maxHealth(maxHealth),
          currentHealth(currentHealth),
          experience(exp),
          level(level),
          gold(gold),
          defense(defense) {}

    Player(const Player& other)
        : Entity(other), inventory(other.inventory),
          player_symbol(other.player_symbol), maxHealth(other.maxHealth),
          currentHealth(other.currentHealth), experience(other.experience),
          level(other.level), xpToNextLevel(other.xpToNextLevel),
          gold(other.gold), defense(other.defense) {}

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
    int getXPToNextLevel() const { return xpToNextLevel; }
    int getDefense() const { return defense; }
    int getGold() const { return gold; }

    // Actions
    bool useItem(int index);
    void gainExperience(int exp);
    void gainGold_From_Enemy(int gold_dropped);
    void heal(int amount);
    void takeDamage(int amount) override;
    void attack(Entity& target) override;

    // Inventory
    void addToInventory(unique_ptr<Item> item);
    void listInventory() const;
    void showInventory() const;

    // Modifiers
    void addGold(int amount) { gold += amount; }
    bool spendGold(int amount) {
        if (gold >= amount) {
            gold -= amount;
            return true;
        }
        return false;
    }

    void addAttackDamage(int amount) { attackpower += amount; }
    void addDefense(int amount) { defense += amount; }
 

    ~Player() = default;
};
