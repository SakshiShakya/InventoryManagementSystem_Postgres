#ifndef INVENTORY_H
#define INVENTORY_H

#include <pqxx/pqxx>
void addProduct(pqxx::connection*);
void viewProducts(pqxx::connection*);
void searchProduct(pqxx::connection*);
void updateProduct(pqxx::connection*);
void deleteProduct(pqxx::connection*);
#endif
