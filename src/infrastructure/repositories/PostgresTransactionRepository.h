#pragma once
#include "domain/repositories/ITransactionRepository.h"
#include "infrastructure/database/PostgresConnection.h"

class PostgresTransactionRepository : public ITransactionRepository {
private:
    PostgresConnection* dbConn;
public:
    PostgresTransactionRepository() : dbConn(&PostgresConnection::getInstance()) {}
    void addTransaction(const Transaction& transaction) override;
    void removeTransaction(int id) override;
    void updateTransaction(const Transaction& transaction) override;
    std::optional<std::shared_ptr<Transaction>> getTransaction(int id) override;
    std::vector<std::shared_ptr<Transaction>> getAllTransactions(int userId) override;
    std::vector<std::shared_ptr<Transaction>> getTransactionsByDate(int userId, const std::string& date) override;
};