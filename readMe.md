# Inventory Management System (C++ + PostgreSQL)

A console-based **Inventory Management System** built using **C++** and **PostgreSQL** with the **libpqxx** library.  
The project demonstrates **Object-Oriented Programming (OOP)** principles, **database integration**, and **transaction management**.

---

## Features
- **OOP Structure**  
  - `Product` class → represents items with ID, name, quantity, and price  
  - `InventoryManager` class → encapsulates all CRUD operations  

- **CRUD Operations**
  - Add a product  
  - View all products  
  - Search products by name  
  - Update product quantity  
  - Delete product by ID  

- **Extra Features**
  - View low-stock products (below threshold)  
  - Export products to CSV file  
  - Calculate total inventory value  

- **Robustness**
  -  Uses **transactions** for all write operations  
  -  Uses **try/catch** for error handling  
  -  Prevents SQL injection with `txn.quote()`  

---

## Tech Stack
- **Language**: C++17  
- **Database**: PostgreSQL  
- **Library**: [libpqxx](https://github.com/jtv/libpqxx) (C++ client API for PostgreSQL)  

---

## Project Structure
InventoryManagementSystem/
│
├── src/
│ ├── main.cpp # Entry point (menu-driven CLI)
│ └── inventory.cpp # Implementation of InventoryManager & Product
│
├── include/
│ └── inventory.h # Class definitions for Product & InventoryManager
│
├── data/ # (Optional) export CSV files stored here
│
├── Makefile # For easy compilation (if added)
└── README.md # Project documentation


---

## Setup Instructions

### 1. Install Dependencies
Make sure PostgreSQL and libpqxx are installed. On macOS with Homebrew:
```bash
brew install postgresql libpqxx

### 2. Create Database & Table 
CREATE DATABASE inventory;

\c inventory;

CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    quantity INT NOT NULL,
    price NUMERIC(10,2) NOT NULL
);

### 3. Compile & Run

Using g++:

g++ -std=c++17 src/*.cpp -Iinclude -lpqxx -lpq -o inventory
./inventory

### 4.Usage

When you run the program, you’ll see a menu:

--- Inventory Management ---
1. Add Product
2. View Products
3. Search Product
4. Update Product Quantity
5. Delete Product
6. View Low Stock
7. Export to CSV
8. Calculate Total Value
9. Exit

## Technical Highlights

Demonstrates Object-Oriented Design in C++

Uses transactions (pqxx::work) for atomic INSERT/UPDATE/DELETE

Uses nontransaction (pqxx::nontransaction) for safe SELECT queries

Implements error handling via try/catch

Ensures SQL safety with txn.quote()

## Author
Sakshi Shakya





