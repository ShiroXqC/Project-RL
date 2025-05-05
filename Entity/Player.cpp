#include "Player.h"
#include <iostream>


bool Player::useItem(int index) {
    if (index < 0 || index >= inventory.getItemCount()) {
        std::cout << "Invalid item index!\n";
        return false;
    }
    return true;
}

void Player::heal(int amount) {
    currentHealth += amount; 
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
    std::cout << "Healed for " << amount << " HP. Current health: " << currentHealth << "/" << maxHealth << "\n";
}

void Player::takeDamage(int amount) {
    currentHealth -= amount;
    if (currentHealth <= 0) {
        currentHealth = 0;
        std::cout << "Player has been defeated!\n";
    }
}

int Player::getHealth() const {
    return currentHealth;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

int Player::getAttackDamage() const {
    return attackDamage;
}
void Player::addToInventory(std::unique_ptr<Item> item) {
    if (!inventory.addItem(std::move(item))) {
        std::cout << "Couldn't add item to inventory - full!\n";
    }
}

void Player::listInventory() const {
    inventory.listItems();
}
/*
bool Player::hasItem(const std::string& itemName) const {
    for (int i = 0; i < inventory.getItemCount(); ++i) {
        if (inventory.getItem(i)->getName() == itemName) {
            return true;
        }
    }
    return false;
}

 //Equipment-related methods (if you want to expand to equipment system)
void Player::equipWeapon(std::unique_ptr<Item> weapon) {
    if (weapon->getType() == ItemType::WEAPON) {
        equippedWeapon = std::move(weapon);
        attackDamage = 10 + equippedWeapon->getBonus(); // Base damage + weapon bonus
    }
}

void Player::unequipWeapon() {
    if (equippedWeapon && inventory.addItem(std::move(equippedWeapon))) {
        attackDamage = 10; // Reset to base damage
    }
}
    */