#pragma once
#include "Transaction.h"
#include <iostream>
#include "../value_objects/Money.h"
#include "../value_objects/Date.h"


class Expense : public Transaction{
private:
    std::string category;

public:
    Expense(int id, int userId, Money& amount, Date& date, const std::string& category)
    : Transaction(id, userId, amount, date), category(category) {}


    std::string getCategory() const { return category; }
    TransactionType getType() const override { return TransactionType::Expense; }
void print() const override {
    std::cout << "[EXPENSE]\n"
              << "  ID: " << id << "\n"
              << "  User ID: " << userId << "\n"
              << "  Category: " << category << "\n"
              << "  Date: " << date.toString() << "\n";
    std::cout<<"  Amount: ";
    amount.print();
    std::cout<<"\n";
}

};