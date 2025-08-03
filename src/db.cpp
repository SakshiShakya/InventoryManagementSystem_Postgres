#include "../include/db.h"
#include <iostream>

pqxx::connection* connectDB() {
    try {
        // Modify credentials as needed
        std::string connStr = "dbname=inventory_db user=postgres password=YourPassword host=localhost";
        pqxx::connection* C = new pqxx::connection(connStr);
        if (C->is_open()) {
            std::cout << "Connected to DB successfully.\n";
            return C;
        }
    } catch (const std::exception &e) {
        std::cerr << "DB connection error: " << e.what() << "\n";
    }
    return nullptr;
}

void closeDB(pqxx::connection* C) {
    if (C) {
        delete C;  // ✔ this automatically closes the connection
    }
}
