#pragma once
#include <iostream>
#include <string>
#include <memory> // For std::unique_ptr

class Player;
class Item {
protected:
    std::string name;
    int x, y;
    bool isConsumedOnUse;
    char symbol;
    
public:
    //Default constructor
    Item () {}

    //Parameterized constructor 
    Item(std::string name, int x, int y, bool isConsumed, char symbol)
        : name(name), x(x), y(y), isConsumedOnUse(isConsumed), symbol(symbol) {}
    
    // Getters
    char getSymbol() const { return symbol; }
    const std::string& getName() const { return name; } // Changed to return by const reference

    int getX() const { return x; }
    int getY() const { return y; }
    bool isConsumable() const { return isConsumedOnUse; }
static Item* createRandomItem(int x, int y);
    // For rendering
    virtual ~Item() = default;
    virtual std::unique_ptr<Item> clone() const = 0;
    virtual void use(Player& player) = 0;
    virtual char getDisplayChar() const = 0;
    
};
