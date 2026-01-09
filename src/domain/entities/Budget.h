#pragma once
#include "Transaction.h"
#include <iostream>
#include "../value_objects/Money.h"
#include "../value_objects/Date.h"


class Budget{
    int id, userId;
    std::string category;
    Money limit_amount;
    Date date;

public:
    Budget(int id, int userId, std::string category, const Money& limit_amount, const Date& date) : id(id), userId(userId), category(category), limit_amount(limit_amount), date(date) {}

    int getId() const { return id; }
    int getUserId() const { return userId; }
    std::string getCategory() const { return category; }
    Money getLimitAmount() const { return limit_amount; }
    Date getDate() const { return date; }
    
    

void print() const {
    std::cout << "[BUDGET]\n"
              << "  User ID: " << userId << "\n"
              << "  Category: " << category << "\n"
              << "  Date: " << date.toString() << "\n";
    std::cout<< "  Limit Amount: ";
    limit_amount.print();
    std::cout<< "\n";

}


};