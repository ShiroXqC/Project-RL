#pragma once 
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Item.h"

class Player; // Forward declaration of Player class

class Inventory {
protected:
    std::vector<std::unique_ptr<Item>> items;
    int capacity;

public:
    Inventory() : capacity(10) {} // Default constructor 
    Inventory(int capacity) : capacity(capacity) {}

    bool addItem(std::unique_ptr<Item> item);
    void listItems() const;
    void useItem(int index, Player& player);
    
    // Getters
    int getCapacity() const { return capacity; }
    int getItemCount() const { return static_cast<int>(items.size()); }
};