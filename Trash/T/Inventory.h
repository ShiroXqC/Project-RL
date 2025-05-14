#pragma once 
#include <map>
#include <vector>
#include <memory> // For std::unique_ptr dynamic memory management 
#include "Item.h" // Include the Item class header

class Player; 
class Inventory {
    protected:
        std::vector<std::unique_ptr<Item>> items; // Vector to store item names
        int capacity; // Maximum capacity of the inventory
    public:
        Inventory(int cap = 10) : capacity(10) {} // Default constructor 
        Inventory(const Inventory& other) : capacity(other.capacity) {
            for (const auto& item : other.items) items.push_back(item->clone());} 
        Inventory& operator=(const Inventory& other) {
            if (this != &other) {
                capacity = other.capacity;
                items.clear();
                for (auto& item : other.items) {
                    items.push_back(item->clone());
                }
            }
            return *this;
        }

        bool addItem(std::unique_ptr<Item> item); // Add an item to the inventory
        void listItems() const; // List all items in the inventory
        void useItem(int index, Player& player); // Use an item from the inventory
        size_t size() const { return items.size(); } 



        // Getters
        int getCapacity() const;
        int getItemCount() const {return static_cast<int>(items.size()); }
};
