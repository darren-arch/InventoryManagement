#include "Database.h"
#include "Item.h"
extern "C" {
#include <sqlite3.h>
}
#include <iostream>
#include <string>
#include <vector>

Database::Database() {
    open();
}

std::string Database::charToString(const unsigned char* nameText) {
    return std::string(reinterpret_cast<const char*>(nameText));
}

int Database::open() {    
    int rc = sqlite3_open("inventory.db", &db);  // database file
    if (rc) {
        return rc;
    }

    const char* createTableSQL =
    "CREATE TABLE IF NOT EXISTS items ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "name TEXT,"
    "quantity INTEGER,"
    "value REAL);";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }

    return 1;
}

void Database::close() {
    sqlite3_close(db);
}

void Database::addItem(Item item) {
    const char* sql = "INSERT INTO items (name, quantity, value) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, item.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, item.quantity);
    sqlite3_bind_double(stmt, 3, item.value);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

std::vector<Item> Database::viewAll() {
    const char* sql = "SELECT name, quantity, value FROM items;";
    sqlite3_stmt* stmt = nullptr;
    std::vector<Item> items;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return items;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Item item;
        const unsigned char* nameText = sqlite3_column_text(stmt, 0); // column 1: name
        item.quantity = sqlite3_column_int(stmt, 1);    // column 2: quantity
        item.value = sqlite3_column_double(stmt, 2); // column 3: value

        item.name = std::string(reinterpret_cast<const char*>(nameText));

        items.push_back(item);

    }
    sqlite3_finalize(stmt);
    return items;
}

Item Database::viewItem(int id) {
    const char* sql = "SELECT name, quantity, value FROM items WHERE (id = ?);";
    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    
    Item item;
    sqlite3_step(stmt);
    item.name = charToString(sqlite3_column_text(stmt, 0));
    item.quantity = sqlite3_column_int(stmt, 1);
    item.value = sqlite3_column_double(stmt, 2);

    sqlite3_finalize(stmt);
    return item;
}

void Database::editItem(int id, Item& item) {
    const char* sql = "UPDATE items SET name = ?, quantity = ?, value = ? WHERE (id = ?);";
    sqlite3_stmt* stmt = nullptr;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, item.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, item.quantity);
    sqlite3_bind_double(stmt, 3, item.value);
    sqlite3_bind_int(stmt, 4, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void Database::deleteItem(int id) {
    const char* sql = "DELETE FROM items WHERE (id = ?);";
    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}