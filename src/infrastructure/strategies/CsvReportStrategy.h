#pragma once
#include "domain/strategies/IReportStrategy.h"
#include <fstream>
#include <iostream>

class CsvReportStrategy : public IReportStrategy {
public:
    void generate(const FinanceManager& manager, const std::string& destination) override {
        std::ofstream file(destination);
        if (!file.is_open()) {
            std::cerr << "Error: Could not Open File " << destination << " for writing." << std::endl;
            return;
        }

        file << "Date,Description,Amount\n";
        for (const auto& income : manager.getAllIncomes()) {
            file << income->getDate().toString() << "," << income->getSource() << "," << income->getAmount().value() << "\n";
        }
        for (const auto& expense : manager.getAllExpenses()) {
            file << expense->getDate().toString() << "," << expense->getCategory() << "," << expense->getAmount().value() << "\n";
        }
        double totalInc = 0;
        for (const auto& i : manager.getAllIncomes()) totalInc += i->getAmount().value();
        double totalExp = 0;
        for (const auto& e : manager.getAllExpenses()) totalExp += e->getAmount().value();

        file << "Total Income," << totalInc << "\n";
        file << "Total Expenses," << totalExp << "\n";
        file << "Total Balance," << (totalInc - totalExp) << "\n";
        file.close();
        std::cout << "Report exported to " << destination << "\n";
    }
};
