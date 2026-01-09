#pragma once
#include <vector>
#include <memory>
#include "domain/entities/Budget.h"
#include "domain/entities/Expense.h"
#include "domain/repositories/IBudgetRepository.h"

class BudgetService {
private:
    std::shared_ptr<IBudgetRepository> budgetRepo;
    int currentUserId;

public:
    BudgetService(std::shared_ptr<IBudgetRepository> repo, int userId) 
        : budgetRepo(repo), currentUserId(userId) {}

    void setBudget(const Budget& budget);
    bool isBudgetExceeded(const std::string& category, const std::vector<std::shared_ptr<Expense>>& expenses) const;
    std::vector<Budget> getAllBudgets() const;
};
