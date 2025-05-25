#include "Inventory.h"
#include "Player.h"
using namespace std;

bool Inventory::addItem(unique_ptr<Item> item){
    if ((int)items.size() < capacity) {
        items.push_back(move(item));    // Move the item into the inventory
        return true;                    // Item added successfully
    }
    cout << "Inventory is full!" << endl;
    return false;                       // Inventory is fullk
    
}

void Inventory::listItems() const {
    cout << "Inventory Items:" << endl;
    for (int i = 0; i < (int)items.size(); ++i) {
        cout << i+1 << ": " << items[i]->getName() << endl;
    }
}
void Inventory::useItem(int index, Player& player) {
    if (index < 0 || index >= getItemCount()) {
        cout << "Invalid item index!" << endl;
        return;
    }
    items[index]->use(player);
    items.erase(items.begin()+index);

    
}