#pragma once 
#include <map>
#include <vector>
#include <memory> // For unique_ptr dynamic memory management 
#include "Item.h"
using namespace std;

class Player; 
class Inventory{
    protected:
        vector<unique_ptr<Item>> items;
        int capacity;
    public:
        Inventory(int cap = 10) : capacity(10) {}
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

        bool addItem(unique_ptr<Item> item); // Add an item to the inventory
        void listItems() const; // List all items in the inventory
        void useItem(int index, Player& player); // Use items from the inventory
        size_t size() const { return items.size(); } 

        int getItemCount() const {return static_cast<int>(items.size()); }
};
