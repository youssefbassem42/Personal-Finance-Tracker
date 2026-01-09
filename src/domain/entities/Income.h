#pragma once
#include "Transaction.h"
#include <iostream>
#include "../value_objects/Money.h"
#include "../value_objects/Date.h"


class Income : public Transaction{
private:
    std::string source;

public:
    Income(int id, int userId, const Money& amount, 
    const Date& date, const std::string& source)
    : Transaction(id, userId, amount, date), source(source) {}
    
    std::string getSource() const { return source; }
    TransactionType getType() const override { return TransactionType::Income; }

    void setAmount(const Money& amount) { this->amount = amount; }


    void print() const override {
        std::cout << "[INCOME]\n"
                << "  ID: " << id << "\n"
                << "  User ID: " << userId << "\n"
                << "  Source: " << source << "\n"
                << "  Date: " << date.toString() << "\n";
        std::cout<<"  Amount: ";
        amount.print();
        std::cout<<"\n";
    }

};