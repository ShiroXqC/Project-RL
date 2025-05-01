#include <iostream>
#include <string>
#include "item.h"
#include "Entity.h"
#include "player.h"

int main (){
    // Create a player object
   
    // Create an item object
    item healthPotion("Health Potion", 2, 3, true); // Example item

    // Display player and item information

    std::cout << "Item Name: " << healthPotion.getName() << std::endl;

    return 0;
}