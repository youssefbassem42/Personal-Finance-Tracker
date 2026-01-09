#include "PostgresConnection.h"
#include "EnvLoader.h"
#include <stdexcept>


std::mutex PostgresConnection::mutex;

PostgresConnection::PostgresConnection() {
    std::string connStr = EnvLoader::get("POSTGRES_CONN");

    if (connStr.empty()) {
        throw std::runtime_error("POSTGRES_CONN not found in environment variables");
    }

    conn = std::make_unique<pqxx::connection>(connStr);
    if (!conn->is_open()) {
        throw std::runtime_error("Failed to connect to database");
    }
}

PostgresConnection::~PostgresConnection() {
    if (conn && conn->is_open()) {
        conn->close();
    }
}

PostgresConnection& PostgresConnection::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    static PostgresConnection instance;
    return instance;
}

pqxx::connection* PostgresConnection::getConnection() {
    return conn.get();
}