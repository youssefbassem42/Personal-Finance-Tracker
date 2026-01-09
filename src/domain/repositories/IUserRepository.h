#include <optional>
#include <string>
#include "domain/entities/User.h"


class IUserRepository {
public:
    virtual ~IUserRepository() = default;
    virtual void addUser(const std::string& username, const std::string& email) const = 0;
    virtual void removeUser(const int user_id) const = 0;
    virtual void updateUser(const int user_id, const std::string& username, const std::string& email) const = 0;
    virtual std::optional<User> getUser(const int user_id) const = 0;
    virtual std::optional<User> getUserById(const int user_id) const = 0;
    virtual std::optional<User> getUserByUsername(const std::string& username) const = 0;
};