#include "SystemTests.h"
#include <fstream>
#include <filesystem>

void SystemTests::runAllTests() {
    std::cout << "\n========================================\n";
    std::cout << "   Running System Tests\n";
    std::cout << "========================================\n";

    try {
        testUserManagement();
        testTransactionManagement();
        testBudgetManagement();
        testReporting();
        
        std::cout << "\n✅ ALL TESTS PASSED!\n";
    } catch (const std::exception& e) {
        std::cout << "\n❌ TESTS FAILED: " << e.what() << "\n";
    }
}

void SystemTests::testUserManagement() {
    std::cout << "[TEST] User Management... ";
    PostgresUserRepository userRepo;
    std::string username = "TestUser_" + std::to_string(std::time(nullptr)); // Unique user
    
    userRepo.addUser(username, username + "@example.com");
    auto user = userRepo.getUserByUsername(username);
    
    assert(user.has_value());
    assert(user->getName() == username);
    std::cout << "PASSED\n";
}

void SystemTests::testTransactionManagement() {
    std::cout << "[TEST] Transaction Management... ";
    
    // Setup
    PostgresUserRepository userRepo;
    auto txnRepo = std::make_shared<PostgresTransactionRepository>();
    auto budgetRepo = std::make_shared<PostgresBudgetRepository>();
    
    std::string username = "TxnTestUser_" + std::to_string(std::time(nullptr));
    userRepo.addUser(username, "txn@test.com");
    int userId = userRepo.getUserByUsername(username)->getId();
    
    auto budgetService = std::make_shared<BudgetService>(budgetRepo, userId);
    FinanceManager fm(txnRepo, budgetService, userId);
    
    // Add Income
    fm.addIncome(Income(0, userId, Money(1000.0), Date("2024-01-01"), "Salary"));
    auto incomes = fm.getAllIncomes();
    assert(incomes.size() == 1);
    assert(incomes[0]->getAmount().value() == 1000.0);
    assert(incomes[0]->getSource() == "Salary");
    
    // Add Expense
    fm.addExpense(Expense(0, userId, Money(200.0), Date("2024-01-02"), "Food"));
    auto expenses = fm.getAllExpenses();
    assert(expenses.size() == 1);
    assert(expenses[0]->getAmount().value() == 200.0);
    assert(expenses[0]->getCategory() == "Food");
    
    // Delete Expense
    fm.deleteExpense(expenses[0]->getId());
    expenses = fm.getAllExpenses();
    assert(expenses.empty());
    
    std::cout << "PASSED\n";
}

void SystemTests::testBudgetManagement() {
    std::cout << "[TEST] Budget Management... ";
    
    PostgresUserRepository userRepo;
    auto txnRepo = std::make_shared<PostgresTransactionRepository>();
    auto budgetRepo = std::make_shared<PostgresBudgetRepository>();
    
    std::string username = "BudgetTestUser_" + std::to_string(std::time(nullptr));
    userRepo.addUser(username, "budget@test.com");
    int userId = userRepo.getUserByUsername(username)->getId();
    
    auto budgetService = std::make_shared<BudgetService>(budgetRepo, userId);
    FinanceManager fm(txnRepo, budgetService, userId);
    
    // Set Budget
    fm.addBudget(Budget(0, userId, "Food", Money(500.0), Date("2024-01-01")));
    
    // Check Budget (Empty expenses)
    assert(fm.checkBudget("Food") == false);
    
    // Add Expense under limit
    fm.addExpense(Expense(0, userId, Money(300.0), Date("2024-01-01"), "Food"));
    assert(fm.checkBudget("Food") == false);
    
    // Add Expense over limit
    fm.addExpense(Expense(0, userId, Money(300.0), Date("2024-01-02"), "Food")); // Total 600 > 500
    assert(fm.checkBudget("Food") == true);
    
    std::cout << "PASSED\n";
}

void SystemTests::testReporting() {
    std::cout << "[TEST] Reporting... ";
    
    PostgresUserRepository userRepo;
    auto txnRepo = std::make_shared<PostgresTransactionRepository>();
    auto budgetRepo = std::make_shared<PostgresBudgetRepository>();
    
    std::string username = "ReportTestUser_" + std::to_string(std::time(nullptr));
    userRepo.addUser(username, "report@test.com");
    int userId = userRepo.getUserByUsername(username)->getId();
    
    auto budgetService = std::make_shared<BudgetService>(budgetRepo, userId);
    FinanceManager fm(txnRepo, budgetService, userId);
    
    fm.addIncome(Income(0, userId, Money(1000.0), Date("2024-01-01"), "Salary"));
    fm.addExpense(Expense(0, userId, Money(200.0), Date("2024-01-02"), "Food"));
    
    ReportService rs;
    CsvReportStrategy strategy;
    std::string filename = "test_report.csv";
    
    // Remove if exists
    if (std::filesystem::exists(filename)) {
        std::filesystem::remove(filename);
    }
    
    rs.generateReport(fm, strategy, filename);
    
    assert(std::filesystem::exists(filename));
    
    // Optional: Check content
    std::ifstream file(filename);
    std::string line;
    bool foundSalary = false;
    while (std::getline(file, line)) {
        if (line.find("Salary") != std::string::npos) foundSalary = true;
    }
    assert(foundSalary);
    
    // Cleanup
    std::filesystem::remove(filename);
    
    std::cout << "PASSED\n";
}
