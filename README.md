# 💰 Personal Finance Tracker

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Database](https://img.shields.io/badge/Database-PostgreSQL-336791.svg)
![Build](https://img.shields.io/badge/Build-CMake-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

A robust, high-performance console application for managing personal finances. Built with modern C++ and PostgreSQL, featuring a clean **Layered Architecture** and industry-standard **Design Patterns**.

---

## 🚀 Features

*   **📊 Transaction Management**: Track Incomes and Expenses with ease.
*   **📉 Budget Control**: Set monthly limits per category and get real-time warnings.
*   **📑 Reporting**: Generate detailed financial reports (CSV export).
*   **🔐 User Management**: Multi-user support with secure data isolation.
*   **🖥️ Interactive CLI**: User-friendly command-line interface.

## 🛠️ Tech Stack

*   **Core**: C++17 (STL, Smart Pointers)
*   **Database**: PostgreSQL (via `libpqxx`)
*   **Build System**: CMake
*   **Architecture**: Layered (Presentation, Application, Domain, Infrastructure)

## 🏗️ Architecture & Design

This project is built to demonstrate professional software engineering practices.

*   **[Architecture Overview](docs/ARCHITECTURE.md)**: Detailed breakdown of the layered structure.
*   **[Design Patterns](docs/DESIGN_PATTERNS.md)**: Deep dive into Singleton, Repository, Factory, Facade, and Strategy patterns.
*   **[Database Schema](docs/DATABASE_SCHEMA.md)**: ER diagrams and table definitions.

## 🏁 Quick Start

### Prerequisites
*   C++ Compiler (GCC/Clang)
*   CMake
*   PostgreSQL
*   libpqxx

### Installation

1.  **Clone the repository**
    ```bash
    git clone https://github.com/yourusername/Personal-Finance-Tracker.git
    cd Personal-Finance-Tracker
    ```

2.  **Configure Database**
    Create a `config/database.env` file:
    ```env
    POSTGRES_CONN=postgresql://user:password@localhost:5432/finance_db
    ```

3.  **Build**
    ```bash
    ./scripts/build.sh
    ```

4.  **Run**
    ```bash
    ./build/finance_tracker
    ```

## 🧪 Testing

Run the automated system test suite to verify all functionalities:

```bash
cd build
./finance_tracker --test
```

## 📂 Project Structure

```
src/
├── application/    # Business Logic (Facade, Services)
├── domain/         # Entities & Interfaces (Pure C++)
├── infrastructure/ # Database & Concrete Implementations
├── presentation/   # CLI / UI Layer
└── tests/          # System Tests
```

## 🤝 Contributing

Contributions are welcome! Please read the [Architecture Guide](docs/ARCHITECTURE.md) before submitting a Pull Request.

---
*Built with ❤️ by Youssef*
