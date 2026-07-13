#include <iostream>
#include <vector>
#include <string>
#include <windows.h>   // For console colors (SetConsoleTextAttribute)
#include <iomanip>
using namespace std;

// ---------- Color Codes ----------
#define COLOR_RED     4
#define COLOR_GREEN   10
#define COLOR_YELLOW  14
#define COLOR_CYAN    11
#define COLOR_WHITE   15
#define COLOR_MAGENTA 13

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor()
{
    setColor(COLOR_WHITE);
}

// ---------- Transaction Class ----------
class Transaction
{
public:
    string type;
    double amount;

    Transaction(string t, double a)
    {
        type = t;
        amount = a;
    }

    void display()
    {
        if (type == "Deposit" || type == "Transfer Received")
            setColor(COLOR_GREEN);
        else
            setColor(COLOR_RED);

        cout << "  " << left << setw(20) << type << ": Rs. " << amount << endl;
        resetColor();
    }
};

// ---------- Account Class ----------
class Account
{
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo = 0, double initialBalance = 0)
    {
        accountNumber = accNo;
        balance = initialBalance;
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    double getBalance()
    {
        return balance;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            setColor(COLOR_RED);
            cout << "Invalid Amount!\n";
            resetColor();
            return;
        }

        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));

        setColor(COLOR_GREEN);
        cout << "Deposit Successful!\n";
        cout << "Current Balance: Rs. " << balance << endl;
        resetColor();
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            setColor(COLOR_RED);
            cout << "Invalid Amount!\n";
            resetColor();
            return;
        }

        if (amount > balance)
        {
            setColor(COLOR_RED);
            cout << "Insufficient Balance!\n";
            resetColor();
            return;
        }

        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));

        setColor(COLOR_GREEN);
        cout << "Withdrawal Successful!\n";
        cout << "Current Balance: Rs. " << balance << endl;
        resetColor();
    }

    void transfer(Account &receiver, double amount)
    {
        if (amount <= 0)
        {
            setColor(COLOR_RED);
            cout << "Invalid Amount!\n";
            resetColor();
            return;
        }

        if (amount > balance)
        {
            setColor(COLOR_RED);
            cout << "Insufficient Balance!\n";
            resetColor();
            return;
        }

        balance -= amount;
        receiver.balance += amount;

        transactions.push_back(Transaction("Transfer Sent", amount));
        receiver.transactions.push_back(Transaction("Transfer Received", amount));

        setColor(COLOR_GREEN);
        cout << "Transfer Successful!\n";
        resetColor();
    }

    void showTransactions()
    {
        setColor(COLOR_CYAN);
        cout << "\nTransaction History\n";
        cout << "-------------------\n";
        resetColor();

        if (transactions.empty())
        {
            setColor(COLOR_YELLOW);
            cout << "No Transactions Found.\n";
            resetColor();
            return;
        }

        for (size_t i = 0; i < transactions.size(); i++)
        {
            transactions[i].display();
        }
    }

    void displayAccount()
    {
        setColor(COLOR_CYAN);
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Balance: Rs. " << balance << endl;
        resetColor();
    }
};

// ---------- Customer Class ----------
class Customer
{
private:
    int customerID;
    string name;
    Account account;

public:
    Customer(int id = 0, string n = "", int accNo = 0, double balance = 0)
        : account(accNo, balance)
    {
        customerID = id;
        name = n;
    }

    int getCustomerID()
    {
        return customerID;
    }

    string getName()
    {
        return name;
    }

    Account &getAccount()
    {
        return account;
    }

    void displayCustomer()
    {
        setColor(COLOR_MAGENTA);
        cout << "\nCustomer ID: " << customerID << endl;
        cout << "Customer Name: " << name << endl;
        resetColor();
        account.displayAccount();
    }
};

// ---------- Admin Login System ----------
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

bool adminLogin()
{
    string username, password;
    int attempts = 3;

    while (attempts > 0)
    {
        setColor(COLOR_YELLOW);
        cout << "\n===== ADMIN LOGIN =====\n";
        resetColor();

        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
        {
            setColor(COLOR_GREEN);
            cout << "\nLogin Successful! Welcome, Admin.\n";
            resetColor();
            return true;
        }
        else
        {
            attempts--;
            setColor(COLOR_RED);
            cout << "Incorrect Username or Password! Attempts left: " << attempts << endl;
            resetColor();
        }
    }

    setColor(COLOR_RED);
    cout << "\nToo many failed attempts. Exiting Program.\n";
    resetColor();
    return false;
}

// ---------- Helper: Find Customer by ID ----------
Customer* findCustomer(vector<Customer> &customers, int id)
{
    for (size_t i = 0; i < customers.size(); i++)
    {
        if (customers[i].getCustomerID() == id)
            return &customers[i];
    }
    return nullptr;
}

void printMenu()
{
    setColor(COLOR_CYAN);
    cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
    resetColor();
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Transfer Funds\n";
    cout << "4. View Account Details\n";
    cout << "5. View Transaction History\n";
    cout << "6. Add New Customer\n";
    cout << "7. Exit\n";
    setColor(COLOR_YELLOW);
    cout << "Enter Choice: ";
    resetColor();
}

int main()
{
    setColor(COLOR_CYAN);
    cout << "===================================\n";
    cout << "   WELCOME TO BANK MANAGEMENT APP   \n";
    cout << "===================================\n";
    resetColor();

    // Admin must log in before using the system
    if (!adminLogin())
    {
        return 0;
    }

    vector<Customer> customers;
    customers.push_back(Customer(101, "Ali", 1001, 5000));
    customers.push_back(Customer(102, "Sara", 1002, 3000));

    int choice;
    double amount;
    int custID, targetID;

    do
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter Customer ID: ";
            cin >> custID;
            Customer* c = findCustomer(customers, custID);
            if (!c) { setColor(COLOR_RED); cout << "Customer Not Found!\n"; resetColor(); break; }

            cout << "Enter Deposit Amount: ";
            cin >> amount;
            c->getAccount().deposit(amount);
            break;
        }

        case 2:
        {
            cout << "Enter Customer ID: ";
            cin >> custID;
            Customer* c = findCustomer(customers, custID);
            if (!c) { setColor(COLOR_RED); cout << "Customer Not Found!\n"; resetColor(); break; }

            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            c->getAccount().withdraw(amount);
            break;
        }

        case 3:
        {
            cout << "Enter Sender Customer ID: ";
            cin >> custID;
            cout << "Enter Receiver Customer ID: ";
            cin >> targetID;

            Customer* sender = findCustomer(customers, custID);
            Customer* receiver = findCustomer(customers, targetID);

            if (!sender || !receiver)
            {
                setColor(COLOR_RED);
                cout << "Invalid Sender or Receiver ID!\n";
                resetColor();
                break;
            }

            cout << "Enter Transfer Amount: ";
            cin >> amount;
            sender->getAccount().transfer(receiver->getAccount(), amount);
            break;
        }

        case 4:
        {
            cout << "Enter Customer ID: ";
            cin >> custID;
            Customer* c = findCustomer(customers, custID);
            if (!c) { setColor(COLOR_RED); cout << "Customer Not Found!\n"; resetColor(); break; }
            c->displayCustomer();
            break;
        }

        case 5:
        {
            cout << "Enter Customer ID: ";
            cin >> custID;
            Customer* c = findCustomer(customers, custID);
            if (!c) { setColor(COLOR_RED); cout << "Customer Not Found!\n"; resetColor(); break; }
            c->getAccount().showTransactions();
            break;
        }

        case 6:
        {
            int id, accNo;
            string name;
            double initBalance;

            cout << "Enter New Customer ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Initial Balance: ";
            cin >> initBalance;

            customers.push_back(Customer(id, name, accNo, initBalance));

            setColor(COLOR_GREEN);
            cout << "Customer Added Successfully!\n";
            resetColor();
            break;
        }

        case 7:
            setColor(COLOR_CYAN);
            cout << "Thank You for Using Our Bank!\n";
            resetColor();
            break;

        default:
            setColor(COLOR_RED);
            cout << "Invalid Choice!\n";
            resetColor();
        }

    } while (choice != 7);

    return 0;
}