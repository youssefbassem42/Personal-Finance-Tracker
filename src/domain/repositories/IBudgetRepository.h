#pragma once
#include <vector>
#include <memory>
#include <optional>
#include "domain/entities/Budget.h"


class IBudgetRepository {
public:
    virtual ~IBudgetRepository() = default;
    virtual void addBudget(const Budget& budget) = 0;
    virtual void removeBudget(int id) = 0;
    virtual void updateBudget(const Budget& budget) = 0;
    virtual std::optional<Budget> getBudget(int id) = 0;
    virtual std::vector<Budget> getAllBudgets(int userId) = 0;
    virtual std::optional<Budget> getBudgetByCategory(int userId, const std::string& category) = 0;
};