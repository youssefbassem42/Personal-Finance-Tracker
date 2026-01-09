#include "infrastructure/repositories/PostgresBudgetRepository.h"
#include <pqxx/pqxx>

void PostgresBudgetRepository::addBudget(const Budget& budget) {
    pqxx::work work(*dbConn->getConnection());
    work.exec_params(
        "INSERT INTO budget (user_id, category, limit_amount, date) VALUES ($1, $2, $3, $4)",
        budget.getUserId(),
        budget.getCategory(),
        budget.getLimitAmount().value(),
        budget.getDate().toString()
    );
    work.commit();
}

void PostgresBudgetRepository::removeBudget(int id) {
    pqxx::work work(*dbConn->getConnection());
    work.exec_params("DELETE FROM budget WHERE id = $1", id);
    work.commit();
}

void PostgresBudgetRepository::updateBudget(const Budget& budget) {
    pqxx::work work(*dbConn->getConnection());
    work.exec_params(
        "UPDATE budget SET limit_amount = $1, date = $2 WHERE id = $3",
        budget.getLimitAmount().value(),
        budget.getDate().toString(),
        budget.getId()
    );
    work.commit();
}

std::optional<Budget> PostgresBudgetRepository::getBudget(int id) {
    pqxx::work work(*dbConn->getConnection());
    pqxx::result result = work.exec_params("SELECT * FROM budget WHERE id = $1", id);
    
    if (result.empty()) return std::nullopt;
    
    auto row = result[0];
    Money amount(row["limit_amount"].as<double>());
    Date date(row["date"].as<std::string>());
    
    return Budget(
        row["id"].as<int>(),
        row["user_id"].as<int>(),
        row["category"].as<std::string>(),
        amount,
        date
    );
}

std::vector<Budget> PostgresBudgetRepository::getAllBudgets(int userId) {
    pqxx::work work(*dbConn->getConnection());
    pqxx::result result = work.exec_params("SELECT * FROM budget WHERE user_id = $1", userId);
    
    std::vector<Budget> budgets;
    for (const auto& row : result) {
        Money amount(row["limit_amount"].as<double>());
        Date date(row["date"].as<std::string>());
        
        budgets.push_back(Budget(
            row["id"].as<int>(),
            row["user_id"].as<int>(),
            row["category"].as<std::string>(),
            amount,
            date
        ));
    }
    return budgets;
}

std::optional<Budget> PostgresBudgetRepository::getBudgetByCategory(int userId, const std::string& category) {
    pqxx::work work(*dbConn->getConnection());
    pqxx::result result = work.exec_params("SELECT * FROM budget WHERE user_id = $1 AND category = $2", userId, category);
    
    if (result.empty()) return std::nullopt;
    
    auto row = result[0];
    Money amount(row["limit_amount"].as<double>());
    Date date(row["date"].as<std::string>());
    
    return Budget(
        row["id"].as<int>(),
        row["user_id"].as<int>(),
        row["category"].as<std::string>(),
        amount,
        date
    );
}
