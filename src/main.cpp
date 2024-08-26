#include "../include/server.h"
#include "../include/database.h"
#include <iostream>

Database db;  // Global Database object

int main() {
    // Load the database from the file in the data folder
    if (!db.loadFromFile("data/storage.txt")) {
        std::cerr << "Failed to load data from storage.txt" << std::endl;
    }

    // Start the server
    Server server;
    server.start(5556);

    // Save the database to the file in the data folder before shutting down
    if (!db.saveToFile("data/storage.txt")) {
        std::cerr << "Failed to save data to storage.txt" << std::endl;
    }

    return 0;
}
