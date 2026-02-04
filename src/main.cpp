#include <iostream>
#include "InventoryService.h"

int main() {

    std::cout << "Inventory App\n";

    InventoryService service;
    int running = true;

    while(running) {
        service.mainMenu();
        running = service.determineChoice();
    }
    
    return 0;
}
