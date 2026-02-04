#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
    public:
        std::string name;
        int quantity;
        float value;
        Item() {};
        Item(std::string name, int quantity, float value) : name(name), quantity(quantity), value(value) {};
};
#endif