#include "Inventory.h"
#include "Player.h"
#include <iostream>

// Constructor with capacity
Inventory::Inventory(int capacity)
    : capacity(capacity) {}

// Add an item to the inventory
bool Inventory::addItem(std::unique_ptr<Item> item) {
    if (items.size() < capacity) {
        items.push_back(std::move(item));
        return true;
    } else {
        std::cout << "Inventory is full!" << std::endl;
        return false;
    }
}

// List all items
void Inventory::listItems() const {
    std::cout << "Inventory Items:" << std::endl;
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << items[i]->getName() << std::endl;
    }
}

// Use an item from the inventory
void Inventory::useItem(int index, Player& player) {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        std::cout << "Invalid item index!" << std::endl;
        return;
    }

    Item* item = items[index].get();
    if (item->isConsumable()) {
        std::cout << "Using item: " << item->getName() << "\n";

        // Health Potion effect
        if (item->getName() == "Health Potion") {
            player.heal(10);
        }

        // Remove consumable item
        items.erase(items.begin() + index);
    } else {
        std::cout << "Item is not consumable!" << std::endl;
    }
}
