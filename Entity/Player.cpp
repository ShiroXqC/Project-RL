#include "Player.h"
#include "Entity.h"
#include <algorithm>
#include <iostream>

// Actions
void Player::heal(int amount) {
    currentHealth = std::min(currentHealth + amount, maxHealth);
    std::cout << "Healed for " << amount << " HP. "
              << "Current health: " << currentHealth << "/" << maxHealth << "\n";
}

void Player::takeDamage(int amount) {
    int damage = std::max(0, amount - defense);
    currentHealth -= damage;
    std::cout << "Took " << damage << " damage. "
              << "HP: " << currentHealth << "/" << maxHealth << "\n";
    if (currentHealth <= 0) {
        std::cout << "Player has been defeated!\n";
    }
}

void Player::attack(Entity& target) {
    target.takeDamage(attackDamage);
}

// Gold management
void Player::addGold(int amount) { gold += amount; }
bool Player::spendGold(int amount) {
    if (gold >= amount) { gold -= amount; return true; }
    std::cout << "Not enough gold!\n";
    return false;
}

// Stat bonuses
void Player::addAttackDamage(int bonus) {
    attackDamage += bonus;
    std::cout << "Attack increased by " << bonus
              << ". New attack: " << attackDamage << "\n";
}

void Player::addDefense(int bonus) {
    defense += bonus;
    std::cout << "Defense increased by " << bonus
              << ". New defense: " << defense << "\n";
}

// Inventory
bool Player::useItem(int index) {
    if (index < 0 || index >= inventory.getItemCount()) return false;
    inventory.useItem(index, *this);
    return true;
}

void Player::addToInventory(std::unique_ptr<Item> item) {
    inventory.addItem(std::move(item));
}

void Player::listInventory() const { inventory.listItems(); }

// Experience and leveling
void Player::addExp(int amount) {
    exp += amount;
    std::cout << "EXP increased by " << amount
              << ". Total EXP: " << exp << "\n";

    static const int thresholds[5] = {50, 100, 150, 200, 250};
    while (level < 5 && exp >= thresholds[level]) {
        level++;
        maxHealth += 2;
        attackDamage += 2;
        defense += 2;
        currentHealth = std::min(currentHealth + 2, maxHealth);
        std::cout << "Leveled up! Now level " << level << "\n";
    }
}
