#pragma once
#include "domain/repositories/IBudgetRepository.h"
#include "infrastructure/database/PostgresConnection.h"

class PostgresBudgetRepository : public IBudgetRepository {
private:
    PostgresConnection* dbConn;
public:
    PostgresBudgetRepository() : dbConn(&PostgresConnection::getInstance()) {}
    void addBudget(const Budget& budget) override;
    void removeBudget(int id) override;
    void updateBudget(const Budget& budget) override;
    std::optional<Budget> getBudget(int id) override;
    std::vector<Budget> getAllBudgets(int userId) override;
    std::optional<Budget> getBudgetByCategory(int userId, const std::string& category) override;
};
