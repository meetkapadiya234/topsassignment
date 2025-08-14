#include <iostream>
#include <string>
#include <sstream> // For converting numbers to string (works in Dev-C++)
using namespace std;

// Helper function to convert number to string
string numToString(long long num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

// BankAccount class
class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    string branchName;   // NEW: branch detail
    double balance;
    int pin;

public:
    // Constructor using scope resolution operator
    BankAccount(string accNum, string accHolder, string branch, double initialBalance, int pinNum);

    // Member functions
    void displayAccountInfo();
    int verifyPin(int enteredPin);
    void deposit(double amount);
    int withdraw(double amount);
    string formatCurrency(double amount);
};

// Constructor definition outside the class
BankAccount::BankAccount(string accNum, string accHolder, string branch, double initialBalance, int pinNum) {
    accountNumber = accNum;
    accountHolder = accHolder;
    branchName = branch; // set branch name
    balance = initialBalance;
    pin = pinNum;
}

// Format currency without <iomanip>
string BankAccount::formatCurrency(double amount) {
    long long cents = (long long)(amount * 100 + 0.5); // rounding
    long long dollars = cents / 100;
    long long remainder = cents % 100;

    string result = "$";
    result += numToString(dollars);
    result += ".";
    if (remainder < 10) result += "0";
    result += numToString(remainder);

    return result;
}

// Display account info
void BankAccount::displayAccountInfo() {
    cout << "\n--- Account Information ---\n";
    cout << "Account Number: " << accountNumber << "\n";
    cout << "Account Holder: " << accountHolder << "\n";
    cout << "Branch: " << branchName << "\n"; // display branch
    cout << "Current Balance: " << formatCurrency(balance) << "\n";
}

// Verify PIN (return 1 if correct, 0 if wrong)
int BankAccount::verifyPin(int enteredPin) {
    if (enteredPin == pin) return 1;
    else return 0;
}

// Deposit money
void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "Deposit successful! New Balance: " << formatCurrency(balance) << "\n";
    } else {
        cout << "Invalid deposit amount!\n";
    }
}

// Withdraw money
int BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        cout << "Withdrawal successful! New Balance: " << formatCurrency(balance) << "\n";
        return 1;
    } else {
        cout << "Invalid amount or insufficient balance!\n";
        return 0;
    }
}

// Main Function
int main() {
    string accNum, accHolder, branch;
    double initialBalance;
    int pin;

    // Take account details from user
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter Account Holder Name: ";
    cin.ignore(); // to clear buffer
    getline(cin, accHolder);
    cout << "Enter Branch Name: ";
    getline(cin, branch);
    cout << "Enter Initial Balance: $";
    cin >> initialBalance;

    // Ensure PIN is valid
    do {
        cout << "Set a 4-digit PIN: ";
        cin >> pin;
        if (pin < 1000 || pin > 9999)
            cout << "PIN must be 4 digits!\n";
    } while (pin < 1000 || pin > 9999);

    // Create bank account
    BankAccount myAccount(accNum, accHolder, branch, initialBalance, pin);

    // PIN verification before accessing menu
    int enteredPin, attempts = 0, isAuthenticated = 0;
    while (attempts < 3 && isAuthenticated == 0) {
        cout << "\nEnter your 4-digit PIN: ";
        cin >> enteredPin;
        if (myAccount.verifyPin(enteredPin) == 1) {
            isAuthenticated = 1; // success
        } else {
            attempts++;
            cout << "Wrong PIN! Attempts left: " << 3 - attempts << "\n";
        }
    }

    if (isAuthenticated == 0) {
        cout << "Too many wrong attempts! Card blocked.\n";
        return 0;
    }

    // ATM Menu
    int choice;
    do {
        cout << "\n====== ATM MENU ======\n";
        cout << "1. View Account Information\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            myAccount.displayAccountInfo();
        }
        else if (choice == 2) {
            double amt;
            cout << "Enter deposit amount: $";
            cin >> amt;
            myAccount.deposit(amt);
        }
        else if (choice == 3) {
            double amt;
            cout << "Enter withdrawal amount: $";
            cin >> amt;
            myAccount.withdraw(amt);
        }
        else if (choice != 4) {
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 4);

    cout << "Thank you for banking with us!\n";
    return 0;
}

