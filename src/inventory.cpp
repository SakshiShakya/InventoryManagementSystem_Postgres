#include "../include/inventory.h"
#include <iostream>
#include <fstream>

using namespace std;

InventoryManager::InventoryManager(pqxx::connection* conn) : C(conn) {}

void InventoryManager::addProduct(const Product& p) {
    try {
        pqxx::work txn(*C);
        txn.exec0("INSERT INTO products (name, quantity, price) VALUES (" +
                  txn.quote(p.getName()) + ", " +
                  txn.quote(p.getQuantity()) + ", " +
                  txn.quote(p.getPrice()) + ")");
        txn.commit();
        cout << "✅ Product added successfully.\n";
    } catch (const exception& e) {
        cerr << "❌ Error adding product: " << e.what() << endl;
    }
}

void InventoryManager::viewProducts() {
    try {
        pqxx::nontransaction txn(*C);
        auto res = txn.exec("SELECT * FROM products");

        cout << "\nID | Name | Quantity | Price\n";
        cout << "----------------------------------\n";
        for (auto row : res) {
            cout << row["id"].as<int>() << " | "
                 << row["name"].as<string>() << " | "
                 << row["quantity"].as<int>() << " | "
                 << row["price"].as<double>() << "\n";
        }
    } catch (const exception& e) {
        cerr << "❌ Error viewing products: " << e.what() << endl;
    }
}

void InventoryManager::searchProduct(const string& name) {
    try {
        pqxx::nontransaction txn(*C);
        auto res = txn.exec("SELECT * FROM products WHERE name = " + txn.quote(name));

        if (res.empty()) {
            cout << "⚠️ No product found.\n";
        } else {
            for (auto row : res) {
                cout << "Found: ID " << row["id"].as<int>()
                     << ", Quantity: " << row["quantity"].as<int>()
                     << ", Price: " << row["price"].as<double>() << "\n";
            }
        }
    } catch (const exception& e) {
        cerr << "❌ Error searching product: " << e.what() << endl;
    }
}

void InventoryManager::updateProductQuantity(int id, int newQty) {
    try {
        pqxx::work txn(*C);
        txn.exec0("UPDATE products SET quantity = " + txn.quote(newQty) +
                  " WHERE id = " + txn.quote(id));
        txn.commit();
        cout << "✅ Product updated successfully.\n";
    } catch (const exception& e) {
        cerr << "❌ Error updating product: " << e.what() << endl;
    }
}

void InventoryManager::deleteProduct(int id) {
    try {
        pqxx::work txn(*C);
        txn.exec0("DELETE FROM products WHERE id = " + txn.quote(id));
        txn.commit();
        cout << "✅ Product deleted successfully.\n";
    } catch (const exception& e) {
        cerr << "❌ Error deleting product: " << e.what() << endl;
    }
}

void InventoryManager::viewLowStock(int threshold) {
    try {
        pqxx::nontransaction txn(*C);
        auto res = txn.exec("SELECT * FROM products WHERE quantity < " + txn.quote(threshold));

        if (res.empty()) {
            cout << "✅ All products are sufficiently stocked.\n";
        } else {
            cout << "\n⚠️ Low Stock Products:\n";
            for (auto row : res) {
                cout << row["id"].as<int>() << " | "
                     << row["name"].as<string>() << " | "
                     << row["quantity"].as<int>() << " | "
                     << row["price"].as<double>() << "\n";
            }
        }
    } catch (const exception& e) {
        cerr << "❌ Error fetching low stock products: " << e.what() << endl;
    }
}

void InventoryManager::exportToCSV(const string& filename) {
    try {
        pqxx::nontransaction txn(*C);
        auto res = txn.exec("SELECT * FROM products");

        ofstream file(filename);
        file << "ID,Name,Quantity,Price\n";
        for (auto row : res) {
            file << row["id"].as<int>() << ","
                 << row["name"].as<string>() << ","
                 << row["quantity"].as<int>() << ","
                 << row["price"].as<double>() << "\n";
        }
        file.close();
        cout << "✅ Exported inventory to " << filename << "\n";
    } catch (const exception& e) {
        cerr << "❌ Error exporting to CSV: " << e.what() << endl;
    }
}

void InventoryManager::calculateTotalValue() {
    try {
        pqxx::nontransaction txn(*C);
        auto res = txn.exec("SELECT SUM(quantity * price) as total_value FROM products");

        if (!res.empty()) {
            cout << "💰 Total Inventory Value: " << res[0]["total_value"].as<double>(0.0) << "\n";
        }
    } catch (const exception& e) {
        cerr << "❌ Error calculating inventory value: " << e.what() << endl;
    }
}
