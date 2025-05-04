#include "Inventory.h"

Inventory::Inventory(int capacity):
    capacity(capacity){}
bool Inventory::addItem(std::unique_ptr<Item> item){
    if (items.size() < capacity) {
        items.push_back(std::move(item)); // Move the item into the inventory
        return true; // Item added successfully
    } else {
        std::cout << "Inventory is full!" << std::endl;
        return false; // Inventory is full
    }
}
void Inventory::listItems() const {
    std::cout << "Inventory Items:" << std::endl;
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << items[i]->getName() << std::endl;
    }
}
void Inventory::useItem(int index) {
    if (index < 0 || index >= items.size()) {
        std::cout << "Invalid item index!" << std::endl;
        return; // Invalid index
    }
    
    Item* item = items[index].get(); // Get the item pointer
    if (item->isConsumable()) {
        std::cout << "Using item: " << item->getName() << std::endl;
        // Implement item usage logic here
        // For example, if it's a health potion, increase player's health
        if (item->getName() == "Health Potion") {
            // Increase player's health logic here
            std::cout << "Player's health increased!" << std::endl;
        }
        
        // Remove the item from the inventory if it's consumed on use
        items.erase(items.begin() + index);
    } else {
        std::cout << "Item is not consumable!" << std::endl;
    }
}