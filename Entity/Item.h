#include <iostream>
#include <string>

class item
{ 
    protected:
    std::string name;
    int x, y;
    bool isConsumedOnUse;
    char symbol;
    public:
    //Constructor overload
    item(std::string name, int x, int y, bool isConsumedOnUse)
    {
      
        this->name=name;
        this->x=x;
        this->y=y;
        this->isConsumedOnUse=isConsumedOnUse;
        this->symbol='?';   // Default symbol for items
    }
    std::string getName() const;
};
