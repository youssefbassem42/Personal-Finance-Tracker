#pragma once
#include <string>
#include <iostream>
#include "../value_objects/Date.h"
#include "../value_objects/Money.h"


enum class TransactionType{
    Income,
    Expense
};

class Transaction{
protected:
    int id, userId;
    Money amount;
    Date date;

public:
    Transaction(int id, int userId, Money& amount, Date& date) : id(id), userId(userId), amount(amount), date(date) {}

    int getId() const { return id; }
    int getUserId() const { return userId; }
    Money getAmount() const { return amount; }
    Date getDate() const { return date; }

    virtual TransactionType getType() const = 0;
    virtual ~Transaction() = default;
    virtual void print() const = 0;

};