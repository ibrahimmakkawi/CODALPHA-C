#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Class to handle individual transactions
class Transaction {
private:
    string type;
    double amount;
    string date;
public:
    Transaction(string type, double amount, string date)
        : type(type), amount(amount), date(date) {}

    void printTransaction() const {
        cout << left << setw(10) << type 
             << left << setw(10) << amount 
             << left << setw(15) << date << endl;
    }
};

// Class to manage customer accounts
class Account {
private:
    string accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(string accNum, double initialBalance = 0.0)
        : accountNumber(accNum), balance(initialBalance) {}

    // Deposit money into the account
    void deposit(double amount, string date) {
        balance += amount;
        transactions.emplace_back("Deposit", amount, date);
    }

    // Withdraw money from the account
    bool withdraw(double amount, string date) {
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdraw", amount, date);
        return true;
    }

    // Transfer money to another account
    bool transfer(Account &toAccount, double amount, string date) {
        if (withdraw(amount, date)) {
            toAccount.deposit(amount, date);
            transactions.emplace_back("Transfer", amount, date);
            return true;
        }
        return false;
    }

    // Display account balance
    void displayBalance() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Display recent transactions
    void displayTransactions() const {
        cout << "Recent Transactions for Account: " << accountNumber << endl;
        cout << left << setw(10) << "Type" 
             << left << setw(10) << "Amount" 
             << left << setw(15) << "Date" << endl;
        for (const auto &transaction : transactions) {
            transaction.printTransaction();
        }
    }

    // Get account number for comparison
    string getAccountNumber() const {
        return accountNumber;
    }
};

// Class to manage bank customers
class Customer {
private:
    string name;
    string customerID;
    vector<Account> accounts;

public:
    Customer(string name, string id) : name(name), customerID(id) {}

    // Add an account to the customer
    void addAccount(const Account &account) {
        accounts.push_back(account);
    }

    // Get customer ID
    string getID() const {
        return customerID;
    }

    // Display customer details and accounts
    void displayCustomerInfo() const {
        cout << "Customer Name: " << name << endl;
        cout << "Customer ID: " << customerID << endl;
        for (const auto &account : accounts) {
            account.displayBalance();
        }
    }

    // Perform banking operations
    Account* getAccount(const string &accNum) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accNum) {
                return &account;
            }
        }
        return nullptr;
    }
};

// Class to manage the banking system
class Bank {
private:
    vector<Customer> customers;

public:
    // Add a customer to the bank
    void addCustomer(const Customer &customer) {
        customers.push_back(customer);
    }

    // Find a customer by ID
    Customer* findCustomer(const string &id) {
        for (auto &customer : customers) {
            if (customer.getID() == id) {
                return &customer;
            }
        }
        return nullptr;
    }

    // Display all customers in the bank
    void displayAllCustomers() const {
        for (const auto &customer : customers) {
            customer.displayCustomerInfo();
            cout << endl;
        }
    }
};

// Function prototypes
void createCustomer(Bank &bank);
void createAccount(Customer &customer);
void performTransactions(Customer &customer);

int main() {
    Bank bank;
    int choice;
    string customerID;

    do {
        cout << "\n*** Banking System Menu ***" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Add Account to Customer" << endl;
        cout << "3. Perform Transactions" << endl;
        cout << "4. Display All Customers" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createCustomer(bank);
            break;
        case 2:
            cout << "Enter Customer ID: ";
            cin >> customerID;
            {
                Customer *customer = bank.findCustomer(customerID);
                if (customer) {
                    createAccount(*customer);
                } else {
                    cout << "Customer not found!" << endl;
                }
            }
            break;
        case 3:
            cout << "Enter Customer ID: ";
            cin >> customerID;
            {
                Customer *customer = bank.findCustomer(customerID);
                if (customer) {
                    performTransactions(*customer);
                } else {
                    cout << "Customer not found!" << endl;
                }
            }
            break;
        case 4:
            bank.displayAllCustomers();
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}

// Function to create a new customer
void createCustomer(Bank &bank) {
    string name, id;
    cout << "Enter Customer Name: ";
    cin >> name;
    cout << "Enter Customer ID: ";
    cin >> id;

    Customer customer(name, id);
    bank.addCustomer(customer);

    cout << "Customer added successfully!" << endl;
}

// Function to create a new account for a customer
void createAccount(Customer &customer) {
    string accNum;
    double initialBalance;
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter Initial Balance: ";
    cin >> initialBalance;

    Account account(accNum, initialBalance);
    customer.addAccount(account);

    cout << "Account created successfully!" << endl;
}

// Function to perform transactions
void performTransactions(Customer &customer) {
    string accNum, date;
    double amount;
    int choice;

    cout << "Enter Account Number: ";
    cin >> accNum;

    Account *account = customer.getAccount(accNum);
    if (!account) {
        cout << "Account not found!" << endl;
        return;
    }

    cout << "\n*** Transaction Menu ***" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Display Balance" << endl;
    cout << "4. Display Transactions" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Enter amount to deposit: ";
        cin >> amount;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;
        account->deposit(amount, date);
        cout << "Deposit successful!" << endl;
        break;
    case 2:
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;
        if (account->withdraw(amount, date)) {
            cout << "Withdrawal successful!" << endl;
        } else {
            cout << "Withdrawal failed!" << endl;
        }
        break;
    case 3:
        account->displayBalance();
        break;
    case 4:
        account->displayTransactions();
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}
