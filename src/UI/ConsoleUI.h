#ifndef CONSOLEUI_H
#define CONSOLEUI_H 

#include <string>
#include "Database.h"
#include <vector>

class ConsoleUI {
    private: 
        void viewInventory(std::vector<Item> items);
        void itemInfo(std::string name, int quantity, float price);
    public:
        int mainMenu(std::vector<Item> items);
        bool determineChoice(int choice);
        bool editItem(int& id, Item& item);
        bool addItem(Item& item);
        bool deleteItem(int& id);
        void askContinue(std::string message = "false");
        void closing();
        void incorrectValue();
};
#endif