#pragma once
#include "IDatabaseConnection.h"
#include <memory>
#include <mutex>

class PostgresConnection : public IDatabaseConnection{
private:
    PostgresConnection();
    ~PostgresConnection();
    std::unique_ptr<pqxx::connection> conn;
    static std::mutex mutex;

public:
    static PostgresConnection& getInstance();
    pqxx::connection* getConnection() override;
    PostgresConnection(const PostgresConnection&) = delete;
    PostgresConnection& operator=(const PostgresConnection&) = delete;
};