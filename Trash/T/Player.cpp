#include "Player.h"
#include <iostream>
using namespace std;

// Attack override that can add special player effects
void Player::attack(Entity& target) {
    cout << "Player attacks!" << endl;
    Entity::attack(target);
}

bool Player::useItem(int index) {
    if (index < 0 || index >= inventory.getItemCount()) {
        cout << "Invalid item index!\n";
        return false;
    }
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
    if (newHp > maxHealth) newHp = maxHealth;
    setHp(newHp);
    cout << "Healed for " << (newHp - oldHp) 
              << " HP. Current health: " << getHp() 
              << "/" << maxHealth << "\n";
}

// Override takeDamage to include player-specific logic
void Player::takeDamage(int amount) {
    // Call base class implementation
    Entity::takeDamage(amount);
    currentHealth = getHp();
    // Add player-specific damage handling
    cout << "Player took " << amount << " damage! Remaining HP: " << getHp() << "\n";
    
    if (!isAlive()) {
        cout << "Player has been defeated!\n";
    }
}

void Player::addToInventory(std::unique_ptr<Item> item) {
    if (!inventory.addItem(move(item))) {
        cout << "Couldn't add item to inventory - full!\n";
    }
}

void Player::listInventory() const {
    inventory.listItems();
}

void Player::showInventory() const {
    const Inventory& inv = getInventory();  

    if (inv.getItemCount() == 0) {
        cout << "Inventory is empty.\n";
        return;
    }
    cout << "Inventory:\n";
    for (int i = 0; i < inv.getItemCount(); ++i) {
        inventory.listItems();
    }
}