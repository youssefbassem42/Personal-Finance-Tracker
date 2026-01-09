#include "CLI.h"

void CLI::clearScreen() {
    // ANSI escape code to clear screen
    std::cout << "\033[2J\033[1;1H";
}

void CLI::printHeader(const std::string& title) {
    std::cout << "\n========================================\n";
    std::cout << "   " << title << "\n";
    std::cout << "========================================\n";
}

void CLI::pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int CLI::getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double CLI::getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string CLI::getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

std::string CLI::getDateInput(const std::string& prompt) {
    // Simple validation could be added here
    return getStringInput(prompt + " (YYYY-MM-DD): ");
}

void CLI::run() {
    while (true) {
        clearScreen();
        printHeader("Personal Finance Tracker");
        std::cout << "1. Manage Transactions\n";
        std::cout << "2. Manage Budgets\n";
        std::cout << "3. Reports\n";
        std::cout << "4. Exit\n";
        
        int choice = getIntInput("Enter choice: ");
        
        switch (choice) {
            case 1: handleTransactionMenu(); break;
            case 2: handleBudgetMenu(); break;
            case 3: handleReportMenu(); break;
            case 4: return;
            default: std::cout << "Invalid choice.\n"; pause();
        }
    }
}

void CLI::handleTransactionMenu() {
    while (true) {
        clearScreen();
        printHeader("Manage Transactions");
        std::cout << "1. Add Income\n";
        std::cout << "2. Add Expense\n";
        std::cout << "3. View All Transactions\n";
        std::cout << "4. Back\n";
        
        int choice = getIntInput("Enter choice: ");
        
        switch (choice) {
            case 1: addIncome(); pause(); break;
            case 2: addExpense(); pause(); break;
            case 3: viewTransactions(); pause(); break;
            case 4: return;
            default: std::cout << "Invalid choice.\n"; pause();
        }
    }
}

void CLI::handleBudgetMenu() {
    while (true) {
        clearScreen();
        printHeader("Manage Budgets");
        std::cout << "1. Set Budget\n";
        std::cout << "2. Check Budget Status\n";
        std::cout << "3. Back\n";
        
        int choice = getIntInput("Enter choice: ");
        
        switch (choice) {
            case 1: setBudget(); pause(); break;
            case 2: checkBudget(); pause(); break;
            case 3: return;
            default: std::cout << "Invalid choice.\n"; pause();
        }
    }
}

void CLI::handleReportMenu() {
    while (true) {
        clearScreen();
        printHeader("Reports");
        std::cout << "1. Generate CSV Report\n";
        std::cout << "2. Back\n";
        
        int choice = getIntInput("Enter choice: ");
        
        switch (choice) {
            case 1: generateReport(); pause(); break;
            case 2: return;
            default: std::cout << "Invalid choice.\n"; pause();
        }
    }
}

void CLI::addIncome() {
    printHeader("Add Income");
    double amount = getDoubleInput("Amount: ");
    std::string source = getStringInput("Source: ");
    std::string date = getDateInput("Date");
    
    // We need userId. FinanceManager has currentUserId but we need to pass it to Income constructor?
    // Wait, FinanceManager::addIncome takes Income object.
    // Income constructor needs userId.
    // We don't have access to userId here easily unless we expose it from FinanceManager or store it in CLI.
    // Let's assume FinanceManager handles the user context, but the Entity needs it.
    // Ideally, FinanceManager should have a factory method `createIncome(amount, source, date)` that uses the internal userId.
    // But currently we construct Income outside.
    // I'll add a getter for currentUserId to FinanceManager or just pass 0 and let FinanceManager fix it? 
    // No, FinanceManager expects a valid Income object.
    
    // Let's add `getCurrentUserId()` to FinanceManager.
    // Or simpler: I'll store userId in CLI or ask FinanceManager.
    // Let's assume for now we use a getter I will add to FinanceManager.
    
    // TEMPORARY FIX: I'll add getCurrentUserId to FinanceManager.h in a moment.
    // For now I will assume it exists.
    int userId = financeManager->getCurrentUserId();
    
    try {
        financeManager->addIncome(Income(0, userId, Money(amount), Date(date), source));
        std::cout << "Income added successfully!\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void CLI::addExpense() {
    printHeader("Add Expense");
    double amount = getDoubleInput("Amount: ");
    std::string category = getStringInput("Category: ");
    std::string date = getDateInput("Date");
    
    int userId = financeManager->getCurrentUserId();
    
    try {
        financeManager->addExpense(Expense(0, userId, Money(amount), Date(date), category));
        std::cout << "Expense added successfully!\n";
        
        // Check budget immediately
        if (financeManager->checkBudget(category)) {
            std::cout << "\n⚠️  WARNING: Budget exceeded for category '" << category << "'!\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void CLI::viewTransactions() {
    printHeader("All Transactions");
    auto incomes = financeManager->getAllIncomes();
    auto expenses = financeManager->getAllExpenses();
    
    std::cout << "\n--- Incomes ---\n";
    std::cout << std::left << std::setw(15) << "Date" << std::setw(20) << "Source" << "Amount\n";
    std::cout << "------------------------------------------------\n";
    for (const auto& inc : incomes) {
        std::cout << std::left << std::setw(15) << inc->getDate().toString() 
                  << std::setw(20) << inc->getSource() 
                  << inc->getAmount().value() << "\n";
    }
    
    std::cout << "\n--- Expenses ---\n";
    std::cout << std::left << std::setw(15) << "Date" << std::setw(20) << "Category" << "Amount\n";
    std::cout << "------------------------------------------------\n";
    for (const auto& exp : expenses) {
        std::cout << std::left << std::setw(15) << exp->getDate().toString() 
                  << std::setw(20) << exp->getCategory() 
                  << exp->getAmount().value() << "\n";
    }
}

void CLI::setBudget() {
    printHeader("Set Budget");
    std::string category = getStringInput("Category: ");
    double amount = getDoubleInput("Limit Amount: ");
    std::string date = getDateInput("Start Date");
    
    int userId = financeManager->getCurrentUserId();
    
    try {
        Money limit(amount);
        financeManager->addBudget(Budget(0, userId, category, limit, Date(date)));
        std::cout << "Budget set successfully!\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void CLI::checkBudget() {
    printHeader("Check Budget");
    std::string category = getStringInput("Category: ");
    
    if (financeManager->checkBudget(category)) {
        std::cout << "⚠️  Budget EXCEEDED for " << category << "\n";
    } else {
        std::cout << "✅  Budget within limits for " << category << "\n";
    }
}

void CLI::generateReport() {
    std::string filename = getStringInput("Enter filename (e.g., report.csv): ");
    try {
        reportService->generateReport(*financeManager, *csvStrategy, filename);
        std::cout << "Report generated successfully at " << filename << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error generating report: " << e.what() << "\n";
    }
}
