#pragma once
#include <iostream>
#include <string>
#include "../CurrentBankAccounts/bankaccounts.h"
#include "../BankAccountTransaction/bankaccounttransaction.h"
#include "../Login/login.h"

using namespace std;

// Fulfill the Withdrawal Transaction
class Withdraw
{
private:
    BankAccount acc;
    CurrentBankAccounts currAccounts;
    User currUser;
    float amountWithdraw;

public:
    Withdraw(CurrentBankAccounts currAccounts, User currUser);

    Transaction RunWithdrawal();
    Transaction SaveTransaction();

    int AdminName();
    int EnterAccountNumber();
    int EnterAmount();
    int UpdateAccount();
};
