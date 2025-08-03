#include "../include/db.h"
#include "../include/inventory.h"
#include <iostream>

int main() {
    pqxx::connection* db = connectDB();
    if (!db) return 1;

    int choice;
    do {
        std::cout << "\n--- Inventory Menu ---\n";
        std::cout << "1. Add Product\n";
        std::cout << "2. View All Products\n";
        std::cout << "3. Search Product\n";
        std::cout << "4. Update Quantity\n";
        std::cout << "5. Delete Product\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: addProduct(db); break;
            case 2: viewProducts(db); break;
            case 3: searchProduct(db); break;
            case 4: updateProduct(db); break;
            case 5: deleteProduct(db); break;
        }
    } while (choice != 0);

    closeDB(db);
    return 0;
}
