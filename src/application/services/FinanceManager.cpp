#include "FinanceManager.h"
#include <algorithm>

void FinanceManager::addIncome(const Income& income) {
    transactionRepo->addTransaction(income);
}

std::vector<std::shared_ptr<Income>> FinanceManager::getAllIncomes() const {
    auto allTransactions = transactionRepo->getAllTransactions(currentUserId);
    std::vector<std::shared_ptr<Income>> incomes;
    
    for (const auto& txn : allTransactions) {
        if (auto income = std::dynamic_pointer_cast<Income>(txn)) {
            incomes.push_back(income);
        }
    }
    return incomes;
}

bool FinanceManager::updateIncome(int id, const Money& newAmount) {
    auto txn = transactionRepo->getTransaction(id);
    if (txn && *txn) {
        if (auto income = std::dynamic_pointer_cast<Income>(*txn)) {
            income->setAmount(newAmount);
            transactionRepo->updateTransaction(*income);
            return true;
        }
    }
    return false;
}

bool FinanceManager::deleteIncome(int id) {
    transactionRepo->removeTransaction(id);
    return true;
}

void FinanceManager::addExpense(const Expense& expense) {
    transactionRepo->addTransaction(expense);
}

std::vector<std::shared_ptr<Expense>> FinanceManager::getAllExpenses() const {
    auto allTransactions = transactionRepo->getAllTransactions(currentUserId);
    std::vector<std::shared_ptr<Expense>> expenses;
    
    for (const auto& txn : allTransactions) {
        if (auto expense = std::dynamic_pointer_cast<Expense>(txn)) {
            expenses.push_back(expense);
        }
    }
    return expenses;
}

bool FinanceManager::updateExpense(int id, const Money& newAmount) {
    auto txn = transactionRepo->getTransaction(id);
    if (txn && *txn) {
        if (auto expense = std::dynamic_pointer_cast<Expense>(*txn)) {
            expense->setAmount(newAmount);
            transactionRepo->updateTransaction(*expense);
            return true;
        }
    }
    return false;
}

bool FinanceManager::deleteExpense(int id) {
    transactionRepo->removeTransaction(id);
    return true;
}

void FinanceManager::addBudget(const Budget& budget) {
    budgetService->setBudget(budget);
}

bool FinanceManager::checkBudget(const std::string& category) const {
    // We need expenses to check against budget
    // Currently getAllExpenses returns all expenses for the user
    // This might be inefficient if we have many expenses, but fine for now.
    auto expenses = getAllExpenses();
    return budgetService->isBudgetExceeded(category, expenses);
}

std::vector<Budget> FinanceManager::getAllBudgets() const {
    return budgetService->getAllBudgets();
}
