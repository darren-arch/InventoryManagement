#include "ConsoleUI.h"
#include <iostream>
#include <string>
#include "Database.h"
#include <vector>
#include "Item.h"


void ConsoleUI::viewInventory(std::vector<Item> items) {
    std::cout << "Inventory:\n";

    Item item;

    for (size_t i = 0; i < items.size(); i++) {
        item = items[i];
        std::cout << i+1 << ".";
        itemInfo(item.name, item.quantity, item.value);
    }
    return;
}

void ConsoleUI::itemInfo(std::string name, int quantity, float price){
    std::cout << "Item: " << name << " -- Amount: " << quantity << " -- Price: $" << price << "\n";
    return;
}

void ConsoleUI::askContinue(std::string message) {
    if(message == "false") {
        std::cout << "Press enter to continue:";
        std::cin.get();
    } else {
        std::cout << message << "\nPress enter to continue:";
        std::cin.get();
        std::cin.get();
    }
}

int ConsoleUI::mainMenu(std::vector<Item> items) {
    viewInventory(items);
    std::cout << "Chose an option:\n1. Edit Item\n2. Add Item\n3. Delete Item\n4. Close App\nInput: ";
        
    int choice;
    std::cin >> choice;
    
    return choice;
}

bool ConsoleUI::editItem(int& id, Item& item) {
    
    std::cout << "Which item would you like to edit: ";
    std::cin >> id;
    if(std::cin.fail()) {return false;}
    std::cout << "What would you like it's name to be: ";
    std::cin >> item.name;
    if(std::cin.fail()) {return false;}
    std::cout << "How many of the item do you have: ";
    std::cin >> item.quantity;
    if(std::cin.fail()) {return false;}
    std::cout << "What is the price of the item: $";
    std::cin >> item.value;
    if(std::cin.fail()) {return false;}
    return true;
}

bool ConsoleUI::addItem(Item& item) {

    std::cout << "What would you like it's name to be: ";
    std::cin >> item.name;
    if(std::cin.fail()) {return false;}
    std::cout << "How many of the item do you have: ";
    std::cin >> item.quantity;
    if(std::cin.fail()) {return false;}
    std::cout << "What is the price of the item: $";
    std::cin >> item.value;
    if(std::cin.fail()) {return false;}
    return true;
}

bool ConsoleUI::deleteItem(int& id) {
    std::cout << "Which item would you like to delete: ";
    std::cin >> id;
    if(std::cin.fail()) {return false;}
    return true;
}

void ConsoleUI::closing() {
    std::cout << "Closing App :)\n";
}

void ConsoleUI::incorrectValue() {
    std::cout << "Not an option\n";
}