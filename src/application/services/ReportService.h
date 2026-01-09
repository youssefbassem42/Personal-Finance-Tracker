#pragma once
#include "FinanceManager.h"

#pragma once
#include "FinanceManager.h"
#include "domain/strategies/IReportStrategy.h"
#include <memory>

class ReportService {
public:
    double totalIncome(const FinanceManager& manager) const;
    double totalExpenses(const FinanceManager& manager) const;
    double totalBalance(const FinanceManager& manager) const;
    
    // Strategy Pattern: Pass the strategy to use
    void generateReport(const FinanceManager& manager, IReportStrategy& strategy, const std::string& destination) const {
        strategy.generate(manager, destination);
    }
};