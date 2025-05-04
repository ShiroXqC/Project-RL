#include <iostream>
#pragma once 
#include <map>
#include <string>
#include <vector>
#include <memory> // For std::unique_ptr dynamic memory management 

class Iventory {
    protected:
    std::vector<std::unique_ptr<item>>; // Vector to store item names
    int capacity; // Maximum capacity of the inventory
    public:
    Inventory(int capacity);

    bool addItem(std::unique_ptr<item> item); // Add an item to the inventory
    void listItems() const; // List all items in the inventory
    void useItem(int index); // Use an item from the inventory


    // Getters
    int getCapacity() const;
}
