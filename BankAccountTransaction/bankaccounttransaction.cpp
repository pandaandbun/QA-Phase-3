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

// Write to file containing the transaction in that session
void BankAccountTransaction::CreateTransactionFile()
{
    // Get current time
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    string time = oss.str();

    // Set current time as file name
    ofstream out(time + ".txt");

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
            paddedAccountHolderName += "_";
        }
        replace(paddedAccountHolderName.begin(), paddedAccountHolderName.end(), ' ', '_');

        // Account Balance
        ostringstream ss2;
        ss2 << setw(8) << setfill('0') << setprecision(2) << fixed << currTransaction.fundsAmount;
        string paddedAccountBalance = ss2.str();

        // Transaction Code
        ostringstream ss3;
        ss3 << setw(2) << setfill('0') << currTransaction.transactionCode;
        string paddedTransactionCode = ss3.str();

        // Adding new account
        string newLine = paddedTransactionCode + "_" + paddedAccountHolderName + "_" + paddedAccountNumber + "_" + paddedAccountBalance + "_" + currTransaction.miscInfo;

        out << newLine << endl;
    }

    // End of line transaction code
    out << "00______________________00000_00000.00_00" << endl;
}