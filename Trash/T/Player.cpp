#include "Player.h"
#include <iostream>

// Attack override that can add special player effects
void Player::attack(Entity& target) {
    std::cout << "Player attacks!" << std::endl;
    
    // Call the base class implementation
    Entity::attack(target);
    
    // Could add special player attack effects here
}

bool Player::useItem(int index) {
    if (index < 0 || index >= inventory.getItemCount()) {
        std::cout << "Invalid item index!\n";
        return false;
    }
    
    // Implement item usage logic
    inventory.useItem(index, *this);
    return true;
}
// Gain experience and level up 
void Player::gainExperience(int exp) {
    experience += exp;
}


void Player::heal(int amount) {
    int oldHp = getHp();
    int newHp = oldHp + amount;
    
    // Cap at maximum health
    if (newHp > maxHealth) {
        newHp = maxHealth;
    }
    
    setHp(newHp);
    std::cout << "Healed for " << (newHp - oldHp) << " HP. Current health: " 
              << getHp() << "/" << maxHealth << "\n";
}

// Override takeDamage to include player-specific logic
void Player::takeDamage(int amount) {
    // Call base class implementation
    Entity::takeDamage(amount);
    
    // Add player-specific damage handling
    std::cout << "Player took " << amount << " damage! Remaining HP: " << getHp() << "\n";
    
    if (!getIsAlive()) {
        std::cout << "Player has been defeated!\n";
    }
}

int Player::getHealth() const {
    return getHp(); // Use the base class getter
}

int Player::getMaxHealth() const {
    return maxHealth;
}

void Player::addToInventory(std::unique_ptr<Item> item) {
    if (!inventory.addItem(std::move(item))) {
        std::cout << "Couldn't add item to inventory - full!\n";
    }
}

void Player::listInventory() const {
    inventory.listItems();
}