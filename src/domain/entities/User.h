#pragma once
#include <string>
#include <iostream>

class User{
private:
    int id;
    std::string name;
    std::string email;
    
public:
    User(int id, std::string name, std::string email) : id(id), name(name), email(email) {}
    int getId() const {return id;}
    std::string getName() const {return name;}
    std::string getEmail() const {return email;}

void print() const {
    std::cout << "[USER]\n"
              << "  ID: " << id << "\n"
              << "  Name: " << name << "\n"
              << "  Email: " << email << "\n";
}

};
