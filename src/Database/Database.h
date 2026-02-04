#ifndef DATABASE_H
#define DATABASE_H 

extern "C" {
#include <sqlite3.h>
}
#include "Item.h"
#include <vector>
#include <string>

class Database {
    private:
        sqlite3* db;
        int openClose();
        int open();
        std::string charToString(const unsigned char* nameText);
    public:
        Database();
        void close();
        void addItem(Item item);
        std::vector<Item> viewAll();
        Item viewItem(int id);
        void editItem(int id, Item& item);
        void deleteItem(int id);
};
#endif