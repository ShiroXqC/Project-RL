#pragma once
#include <iostream>
#include <string>

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
    
    virtual ~Item() {} // Virtual destructor for proper cleanup
    
    // Getters
    char getSymbol() const { return symbol; }
    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isConsumable() const { return isConsumedOnUse; }
    
    // For rendering
    virtual char getDisplayChar() const { return symbol; }
};
