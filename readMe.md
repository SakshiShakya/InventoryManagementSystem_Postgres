# Inventory Management System (C++ + PostgreSQL)

A terminal-based inventory management system built in C++ using the PostgreSQL database for data persistence. This project demonstrates database integration, modular system design, and basic inventory operations via CLI.

---

## Features

- Connects to PostgreSQL using the `libpqxx` C++ library
- Add new products with name, quantity, and price
- View all existing products
- Update product details
- Delete products from the database
- Fully persistent using PostgreSQL

---

## Tech Stack

| Component      | Tool/Library                      |
|----------------|-----------------------------------|
| Language       | C++                               |
| Database       | PostgreSQL                        |
| DB Interface   | `libpqxx` (PostgreSQL C++ client) |
| Build Tool     | `clang++` or `g++`                |
| OS             | macOS (Apple Silicon tested)      |

---

## Project Structure

InventoryManagementSystem_Postgres/
├── src/ # Source code files
│ ├── main.cpp # Main menu logic
│ ├── db.cpp # DB connection and SQL execution
│ └── inventory.cpp # Inventory operations (add/view/update/delete)
├── include/ # Header files
│ ├── db.h
│ └── inventory.h
├── inventory_postgres # Output binary (after compilation)
└── README.md # You're reading this!


---

## Setup Instructions

### 1. Prerequisites

Install PostgreSQL and libpqxx via Homebrew:

```bash
brew install postgresql libpq libpqxx

Ensure the following paths are used when compiling (especially for Apple Silicon):

libpq: /opt/homebrew/opt/libpq

libpqxx: /opt/homebrew/Cellar/libpqxx/<version>

### 2. Create the PostgreSQL database 

CREATE DATABASE inventory_db;
\c inventory_db

CREATE TABLE products (
  id SERIAL PRIMARY KEY,
  name TEXT NOT NULL,
  quantity INTEGER NOT NULL,
  price REAL NOT NULL
);

### 3. Compile the project

clang++ -std=c++17 \
  -Iinclude \
  -I/opt/homebrew/Cellar/libpqxx/7.10.1/include \
  -I/opt/homebrew/opt/libpq/include \
  -L/opt/homebrew/Cellar/libpqxx/7.10.1/lib \
  -L/opt/homebrew/opt/libpq/lib \
  -lpqxx -lpq \
  src/*.cpp \
  -o inventory_postgres

### 4. Run the Program 

./inventory_postgres

Author
Sakshi Shakya
C++ & Web Developer | Interested in DB systems, DL & software design




