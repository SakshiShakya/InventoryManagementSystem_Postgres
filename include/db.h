#ifndef DB_H
#define DB_H

#include <pqxx/pqxx>
pqxx::connection* connectDB();
void closeDB(pqxx::connection*);
#endif