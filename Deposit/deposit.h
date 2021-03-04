#pragma once
#include <iostream>
#include <string>
#include "../CurrentBankAccounts/bankaccounts.h"
#include "../BankAccountTransaction/bankaccounttransaction.h"
#include "../Login/login.h"

// Deposit Transaction
class Deposit
{
private:
    BankAccount acc;
    CurrentBankAccounts currAccounts;
    User currUser;
    float depositAmount;

public:
    Deposit(CurrentBankAccounts currAccounts, User currUser);

    Transaction RunDeposit();
    Transaction SaveTransaction();

    int AdminName();
    int EnterAccountNumber();
    int EnterAmount();
    int UpdateAccount();
};