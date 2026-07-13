#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Transaction Class
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
        cout << type << " : Rs. " << amount << endl;
    }
};

// Account Class
class Account
{
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo, double initialBalance = 0)
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
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));

        cout << "Deposit Successful!\n";
        cout << "Current Balance: Rs. " << balance << endl;
    }

    void withdraw(double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient Balance!\n";
            return;
        }

        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));

        cout << "Withdrawal Successful!\n";
        cout << "Current Balance: Rs. " << balance << endl;
    }

    void transfer(Account &receiver, double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient Balance!\n";
            return;
        }

        balance -= amount;
        receiver.balance += amount;

        transactions.push_back(Transaction("Transfer Sent", amount));
        receiver.transactions.push_back(Transaction("Transfer Received", amount));

        cout << "Transfer Successful!\n";
    }

    void showTransactions()
    {
        cout << "\nTransaction History\n";
        cout << "-------------------\n";

        if (transactions.empty())
        {
            cout << "No Transactions Found.\n";
            return;
        }

        for (int i = 0; i < transactions.size(); i++)
        {
            transactions[i].display();
        }
    }

    void displayAccount()
    {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

// Customer Class
class Customer
{
private:
    int customerID;
    string name;
    Account account;

public:
    Customer(int id, string n, int accNo, double balance)
        : account(accNo, balance)
    {
        customerID = id;
        name = n;
    }

    Account &getAccount()
    {
        return account;
    }

    void displayCustomer()
    {
        cout << "\nCustomer ID: " << customerID << endl;
        cout << "Customer Name: " << name << endl;
        account.displayAccount();
    }
};

int main()
{
    Customer c1(101, "Ali", 1001, 5000);
    Customer c2(102, "Sara", 1002, 3000);

    int choice;
    double amount;

    do
    {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Transfer Funds\n";
        cout << "4. View Account Details\n";
        cout << "5. View Transaction History\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            c1.getAccount().deposit(amount);
            break;

        case 2:
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            c1.getAccount().withdraw(amount);
            break;

        case 3:
            cout << "Enter Transfer Amount: ";
            cin >> amount;
            c1.getAccount().transfer(c2.getAccount(), amount);
            break;

        case 4:
            c1.displayCustomer();
            break;

        case 5:
            c1.getAccount().showTransactions();
            break;

        case 6:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}