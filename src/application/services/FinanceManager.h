#pragma once
#include <vector>
#include <memory>
#include "domain/entities/Income.h"
#include "domain/entities/Expense.h"

#include "domain/repositories/ITransactionRepository.h"

#include "domain/repositories/ITransactionRepository.h"
#include "application/services/BudgetService.h"

class FinanceManager {
private:
    std::shared_ptr<ITransactionRepository> transactionRepo;
    std::shared_ptr<BudgetService> budgetService;
    int currentUserId;

public:
    FinanceManager(std::shared_ptr<ITransactionRepository> txnRepo, std::shared_ptr<BudgetService> budgetSvc, int userId) 
        : transactionRepo(txnRepo), budgetService(budgetSvc), currentUserId(userId) {}

    void addIncome(const Income& income);
    std::vector<std::shared_ptr<Income>> getAllIncomes() const;
    bool updateIncome(int id, const Money& newAmount);
    bool deleteIncome(int id);

    void addExpense(const Expense& expense);
    std::vector<std::shared_ptr<Expense>> getAllExpenses() const;
    bool updateExpense(int id, const Money& newAmount);
    bool deleteExpense(int id);

    // Budget Management
    void addBudget(const Budget& budget);
    bool checkBudget(const std::string& category) const;
    std::vector<Budget> getAllBudgets() const;

    int getCurrentUserId() const { return currentUserId; }
};