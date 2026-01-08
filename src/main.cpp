#include "domain/entities/User.h"
#include "domain/entities/Income.h"
#include "domain/entities/Expense.h"
#include "domain/entities/Budget.h"

int main() {
    try {
        Money salaryAmount(5000);
        Money foodAmount(300);
        Money foodLimit(1000);

        Date d1("2026-01-01");
        Date d2("2026-01-02");

        Income salary(1, 1, salaryAmount, d1, "Job");
        Expense food(2, 1, foodAmount, d2, "Food");
        Budget budget(1, 1, "Food", foodLimit, d2);

        salary.print();
        food.print();
        budget.print();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
