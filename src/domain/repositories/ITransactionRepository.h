#pragma once
#include <vector>
#include <memory>
#include <optional>
#include "domain/entities/Transaction.h"


class ITransactionRepository {
public:
    virtual ~ITransactionRepository() = default;
    virtual void addTransaction(const Transaction& transaction) = 0;
    virtual void removeTransaction(int id) = 0;
    virtual void updateTransaction(const Transaction& transaction) = 0;
    virtual std::optional<std::shared_ptr<Transaction>> getTransaction(int id) = 0;
    virtual std::vector<std::shared_ptr<Transaction>> getAllTransactions(int userId) = 0;
    virtual std::vector<std::shared_ptr<Transaction>> getTransactionsByDate(int userId, const std::string& date) = 0;
};