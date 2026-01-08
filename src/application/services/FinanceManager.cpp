#include "FinanceManager.h"

void FinanceManager::addIncome(const Income& income) {
    incomes.push_back(income);
}

const std::vector<std::shared_ptr<Income>>& FinanceManager::getAllIncomes() const {
    return incomes;
}

bool FinanceManager::updateIncome(int id, const Money& newAmount) {
    for (auto& income : incomes) {
        if (income->getId() == id) {
            income->setAmount(newAmount);
            return true;
        }
    }
    return false;
}

bool FinanceManager::deleteIncome(int id) {
    for (auto it = incomes.begin(); it != incomes.end(); ++it) {
        if ((*it)->getId() == id) {
            incomes.erase(it);
            return true;
        }
    }
    return false;
}

void FinanceManager::addExpense(const Expense& expense) {
    expenses.push_back(expense);
}

const std::vector<std::shared_ptr<Expense>>& FinanceManager::getAllExpenses() const {
    return expenses;
}

bool FinanceManager::updateExpense(int id, const Money& newAmount) {
    for (auto& expense : expenses) {
        if (expense->getId() == id) {
            expense->setAmount(newAmount);
            return true;
        }
    }
    return false;
}

bool FinanceManager::deleteExpense(int id) {
    for (auto it = expenses.begin(); it != expenses.end(); ++it) {
        if ((*it)->getId() == id) {
            expenses.erase(it);
            return true;
        }
    }
    return false;
}
