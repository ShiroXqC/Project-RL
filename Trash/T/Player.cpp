#include "Player.h"
#include <iostream>


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
    while (experience >= xpToNextLevel) {
        experience -= xpToNextLevel;
        level++;
        xpToNextLevel += 50;
        maxHealth += 5;
        attackpower += 2;
        setHp(maxHealth); // Heal to full
        cout << "Level up! New level: " << level << "\n";
    }
}

// Get gold dropped from enemy 
void Player::gainGold_From_Enemy(int gold_dropped) {
    gold += gold_dropped; 
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
    int netDamage = max(0, amount - defense);  // Use defense to reduce damage
    Entity::takeDamage(netDamage);
    currentHealth = getHp();

    cout << "Player took " << netDamage << " damage! Remaining HP: "
         << getHp() << "/" << maxHealth << "\n";

    if (!isAlive()) {
        cout << "Player has been defeated!\n";
    }
}
// Add Item To Inventory
void Player::addToInventory(unique_ptr<Item> item) {
    if (!inventory.addItem(move(item))) {
        cout << "Couldn't add item to inventory - full!\n";
    }
}

// List Player Inventory 
void Player::listInventory() const {
    inventory.listItems();
}

// Show Player Inventory 
void Player::showInventory() const {
    const Inventory& inv = getInventory();  
    if (inv.getItemCount() == 0) {
        cout << "Inventory is empty.\n";
        return;
    }
    cout << "Inventory:\n";
    inv.listItems();
}
