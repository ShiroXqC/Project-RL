#include <iostream>
#include <string>
#include "entity.h"
#include "player.h" 
#include "item.h"

int main (){
    // Create a player object
    Player player(5, 5); // Starting position (5, 5)

    // Create an item object
    item healthPotion("Health Potion", 2, 3, true); // Example item

    // Display player and item information
    std::cout << "Player HP: " << player.getHp() << std::endl;
    std::cout << "Item Name: " << healthPotion.getName() << std::endl;

    return 0;
}