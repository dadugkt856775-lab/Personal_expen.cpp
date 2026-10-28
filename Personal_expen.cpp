
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Expense {
public:
    int id;
    string date;
    string category;
    string description;
    double amount;

    Expense(int expenseId, string expenseDate,
            string expenseCategory, string expenseDescription,
            double expenseAmount) {
        id = expenseId;
        date = expenseDate;
        category = expenseCategory;
        description = expenseDescription;
        amount = expenseAmount;
    }

    void display() const {
        cout << left << setw(6) << id
             << setw(13) << date
             << setw(16) << category
             << setw(24) << description
             << fixed << setprecision(2)
             << amount << endl;
    }
};

class ExpenseTracker {
private:
    vector<Expense> expenses;
    double monthlyBudget;
    int nextId;

public:
    ExpenseTracker() {
        monthlyBudget = 0;
        nextId = 1;
    }

    void setBudget() {
        double budget;

        cout << "\nEnter your monthly budget (Rs.): ";
        cin >> budget;

        if (cin.fail() || budget <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a valid positive budget.\n";
            return;
        }

        monthlyBudget = budget;
        cout << "Monthly budget updated successfully!\n";
    }

    void addExpense() {
        string date, category, description;
        double amount;

        cout << "\nEnter date (DD-MM-YYYY): ";
        cin >> date;

        cout << "Enter category "
             << "(Food/Travel/Education/Bills/Other): ";
        getline(cin >> ws, category);

        cout << "Enter description: ";
        getline(cin, description);

        cout << "Enter amount (Rs.): ";
        cin >> amount;

        if (cin.fail() || amount <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid expense amount!\n";
            return;
        }

        expenses.emplace_back(nextId++, date, category,
                              description, amount);

        cout << "Expense added successfully!\n";

        if (monthlyBudget > 0 &&
            getTotalExpenses() > monthlyBudget) {
            cout << "Warning: Your recorded expenses exceed "
                 << "your budget!\n";
        }
    }

    double getTotalExpenses() const {
        double total = 0;

        for (const Expense& expense : expenses)
            total += expense.amount;

        return total;
    }

    void displayAllExpenses() const {
        if (expenses.empty()) {
            cout << "\nNo expenses recorded yet.\n";
            return;
        }

        cout << "\n================ EXPENSE REPORT ================\n";
        cout << left << setw(6) << "ID"
             << setw(13) << "Date"
             << setw(16) << "Category"
             << setw(24) << "Description"
             << "Amount (Rs.)\n";

        for (const Expense& expense : expenses)
            expense.display();
    }

    void searchByCategory() const {
        string searchCategory;
        bool found = false;
        double categoryTotal = 0;

        cout << "\nEnter category to search: ";
        getline(cin >> ws, searchCategory);

        cout << "\nExpenses in category: "
             << searchCategory << endl;

        for (const Expense& expense : expenses) {
            if (expense.category == searchCategory) {
                expense.display();
                categoryTotal += expense.amount;
                found = true;
            }
        }

        if (found) {
            cout << fixed << setprecision(2);
            cout << "Category total: Rs. "
                 << categoryTotal << endl;
        } else {
            cout << "No matching expenses found.\n";
        }
    }

    void deleteExpense() {
        int id;

        cout << "\nEnter expense ID to delete: ";
        cin >> id;

        for (auto it = expenses.begin();
             it != expenses.end(); ++it) {
            if (it->id == id) {
                cout << "Deleted expense: "
                     << it->description << endl;

                expenses.erase(it);
                cout << "Expense deleted successfully!\n";
                return;
            }
        }

        cout << "Expense ID not found!\n";
    }

    void showHighestExpense() const {
        if (expenses.empty()) {
            cout << "\nNo expenses available.\n";
            return;
        }

        const Expense* highest = &expenses[0];

        for (const Expense& expense : expenses) {
            if (expense.amount > highest->amount)
                highest = &expense;
        }

        cout << "\n========== HIGHEST EXPENSE ==========\n";
        highest->display();
    }

    void displaySummary() const {
        double total = getTotalExpenses();

        cout << "\n========== BUDGET SUMMARY ==========\n";
        cout << fixed << setprecision(2);
        cout << "Number of expenses : " << expenses.size() << endl;
        cout << "Total spending     : Rs. " << total << endl;

        if (monthlyBudget > 0) {
            cout << "Monthly budget     : Rs. "
                 << monthlyBudget << endl;

            double remaining = monthlyBudget - total;

            if (remaining >= 0) {
                cout << "Budget remaining   : Rs. "
                     << remaining << endl;
            } else {
                cout << "Budget exceeded by : Rs. "
                     << -remaining << endl;
            }

            double percentage = (total / monthlyBudget) * 100;
            cout << "Budget used        : "
                 << percentage << "%\n";
        } else {
            cout << "Monthly budget     : Not set\n";
        }
    }

    void run() {
        int choice;

        do {
            cout << "\n===== EXPENSE TRACKER =====\n";
            cout << "1. Set Monthly Budget\n";
            cout << "2. Add Expense\n";
            cout << "3. View All Expenses\n";
            cout << "4. Search by Category\n";
            cout << "5. Delete Expense\n";
            cout << "6. Show Highest Expense\n";
            cout << "7. Budget Summary\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "Invalid input!\n";
                break;
            }

            switch (choice) {
                case 1: setBudget(); break;
                case 2: addExpense(); break;
                case 3: displayAllExpenses(); break;
                case 4: searchByCategory(); break;
                case 5: deleteExpense(); break;
                case 6: showHighestExpense(); break;
                case 7: displaySummary(); break;
                case 0:
                    cout << "Thank you for using Expense Tracker!\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }

        } while (choice != 0);
    }
};

int main() {
    ExpenseTracker tracker;
    tracker.run();
    return 0;
}
