#pragma once
#include <iostream>
#include <string>
#include "../CurrentBankAccounts/bankaccounts.h"
#include "../BankAccountTransaction/bankaccounttransaction.h"
#include "../Login/login.h"

using namespace std;

// ChangePlan Transaction
class ChangePlan
{
private:
    BankAccount acc;
    CurrentBankAccounts &currAccounts;
    User currUser;

public:
    ChangePlan(CurrentBankAccounts &currAccounts, User currUser)
        : currAccounts(currAccounts)
    {
        this->currUser = currUser;
    }

    Transaction RunChangePlan();
    Transaction SaveTransaction();

    int ChangeAccount();
    int EnterAccountHolderName();
    int EnterAccountNumber();
    int EnterAccountPlan();
    int CheckValidAccount();
    int CheckValidPlan();
};