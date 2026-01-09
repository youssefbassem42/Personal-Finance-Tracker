#include "infrastructure/database/PostgresConnection.h"
#include "infrastructure/repositories/PostgresUserRepository.h"
#include "infrastructure/repositories/PostgresTransactionRepository.h"
#include "infrastructure/repositories/PostgresBudgetRepository.h"
#include "application/services/FinanceManager.h"
#include "application/services/BudgetService.h"
#include "application/services/ReportService.h"
#include "presentation/CLI.h"
#include "tests/SystemTests.h"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    // Check for test mode
    if (argc > 1 && std::strcmp(argv[1], "--test") == 0) {
        SystemTests tests;
        tests.runAllTests();
        return 0;
    }

    try {
        // 1. Setup Repositories
        PostgresUserRepository userRepo;
        auto transactionRepo = std::make_shared<PostgresTransactionRepository>();
        auto budgetRepo = std::make_shared<PostgresBudgetRepository>();

        // 2. Create a test user (if not exists)
        try {
            userRepo.addUser("Demo User", "demo@example.com");
        } catch (...) {
            // Ignore if already exists
        }
        
        // Get the user ID
        auto user = userRepo.getUserByUsername("Demo User");
        if (!user) {
            std::cerr << "Failed to find/create user.\n";
            return 1;
        }
        int userId = user->getId();
        
        // 3. Setup Services
        auto budgetService = std::make_shared<BudgetService>(budgetRepo, userId);
        auto reportService = std::make_shared<ReportService>();

        // 4. Setup Facade
        auto financeManager = std::make_shared<FinanceManager>(transactionRepo, budgetService, userId);

        // 5. Launch CLI
        CLI cli(financeManager, reportService);
        cli.run();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}