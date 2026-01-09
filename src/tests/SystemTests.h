#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include "application/services/FinanceManager.h"
#include "application/services/ReportService.h"
#include "application/services/BudgetService.h"
#include "infrastructure/repositories/PostgresUserRepository.h"
#include "infrastructure/repositories/PostgresTransactionRepository.h"
#include "infrastructure/repositories/PostgresBudgetRepository.h"
#include "infrastructure/strategies/CsvReportStrategy.h"

class SystemTests {
public:
    void runAllTests();

private:
    void testUserManagement();
    void testTransactionManagement();
    void testBudgetManagement();
    void testReporting();

    // Helper to setup clean environment (if possible)
    // For now we just use a test user
    const std::string TEST_USER = "TestUser_" + std::to_string(std::time(nullptr));
};
