#include "infrastructure/repositories/PostgresTransactionRepository.h"
#include "domain/factories/TransactionFactory.h"
#include "domain/entities/Income.h"
#include "domain/entities/Expense.h"
#include <pqxx/pqxx>

void PostgresTransactionRepository::addTransaction(const Transaction& transaction) {
    pqxx::work work(*dbConn->getConnection());
    
    std::string type = (transaction.getType() == TransactionType::Income) ? "INCOME" : "EXPENSE";
    std::string source = "";
    std::string category = "";

    if (auto* inc = dynamic_cast<const Income*>(&transaction)) {
        source = inc->getSource();
    } else if (auto* exp = dynamic_cast<const Expense*>(&transaction)) {
        category = exp->getCategory();
    }

    work.exec_params(
        "INSERT INTO transactions (user_id, amount, date, type, source, category) VALUES ($1, $2, $3, $4, $5, $6)",
        transaction.getUserId(),
        transaction.getAmount().value(),
        transaction.getDate().toString(),
        type,
        source,
        category
    );
    work.commit();
}

void PostgresTransactionRepository::removeTransaction(int id) {
    pqxx::work work(*dbConn->getConnection());
    work.exec_params("DELETE FROM transactions WHERE id = $1", id);
    work.commit();
}

void PostgresTransactionRepository::updateTransaction(const Transaction& transaction) {
    std::string source = "";
    std::string category = "";
    if (auto* inc = dynamic_cast<const Income*>(&transaction)) {
        source = inc->getSource();
    } else if (auto* exp = dynamic_cast<const Expense*>(&transaction)) {
        category = exp->getCategory();
    }
    
    std::string type = (transaction.getType() == TransactionType::Income) ? "INCOME" : "EXPENSE";

    pqxx::work work(*dbConn->getConnection());
    work.exec_params(
        "UPDATE transactions SET amount=$1, date=$2, type=$3, source=$4, category=$5 WHERE id=$6",
        transaction.getAmount().value(),
        transaction.getDate().toString(),
        type,
        source,
        category,
        transaction.getId()
    );
    work.commit();
}

std::optional<std::shared_ptr<Transaction>> PostgresTransactionRepository::getTransaction(int id) {
    pqxx::work work(*dbConn->getConnection());
    pqxx::result result = work.exec_params("SELECT * FROM transactions WHERE id = $1", id);
    
    if (result.empty()) return std::nullopt;
    
    auto row = result[0];
    std::string type = row["type"].as<std::string>();
    std::string details = (type == "INCOME") ? row["source"].as<std::string>() : row["category"].as<std::string>();

    return TransactionFactory::createTransaction(
        type,
        row["id"].as<int>(),
        row["user_id"].as<int>(),
        row["amount"].as<double>(),
        row["date"].as<std::string>(),
        details
    );
}

std::vector<std::shared_ptr<Transaction>> PostgresTransactionRepository::getAllTransactions(int userId) {
    pqxx::work work(*dbConn->getConnection());
    pqxx::result result = work.exec_params("SELECT * FROM transactions WHERE user_id = $1", userId);
    
    std::vector<std::shared_ptr<Transaction>> transactions;
    for (const auto& row : result) {
        std::string type = row["type"].as<std::string>();
        std::string details = (type == "INCOME") ? row["source"].as<std::string>() : row["category"].as<std::string>();

        transactions.push_back(TransactionFactory::createTransaction(
            type,
            row["id"].as<int>(),
            row["user_id"].as<int>(),
            row["amount"].as<double>(),
            row["date"].as<std::string>(),
            details
        ));
    }
    return transactions;
}

std::vector<std::shared_ptr<Transaction>> PostgresTransactionRepository::getTransactionsByDate(int userId, const std::string& date) {
    pqxx::work work(*dbConn->getConnection());
    pqxx::result result = work.exec_params("SELECT * FROM transactions WHERE user_id = $1 AND date = $2", userId, date);
    
    std::vector<std::shared_ptr<Transaction>> transactions;
    for (const auto& row : result) {
        std::string type = row["type"].as<std::string>();
        std::string details = (type == "INCOME") ? row["source"].as<std::string>() : row["category"].as<std::string>();

        transactions.push_back(TransactionFactory::createTransaction(
            type,
            row["id"].as<int>(),
            row["user_id"].as<int>(),
            row["amount"].as<double>(),
            row["date"].as<std::string>(),
            details
        ));
    }
    return transactions;
}
