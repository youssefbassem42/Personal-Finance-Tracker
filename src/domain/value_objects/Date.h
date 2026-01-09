#pragma once
#include <string>


class Date{
private:
    std::string value;
    bool isValidFormat(const std::string& date) const {
        return date.size() == 10 && date[4] == '-' && date[7] == '-';
    }
public:
    explicit Date(const std::string& date){
        if (!isValidFormat(date)){
            throw std::invalid_argument("Invalid date format (YYYY-MM-DD)");
        }
        value = date;
    }
    std::string toString() const {
        return value;
    }
    void print() const {
        std::cout<<value;
    }
};

