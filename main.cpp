#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Expense {
public:
    string category;
    double amount;
    string description;

    Expense(string c, double a, string d) {
        category = c;
        amount = a;
        description = d;
    }
};

void saveExpenses(const vector<Expense>& expenses) {
    ofstream file("expenses.txt");

    for (const auto& e : expenses) {
        file << e.category << "|"
             << e.amount << "|"
             << e.description << "\n";
    }

    file.close();
}

void loadExpenses(vector<Expense>& expenses) {
    ifstream file("expenses.txt");

    string category, amountText, description;

    while (getline(file, category, '|')) {
        getline(file, amountText, '|');
        getline(file, description);

        if (!category.empty() && !amountText.empty()) {
            expenses.push_back(
                Expense(category, stod(amountText), description)
            );
        }
    }

    file.close();
}

void addExpense(vector<Expense>& expenses) {

    string category;
    string description;
    double amount;

    cout << "\nEnter category: ";
    cin >> ws;
    getline(cin, category);

    cout << "Enter amount: ";
    cin >> amount;

    cout << "Enter description: ";
    cin >> ws;
    getline(cin, description);

    expenses.push_back(Expense(category, amount, description));

    saveExpenses(expenses);

    cout << "\nExpense added successfully!\n";
}

void viewExpenses(const vector<Expense>& expenses) {

    if (expenses.empty()) {
        cout << "\nNo expenses recorded yet.\n";
        return;
    }

    cout << "\n================ EXPENSES ================\n";

    for (int i = 0; i < expenses.size(); i++) {

        cout << "\nExpense " << i + 1 << endl;
        cout << "Category: " << expenses[i].category << endl;
        cout << "Amount: Rs. " << expenses[i].amount << endl;
        cout << "Description: " << expenses[i].description << endl;
    }
}

void searchByCategory(const vector<Expense>& expenses) {

    string category;
    bool found = false;

    cout << "\nEnter category: ";
    cin >> ws;
    getline(cin, category);

    for (int i = 0; i < expenses.size(); i++) {

        if (expenses[i].category == category) {

            cout << "\nCategory: " << expenses[i].category << endl;
            cout << "Amount: Rs. " << expenses[i].amount << endl;
            cout << "Description: " << expenses[i].description << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "\nNo expense found in this category.\n";
    }
}

void calculateTotal(const vector<Expense>& expenses) {

    if (expenses.empty()) {
        cout << "\nNo expenses recorded yet.\n";
        return;
    }

    double total = 0;

    for (const auto& e : expenses) {
        total += e.amount;
    }

    cout << "\n==============================\n";
    cout << "Total Expenses: Rs. " << total << endl;
    cout << "==============================\n";
}

void deleteExpense(vector<Expense>& expenses) {

    if (expenses.empty()) {
        cout << "\nNo expenses available.\n";
        return;
    }

    viewExpenses(expenses);

    int id;

    cout << "\nEnter expense number to delete: ";
    cin >> id;

    if (id >= 1 && id <= expenses.size()) {

        expenses.erase(expenses.begin() + id - 1);

        saveExpenses(expenses);

        cout << "\nExpense deleted successfully!\n";

    } else {

        cout << "\nInvalid expense number.\n";
    }
}

int main() {

    vector<Expense> expenses;

    loadExpenses(expenses);

    int choice;

    while (true) {

        cout << "\n\n====================================\n";
        cout << "       STUDENT EXPENSE TRACKER\n";
        cout << "====================================\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Search by Category\n";
        cout << "4. Calculate Total Expenses\n";
        cout << "5. Delete Expense\n";
        cout << "6. Exit\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\nPlease enter a number between 1 and 6.\n";

            continue;
        }

        switch (choice) {

        case 1:
            addExpense(expenses);
            break;

        case 2:
            viewExpenses(expenses);
            break;

        case 3:
            searchByCategory(expenses);
            break;

        case 4:
            calculateTotal(expenses);
            break;

        case 5:
            deleteExpense(expenses);
            break;

        case 6:
            cout << "\nThank you for using Student Expense Tracker!\n";
            return 0;

        default:
            cout << "\nInvalid choice. Please select 1-6.\n";
        }
    }

    return 0;
}