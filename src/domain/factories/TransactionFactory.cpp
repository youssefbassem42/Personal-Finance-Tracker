#include "domain/factories/TransactionFactory.h"
#include "domain/entities/Income.h"
#include "domain/entities/Expense.h"
#include <stdexcept>

std::shared_ptr<Transaction> TransactionFactory::createTransaction(
    const std::string& type, int id, int userId, double amount, 
    const std::string& dateStr, const std::string& details) {
    
    Money money(amount);
    Date date(dateStr);

    if (type == "INCOME") {
        return std::make_shared<Income>(id, userId, money, date, details);
    } 
    else if (type == "EXPENSE") {
        return std::make_shared<Expense>(id, userId, money, date, details);
    }
    
    throw std::invalid_argument("Unknown transaction type: " + type);
}
