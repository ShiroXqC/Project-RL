#pragma once 
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory> // For std::unique_ptr dynamic memory management 
#include "Item.h" // Include the Item class header

class Player; // Forward declaration of Player class
 
class Item; // Forward declaration of Item class

class Inventory {
    protected:
    std::vector<std::unique_ptr<Item>> items; // Vector to store item names
    int capacity; // Maximum capacity of the inventory
    public:
    Inventory() : capacity(10) {} // Default constructor 
    Inventory(int capacity);

    bool addItem(std::unique_ptr<Item> item); // Add an item to the inventory
    void listItems() const; // List all items in the inventory
    bool useItem(int index, Player& player); // Use an item from the inventory


    // Getters
    int getCapacity() const;
    int getItemCount() const {return static_cast<int>(items.size()); }
};
