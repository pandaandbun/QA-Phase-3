#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../CurrentBankAccounts/bankaccounts.h"
using namespace std;

// Transaction class contain the info of each transaction like
// transaction code, acount name, account number, amount of money involve in the transaction, misc info
class Transaction
{
public:
    int transactionCode;
    string accountHolderName;
    int bankAccountNumber;
    float fundsAmount;
    string miscInfo;
    Transaction();
    Transaction(int transactionCode, string accountHolderName, int bankAccountNumber, float fundsAmount, string miscInfo);
};

// Bank account transaction class is basically a compilation of Transaction instance in a single session
class BankAccountTransaction
{
private:
    string fileName;

public:
    // Dynamic array
    vector<Transaction> transactions;

    BankAccountTransaction();
    BankAccountTransaction(string fileName);
    void CreateTransactionFile();
};