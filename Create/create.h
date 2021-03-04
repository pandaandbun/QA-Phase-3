#pragma once
#include <iostream>
#include <string>
#include "../CurrentBankAccounts/bankaccounts.h"
#include "../BankAccountTransaction/bankaccounttransaction.h"
#include "../Login/login.h"

using namespace std;

// Create Transaction
class Create
{
private:
    BankAccount acc;
    CurrentBankAccounts currAccounts;
    User currUser;

public:
    Create(CurrentBankAccounts currAccounts, User currUser);

    Transaction RunCreate();
    Transaction SaveTransaction();

    int CreateAccount();
    int EnterAccountHolderName();
    int EnterAccountBalance();
    int CheckValidAccountBalance(float newAccountBalance);
    int GenerateAccountNumber();
};