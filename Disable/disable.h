#pragma once
#include <iostream>
#include <string>
#include "../CurrentBankAccounts/bankaccounts.h"
#include "../BankAccountTransaction/bankaccounttransaction.h"
#include "../Login/login.h"

using namespace std;

// Disable Transaction
class Disable
{
private:
    BankAccount acc;
    CurrentBankAccounts &currAccounts;
    User currUser;

public:
    Disable(CurrentBankAccounts &currAccounts, User currUser)
        : currAccounts(currAccounts)
    {
        this->currUser = currUser;
    }

    Transaction RunDisable();
    Transaction SaveTransaction();

    int DisableAccount();
    int EnterAccountHolderName();
    int EnterAccountNumber();
    int CheckValidAccount();
};