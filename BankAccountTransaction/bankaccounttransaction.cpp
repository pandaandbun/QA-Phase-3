#include "bankaccounttransaction.h"

// Default Constructor for Transaction
Transaction::Transaction(){};

// Constructor for Transaction
// Take transaction code, account name, account number, amount of money involved and misc info
Transaction::Transaction(int transactionCode, string accountHolderName, int bankAccountNumber, float fundsAmount, string miscInfo)
{
    this->transactionCode = transactionCode;
    this->accountHolderName = accountHolderName;
    this->bankAccountNumber = bankAccountNumber;
    this->fundsAmount = fundsAmount;
    this->miscInfo = miscInfo;
}

// -----------------------------------------------
// Default Constructor
BankAccountTransaction::BankAccountTransaction() {}

// Constructor
BankAccountTransaction::BankAccountTransaction(string fileName)
{
    this->fileName = fileName;
}

// Write to file containing the transaction in that session
int BankAccountTransaction::CreateTransactionFile()
{
    // Set current time as file name
    ofstream out(fileName);

    // Write to file
    for (int i = 0; i < transactions.size(); i++)
    {
        // Transaction Code
        Transaction currTransaction = transactions[i];

        // Account Number
        ostringstream ss;
        ss << setw(5) << setfill('0') << currTransaction.bankAccountNumber;
        string paddedAccountNumber = ss.str();

        // Account Holder Name
        string paddedAccountHolderName = currTransaction.accountHolderName;
        int padLength = 20 - currTransaction.accountHolderName.size();
        for (int i = 0; i < padLength; i++)
        {
            paddedAccountHolderName += " ";
        }

        // Account Balance
        ostringstream ss2;
        ss2 << setw(8) << setfill('0') << setprecision(2) << fixed << currTransaction.fundsAmount;
        string paddedAccountBalance = ss2.str();

        // Transaction Code
        ostringstream ss3;
        ss3 << setw(2) << setfill('0') << currTransaction.transactionCode;
        string paddedTransactionCode = ss3.str();

        // Adding new account
        string newLine = paddedTransactionCode + " " + paddedAccountHolderName + " " + paddedAccountNumber + " " + paddedAccountBalance + " " + currTransaction.miscInfo;

        out << newLine << endl;
    }

    // End of line transaction code
    out << "00                      00000 00000.00 00" << endl;

    return 1;
}