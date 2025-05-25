#pragma once
#include <iostream>
#include <string>
#include <memory> // For unique_ptr
using namespace std;

class Player;
class Item {
protected:
    string name;
    bool isConsumedOnUse;
    char symbol;
    
public:
    Item(const string& n, bool c, char s)
        : name(n), isConsumedOnUse(c), symbol(s) {}
    virtual ~Item() = default;
    const string& getName() const { return name; }
    bool isConsumable() const { return isConsumedOnUse; }
    virtual void use(Player& player) = 0;
    virtual unique_ptr<Item> clone() const = 0;
    virtual char getDisplayChar() const = 0;
    
};
