#include "../include/inventory.h"
#include <iostream>
#include <pqxx/pqxx>

using namespace std;

void addProduct(pqxx::connection* C) {
    string name;
    int quantity;
    double price;

    cout << "Product name: ";
    cin >> name;
    cout << "Quantity: ";
    cin >> quantity;
    cout << "Price: ";
    cin >> price;

    try {
        pqxx::work txn(*C);  // Start transaction
        txn.exec0("INSERT INTO products (name, quantity, price) VALUES (" +
                  txn.quote(name) + ", " + txn.quote(quantity) + ", " + txn.quote(price) + ")");
        txn.commit();  // Commit transaction
        cout << "Product added successfully.\n";
    } catch (const exception& e) {
        cerr << "Error adding product: " << e.what() << endl;
    }
}

void viewProducts(pqxx::connection* C) {
    try {
        pqxx::nontransaction txn(*C);
        auto res = txn.exec("SELECT * FROM products");

        cout << "ID | Name | Quantity | Price\n";
        for (auto row : res) {
            cout << row["id"].as<int>() << " | "
                 << row["name"].as<string>() << " | "
                 << row["quantity"].as<int>() << " | "
                 << row["price"].as<double>() << "\n";
        }
    } catch (const exception& e) {
        cerr << "Error viewing products: " << e.what() << endl;
    }
}

void searchProduct(pqxx::connection* C) {
    string name;
    cout << "Enter name to search: ";
    cin >> name;

    try {
        pqxx::nontransaction txn(*C);
        auto res = txn.exec("SELECT * FROM products WHERE name = " + txn.quote(name));

        if (res.empty()) {
            cout << "No product found.\n";
        } else {
            for (auto row : res) {
                cout << "Found: ID " << row["id"].as<int>()
                     << ", Quantity: " << row["quantity"].as<int>()
                     << ", Price: " << row["price"].as<double>() << "\n";
            }
        }
    } catch (const exception& e) {
        cerr << "Error searching product: " << e.what() << endl;
    }
}

void updateProduct(pqxx::connection* C) {
    int id, newQty;
    cout << "Enter product ID to update: ";
    cin >> id;
    cout << "Enter new quantity: ";
    cin >> newQty;

    try {
        pqxx::work txn(*C);  // Start transaction
        txn.exec0("UPDATE products SET quantity = " + txn.quote(newQty) +
                  " WHERE id = " + txn.quote(id));
        txn.commit();
        cout << "Product updated successfully.\n";
    } catch (const exception& e) {
        cerr << "Error updating product: " << e.what() << endl;
    }
}

void deleteProduct(pqxx::connection* C) {
    int id;
    cout << "Enter product ID to delete: ";
    cin >> id;

    try {
        pqxx::work txn(*C);  // Start transaction
        txn.exec0("DELETE FROM products WHERE id = " + txn.quote(id));
        txn.commit();
        cout << "Product deleted successfully.\n";
    } catch (const exception& e) {
        cerr << "Error deleting product: " << e.what() << endl;
    }
}
