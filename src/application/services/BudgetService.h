#pragma once
#include <vector>
#include "domain/entities/Budget.h"
#include "domain/entities/Expense.h"


class BudgetService {
private:
    std::vector<Budget> budgets;

public:
    void setBudget(const Budget& budget);

    bool isBudgetExceeded(const std::string& category, const std::vector<std::shared_ptr<Expense>>& expenses) const;
}
