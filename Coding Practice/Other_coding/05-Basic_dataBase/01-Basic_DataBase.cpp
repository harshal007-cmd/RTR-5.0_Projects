#include <iostream>
#include <sqlite3.h>
#pragma comment(lib, "sqlite3.lib")

int main() {
    sqlite3* db;
    char* errorMessage = nullptr;

    // Step 1: Open or create a database
    int result = sqlite3_open("example.db", &db);
    if (result != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return result;
    }

    // Step 2: Create a table
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
    result = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "Error creating table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return result;
    }

    // Step 3: Insert data into the table
    const char* insertDataSQL = "INSERT INTO users (name, age) VALUES ('John Doe', 25);";
    result = sqlite3_exec(db, insertDataSQL, nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "Error inserting data: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return result;
    }

    // Step 4: Query data from the table
    const char* querySQL = "SELECT * FROM users;";
    result = sqlite3_exec(db, querySQL, [](void* data, int columns, char** row, char** columnNames) -> int {
        for (int i = 0; i < columns; ++i) {
            std::cout << columnNames[i] << ": " << (row[i] ? row[i] : "NULL") << "\t";
        }
        std::cout << std::endl;
        return SQLITE_OK;
        }, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Error querying data: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return result;
    }

    // Step 5: Close the database
    sqlite3_close(db);

    return 0;
}
