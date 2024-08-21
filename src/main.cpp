#include "server.h"
#include "database.h"

Database db;  // Global Database object

int main() {
    // Load the database from file
    db.loadFromFile("data/storage.txt");

    // Start the server
    Server server;
    server.start(5555);

    // Save the database to file before shutting down
    db.saveToFile("data/storage.txt");

    return 0;
}