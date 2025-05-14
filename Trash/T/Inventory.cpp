#include "Inventory.h"
#include "Player.h"


bool Inventory::addItem(std::unique_ptr<Item> item){
    if ((int)items.size() < capacity) {
        items.push_back(std::move(item)); // Move the item into the inventory
        return true; // Item added successfully
    }
    std::cout << "Inventory is full!" << std::endl;
    return false; // Inventory is full
    
}

void Inventory::listItems() const {
    std::cout << "Inventory Items:" << std::endl;
    for (int i = 0; i < (int)items.size(); ++i) {
        std::cout << i<< ": " << items[i]->getName() << std::endl;
    }
}
void Inventory::useItem(int index, Player& player) {
    if (index < 0 || index >= getItemCount()) {
        std::cout << "Invalid item index!" << std::endl;
        return;
    }
    items[index]->use(player);
    items.erase(items.begin()+index);
    
}