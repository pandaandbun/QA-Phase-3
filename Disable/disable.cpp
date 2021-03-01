#include "disable.h"

Disable::Disable(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

Transaction Disable::RunDisable()
{
    if (currUser.isAdmin)
    {

        if (EnterAccountHolderName())
        {

            if (EnterAccountNumber())
            {
                if (CheckValidAccount())
                {
                    DisableAccount();
                    return SaveTransaction();
                }
            }
        }
    }

    Transaction temp;
    return temp;
}

int Disable::EnterAccountHolderName()
{
    cout << "Enter Account Holder Name:" << endl;
    getline(cin >> ws, acc.accountHolderName);
    return 1;
}

int Disable::EnterAccountNumber()
{
    cout << "Enter Account Number:" << endl;
    cin >> acc.accountNumber;
    return 1;
}

int Disable::CheckValidAccount()
{
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;

        if (acc.accountNumber == currAccNum && acc.accountHolderName == currAccName)
        {
            cout << "Account Found!" << endl;
            return 1;
        }
    }

    cout << "Account Not Found" << endl;
    return 0;
}

int Disable::DisableAccount()
{
    cout << "Account Disable" << endl;
    currAccounts.DisableAccount(acc);
    return 1;
}

Transaction Disable::SaveTransaction()
{
    Transaction transaction(7, acc.accountHolderName, acc.accountNumber, 0, "00");
    cout << "Receipt Saved!" << endl;
    return transaction;
}