#ifndef INVENTORYSERVICE_H
#define INVENTORYSERVICE_H

#include "Item.h"
#include "Database.h"
#include "ConsoleUI.h"
#include <vector>

class InventoryService {
    private:
        void addItem();
        void deleteItem();
        void editItem();
        void cinFail();
        
        int choice;
        int id;
        
        Database db;
        ConsoleUI ui;
        Item item;
        std::vector<Item> items;

    public:
        int mainMenu();
        bool determineChoice();

};

#endif