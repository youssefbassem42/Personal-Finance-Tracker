#pragma once
#include <string>
#include "application/services/FinanceManager.h"

class IReportStrategy {
public:
    virtual ~IReportStrategy() = default;
    virtual void generate(const FinanceManager& manager, const std::string& destination) = 0;
};
