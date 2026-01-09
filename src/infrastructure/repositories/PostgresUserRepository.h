#pragma once
#include <optional>
#include "domain/repositories/IUserRepository.h"
#include "domain/entities/User.h"
#include "infrastructure/database/PostgresConnection.h"

class PostgresUserRepository : public IUserRepository {
private:
    PostgresConnection* dbConn;
public:
    PostgresUserRepository() : dbConn(&PostgresConnection::getInstance()) {}
    ~PostgresUserRepository() = default;
    void addUser(const std::string& username, const std::string& email) const override;
    void removeUser(const int user_id) const override;
    void updateUser(const int user_id, const std::string& username, const std::string& email) const override;
    std::optional<User> getUser(const int user_id) const override;
    std::optional<User> getUserById(const int user_id) const override;
    std::optional<User> getUserByUsername(const std::string& username) const override;
};