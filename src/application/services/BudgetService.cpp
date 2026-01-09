#include "BudgetService.h"

#include "BudgetService.h"

void BudgetService::setBudget(const Budget& budget) {
    auto existing = budgetRepo->getBudgetByCategory(currentUserId, budget.getCategory());
    if (existing) {
        try {
             budgetRepo->addBudget(budget);
        } catch (...) {
            budgetRepo->updateBudget(budget);
        }
    } else {
        budgetRepo->addBudget(budget);
    }
}

bool BudgetService::isBudgetExceeded(const std::string& category, const std::vector<std::shared_ptr<Expense>>& expenses) const {
    auto budget = budgetRepo->getBudgetByCategory(currentUserId, category);
    if (!budget) {
        return false;
    }

    Money totalExpenses(0);
    for (const auto& expense : expenses) {
        if (expense->getCategory() == category) {
            totalExpenses += expense->getAmount();
        }
    }
    return totalExpenses > budget->getLimitAmount();
}

std::vector<Budget> BudgetService::getAllBudgets() const {
    return budgetRepo->getAllBudgets(currentUserId);
}
