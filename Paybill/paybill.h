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
    string companyName;
    float amountPaid;
    CurrentBankAccounts currAccounts;
    User currUser;

public:
    Paybill(CurrentBankAccounts currAccounts, User currUser);

    Transaction RunPaybill();
    Transaction SaveTransaction();

    int AdminName();
    int EnterAccountNumber();
    int SelectCompany();
    int EnterAmount();
};