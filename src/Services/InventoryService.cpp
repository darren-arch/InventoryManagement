#include "InventoryService.h"

#include "Item.h"
#include <iostream>

bool InventoryService::determineChoice(){
    switch(choice) {
        case 1:
            editItem();
            return true;
        case 2:
            addItem();
            return true;
        case 3:
            deleteItem();
            return true;
        case 4:
            ui.closing();
            db.close();
            return false;
        default: 
            cinFail();
            return true;
    }
}

int InventoryService::mainMenu() {
    try
    {
        items = db.viewAll();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        choice = ui.mainMenu(items);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return choice;
}

void InventoryService::addItem() {
    if(ui.addItem(item)) {
        db.addItem(item);
        ui.askContinue("Item Added!");
    } else {
        cinFail();
    }
}

void InventoryService::editItem() {
    if(ui.editItem(id, item)) {
        db.editItem(id, item);
        ui.askContinue("Item Updated!");
    } else {
        cinFail();
    }
}


void InventoryService::deleteItem() {
    if(ui.deleteItem(id)) {
        db.deleteItem(id);
        ui.askContinue("Item Deleted!");
    } else {
        cinFail();
    }
}

void InventoryService::cinFail() {
    ui.incorrectValue();
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    choice = 1;
    ui.askContinue();
}