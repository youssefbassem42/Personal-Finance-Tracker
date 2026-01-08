#pragma once
#include <vector>
#include <memory>
#include "domain/entities/Income.h"
#include "domain/entities/Expense.h"

class FinanceManager {
private:
    std::vector<std::shared_ptr<Income>> incomes;
    std::vector<std::shared_ptr<Expense>> expenses;
public:
    void addIncome(const Income& income);

    const std::vector<std::shared_ptr<Income>>& getAllIncomes() const;

    bool updateIncome(int id, const Money& newAmount);

    bool deleteIncome(int id);

    void addExpense(const Expense& expenses);

    const std::vector<std::shared_ptr<Expense>>& getAllExpenses() const;

    bool updateExpense(int id, const Money& newAmount);

    bool deleteExpense(int id);
};