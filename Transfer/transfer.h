#pragma once
#include <iostream>
#include <string>
#include "../CurrentBankAccounts/bankaccounts.h"
#include "../BankAccountTransaction/bankaccounttransaction.h"
#include "../Login/login.h"

using namespace std;

// Transfer Tranasction
class Transfer
{
private:
    BankAccount fromAcc;
    BankAccount toAcc;
    int fromAccountNumber;
    int toAccountNumber;
    float transferAmount;
    CurrentBankAccounts& currAccounts;
    User currUser;

public:
    Transfer(CurrentBankAccounts& currAccounts, User currUser)
        : currAccounts(currAccounts)
    {
        this->currUser = currUser;
    }

    Transaction RunTransfer();
    Transaction SaveTransaction();

    int AdminName();
    int isValidName(string name);
    int FromAccountNumber();
    int ToAccountNumber();
    int EnterAmount();
    int UpdateAccount();
};
