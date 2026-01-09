#include <fstream>
#include "ReportService.h"

double ReportService::totalIncome(const FinanceManager& manager) const {
    double total = 0;
    for (const auto& income : manager.getAllIncomes()) {
        total += income->getAmount().value();
    }
    return total;
}


double ReportService::totalExpenses(const FinanceManager& manager) const {
    double total = 0;
    for (const auto& expense : manager.getAllExpenses()) {
        total += expense->getAmount().value();
    }
    return total;
}



double ReportService::totalBalance(const FinanceManager& manager) const {
    return totalIncome(manager) - totalExpenses(manager);
}


