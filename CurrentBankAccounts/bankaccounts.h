#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip> 
using namespace std;

// BankAccount class
// Each instance of the class contains info of each bank account in the file
class BankAccount
{
public:
    int accountNumber;
    string accountHolderName;
    string accountStatus;
    float accountBalance;
};

// Current Bank Accounts manage many BankAccount instances
class CurrentBankAccounts
{
private:
    // string fileName = "currentbankaccountfile.txt";
    string fileName;

public:
    // Dynamic array
    vector<BankAccount> accounts;

    CurrentBankAccounts();
    CurrentBankAccounts(string fileName);

    int ReadCurrentBankAccounts();
    int LoadBankAccounts();

    void CreateAccount(BankAccount acc);
    void DeleteAccount(BankAccount acc);
    void DisableAccount(BankAccount acc);
    void UpdateAccount(BankAccount acc);
};