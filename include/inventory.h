#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <pqxx/pqxx>
#include <vector>

class Product {
private:
    int id;
    std::string name;
    int quantity;
    double price;

public:
    Product(std::string n, int q, double p, int i = -1)
        : id(i), name(n), quantity(q), price(p) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }
};

class InventoryManager {
private:
    pqxx::connection* C;

public:
    InventoryManager(pqxx::connection* conn);
    void addProduct(const Product& p);
    void viewProducts();
    void searchProduct(const std::string& name);
    void updateProductQuantity(int id, int newQty);
    void deleteProduct(int id);

    // Extra features
    void viewLowStock(int threshold);
    void exportToCSV(const std::string& filename);
    void calculateTotalValue();
};

#endif
