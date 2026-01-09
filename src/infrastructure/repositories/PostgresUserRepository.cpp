#include "infrastructure/repositories/PostgresUserRepository.h"
#include "infrastructure/database/PostgresConnection.h"
#include <pqxx/pqxx>



void PostgresUserRepository::addUser(const std::string& username, const std::string& email) const {
    pqxx::work work(*dbConn->getConnection());
    work.exec("INSERT INTO users (name, email) VALUES ('" + username + "', '" + email + "')");
    work.commit();
}
void PostgresUserRepository::removeUser(const int user_id) const {
    pqxx::work work(*dbConn->getConnection());
    work.exec("DELETE FROM users WHERE user_id = " + std::to_string(user_id));
    work.commit();
}
void PostgresUserRepository::updateUser(const int user_id, const std::string& username, const std::string& email) const {
    pqxx::work work(*dbConn->getConnection());
    work.exec("UPDATE users SET name = '" + username + "', email = '" + email + "' WHERE user_id = " + std::to_string(user_id));
    work.commit();
}
std::optional<User> PostgresUserRepository::getUser(const int user_id) const {
    pqxx::work work(*dbConn->getConnection());
    pqxx::result result = work.exec("SELECT * FROM users WHERE user_id = " + std::to_string(user_id));
    work.commit();
    if (result.size() == 0){
        return std::nullopt;
    }
    return User(result[0]["user_id"].as<int>(), result[0]["name"].as<std::string>(), result[0]["email"].as<std::string>());
}
std::optional<User> PostgresUserRepository::getUserById(const int user_id) const {
    pqxx::work work(*dbConn->getConnection());
    pqxx::result result = work.exec("SELECT * FROM users WHERE user_id = " + std::to_string(user_id));
    work.commit();
    if (result.size() == 0){
        return std::nullopt;
    }
    return User(result[0]["user_id"].as<int>(), result[0]["name"].as<std::string>(), result[0]["email"].as<std::string>());
}
std::optional<User> PostgresUserRepository::getUserByUsername(const std::string& username) const {
    pqxx::work work(*dbConn->getConnection());
    pqxx::result result = work.exec("SELECT * FROM users WHERE name = '" + username + "'");
    work.commit();
    if (result.size() == 0){
        return std::nullopt;
    }
    return User(result[0]["user_id"].as<int>(), result[0]["name"].as<std::string>(), result[0]["email"].as<std::string>());
}

