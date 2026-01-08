#include "BudgetService.h"

void BudgetService::setBudget(const Budget& budget) {
    budgets.push_back(budget);
}

bool BudgetService::isBudgetExceeded(const std::string& category, const std::vector<std::shared_ptr<Expense>>& expenses) const {
    for (const auto& budget : budgets) {
        if (budget.getCategory() == category) {
            Money totalExpenses = Money(0);
            for (const auto& expense : expenses) {
                if (expense->getCategory() == category) {
                    totalExpenses += expense->getAmount();
                }
            }
            return totalExpenses > budget.getLimit();
        }
    }
    return false;
}
