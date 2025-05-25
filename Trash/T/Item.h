#pragma once
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Player;
class Item {
protected:
    string name;
    char symbol;
    
public:
    Item(const string& n): name(n){}
    virtual ~Item() = default;
    const string& getName() const { return name; }
    virtual void use(Player& player) = 0;
    virtual unique_ptr<Item> clone() const = 0;
    
};
