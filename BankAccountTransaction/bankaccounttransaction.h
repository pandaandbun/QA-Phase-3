#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
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
public:
    // Dynamic array
    vector<Transaction> transactions;
    void CreateTransactionFile();
};