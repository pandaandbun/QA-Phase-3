#pragma once
#include <iostream>
#include <string>
#include "../CurrentBankAccounts/bankaccounts.h"
#include "../BankAccountTransaction/bankaccounttransaction.h"
#include "../Login/login.h"

using namespace std;

// Paybill Transaction
class Paybill
{
private:
    BankAccount acc;
    CurrentBankAccounts &currAccounts;
    string companyName;
    User currUser;
    float amountPaid;

public:
    Paybill(CurrentBankAccounts &currAccounts, User currUser)
        : currAccounts(currAccounts)
    {
        this->currUser = currUser;
    }

    Transaction RunPaybill();
    Transaction SaveTransaction();

    int AdminName();
    int EnterAccountNumber();
    int SelectCompany();
    int EnterAmount();
    int UpdateAccount();
    int CheckAccountBalance();
};