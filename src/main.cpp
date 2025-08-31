#include "../include/inventory.h"
#include <iostream>

using namespace std;

int main() {
    try {
        pqxx::connection C("dbname=inventory user=postgres password=yourpassword host=localhost port=5432");

        if (!C.is_open()) {
            cerr << "❌ Cannot connect to database\n";
            return 1;
        }

        InventoryManager manager(&C);

        int choice;
        while (true) {
            cout << "\n--- Inventory Management ---\n";
            cout << "1. Add Product\n2. View Products\n3. Search Product\n";
            cout << "4. Update Product Quantity\n5. Delete Product\n";
            cout << "6. View Low Stock\n7. Export to CSV\n8. Calculate Total Value\n";
            cout << "9. Exit\nChoose: ";
            cin >> choice;

            if (choice == 1) {
                string name; int qty; double price;
                cout << "Enter name qty price: ";
                cin >> name >> qty >> price;
                Product p(name, qty, price);
                manager.addProduct(p);
            } else if (choice == 2) manager.viewProducts();
            else if (choice == 3) {
                string name;
                cout << "Enter name: ";
                cin >> name;
                manager.searchProduct(name);
            } else if (choice == 4) {
                int id, qty;
                cout << "Enter ID and new qty: ";
                cin >> id >> qty;
                manager.updateProductQuantity(id, qty);
            } else if (choice == 5) {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                manager.deleteProduct(id);
            } else if (choice == 6) {
                int th;
                cout << "Enter stock threshold: ";
                cin >> th;
                manager.viewLowStock(th);
            } else if (choice == 7) manager.exportToCSV("inventory.csv");
            else if (choice == 8) manager.calculateTotalValue();
            else if (choice == 9) break;
            else cout << "Invalid choice.\n";
        }

    } catch (const exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
