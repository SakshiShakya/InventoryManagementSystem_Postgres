#include "../include/inventory.h"
#include <iostream>

void addProduct(pqxx::connection* C) {
    std::string name;
    int quantity;
    double price;

    std::cout << "Product name: ";
    std::cin >> name;
    std::cout << "Quantity: ";
    std::cin >> quantity;
    std::cout << "Price: ";
    std::cin >> price;

    pqxx::work txn(*C);
    txn.exec0("INSERT INTO products (name, quantity, price) VALUES (" +
              txn.quote(name) + ", " + txn.quote(quantity) + ", " + txn.quote(price) + ")");
    txn.commit();
    std::cout << "Product added.\n";
}

void viewProducts(pqxx::connection* C) {
    pqxx::nontransaction txn(*C);
    auto res = txn.exec("SELECT * FROM products");
    std::cout << "ID | Name | Quantity | Price\n";
    for (auto row : res) {
        std::cout << row["id"].as<int>() << " | "
                  << row["name"].as<std::string>() << " | "
                  << row["quantity"].as<int>() << " | "
                  << row["price"].as<double>() << "\n";
    }
}

void searchProduct(pqxx::connection* C) {
    std::string name;
    std::cout << "Enter name to search: ";
    std::cin >> name;

    pqxx::nontransaction txn(*C);
    auto res = txn.exec("SELECT * FROM products WHERE name = " + txn.quote(name));
    if (res.empty()) {
        std::cout << "No product found.\n";
    } else {
        for (auto row : res) {
            std::cout << "Found: ID " << row["id"].as<int>()
                      << ", Quantity: " << row["quantity"].as<int>()
                      << ", Price: " << row["price"].as<double>() << "\n";
        }
    }
}

void updateProduct(pqxx::connection* C) {
    int id, newQty;
    std::cout << "Enter product ID to update: ";
    std::cin >> id;
    std::cout << "Enter new quantity: ";
    std::cin >> newQty;

    pqxx::work txn(*C);
    txn.exec0("UPDATE products SET quantity = " + txn.quote(newQty) +
              " WHERE id = " + txn.quote(id));
    txn.commit();
    std::cout << "Product updated.\n";
}

void deleteProduct(pqxx::connection* C) {
    int id;
    std::cout << "Enter product ID to delete: ";
    std::cin >> id;

    pqxx::work txn(*C);
    txn.exec0("DELETE FROM products WHERE id = " + txn.quote(id));
    txn.commit();
    std::cout << "Product deleted.\n";
}
