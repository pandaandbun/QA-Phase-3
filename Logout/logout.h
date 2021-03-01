#pragma once
#include <iostream>
#include <string>
#include "../BankAccountTransaction/bankaccounttransaction.h"

using namespace std;

// Logout Transaction
class Logout
{
private:
    BankAccountTransaction currTransaction;
public:
    Logout(BankAccountTransaction currTransaction);
    int RunLogout();
};