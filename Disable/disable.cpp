#include "disable.h"

// Constructor
Disable::Disable(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

// Where everything is run
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

// Enter Account Holder Name Prompt
int Disable::EnterAccountHolderName()
{
    cout << "Enter Account Holder Name:" << endl;
    getline(cin >> ws, acc.accountHolderName);
    return 1;
}

// Enter Account number
int Disable::EnterAccountNumber()
{
    cout << "Enter Account Number:" << endl;
    cin >> acc.accountNumber;
    return 1;
}

// Check if the entered account is valid
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

// Disable the specified account
int Disable::DisableAccount()
{
    cout << "Account Disable" << endl;
    currAccounts.DisableAccount(acc);
    return 1;
}

// Create a record of this transaction
Transaction Disable::SaveTransaction()
{
    Transaction transaction(7, acc.accountHolderName, acc.accountNumber, 0, "00");
    cout << "Receipt Saved!" << endl;
    return transaction;
}