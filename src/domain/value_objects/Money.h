#pragma once
#include <string>
#include <stdexcept>

class Money{
private:
    double amount;
public:
    explicit Money(double value){
        if (value < 0){
            throw std::invalid_argument("Money amount cannot be negative");
        }
        amount = value;
    }
    double value() const {return amount;}

    void print() const {
        std::cout << amount << "\n";
    }
    bool operator<(const Money& other) {
        return amount < other.amount;
    }
    bool operator>(const Money& other) {
        return amount > other.amount;
    }
    Money operator+(const Money& other) {
        return Money(amount + other.amount);
    }
    Money operator-(const Money& other) {
        return Money(amount - other.amount);
    }
    Money operator*(const Money& other) {
        return Money(amount * other.amount);
    }
    Money operator/(const Money& other) {
        return Money(amount / other.amount);
    }
};

