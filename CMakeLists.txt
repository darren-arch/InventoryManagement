cmake_minimum_required(VERSION 3.16)

project(InventoryApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    src/UI
    src/Database
    src/Models
    src/Services
)

# Add executable
add_executable(inventory_app
    src/main.cpp
    src/UI/ConsoleUI.cpp
    src/Database/Database.cpp
    src/Services/InventoryService.cpp
)

# Find SQLite3 using CMake module
find_package(SQLite3 REQUIRED)

# Link SQLite3 to your executable
target_link_libraries(inventory_app PRIVATE SQLite::SQLite3)