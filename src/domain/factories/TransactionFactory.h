#pragma once
#include <memory>
#include <string>
#include "domain/entities/Transaction.h"

class TransactionFactory {
public:
    static std::shared_ptr<Transaction> createTransaction(
        const std::string& type, 
        int id, 
        int userId, 
        double amount, 
        const std::string& dateStr, 
        const std::string& details
    );
};
