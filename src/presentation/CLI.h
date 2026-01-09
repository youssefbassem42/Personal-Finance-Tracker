#pragma once
#include "application/services/FinanceManager.h"
#include "application/services/ReportService.h"
#include "infrastructure/strategies/CsvReportStrategy.h"
#include <iostream>
#include <limits>
#include <iomanip>

class CLI {
private:
    std::shared_ptr<FinanceManager> financeManager;
    std::shared_ptr<ReportService> reportService;
    std::shared_ptr<CsvReportStrategy> csvStrategy;
    
    // Helper methods for input
    void clearScreen();
    void printHeader(const std::string& title);
    int getIntInput(const std::string& prompt);
    double getDoubleInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);
    std::string getDateInput(const std::string& prompt);
    void pause();

    // Menus
    void showMainMenu();
    void handleTransactionMenu();
    void handleBudgetMenu();
    void handleReportMenu();

    // Actions
    void addIncome();
    void addExpense();
    void viewTransactions();
    void setBudget();
    void checkBudget();
    void generateReport();

public:
    CLI(std::shared_ptr<FinanceManager> fm, std::shared_ptr<ReportService> rs) 
        : financeManager(fm), reportService(rs) {
        csvStrategy = std::make_shared<CsvReportStrategy>();
    }

    void run();
};
