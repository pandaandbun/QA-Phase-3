#pragma once
#include <iostream>
#include <string>
#include "../CurrentBankAccounts/bankaccounts.h"
#include "../BankAccountTransaction/bankaccounttransaction.h"
#include "../Login/login.h"

using namespace std;

// Delete Transaction
class Delete
{
private:
    BankAccount acc;
    CurrentBankAccounts currAccounts;
    User currUser;

public:
    Delete(CurrentBankAccounts currAccounts, User currUser);

    Transaction RunDelete();
    Transaction SaveTransaction();

    int DeleteAccount();
    int EnterAccountHolderName();
    int EnterAccountNumber();
    int CheckValidAccount();
};