#include "create.h"

Create::Create(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

Transaction Create::RunCreate()
{
    if (currUser.isAdmin)
    {

        if (EnterAccountHolderName())
        {

            if (EnterAccountBalance())
            {

                if (GenerateAccountNumber())
                {
                    CreateAccount();
                    return SaveTransaction();
                }
            }
        }
    }

    Transaction temp;
    return temp;
}

int Create::EnterAccountHolderName()
{
    cout << "Enter Account Holder Name:" << endl;
    getline(cin >> ws, acc.accountHolderName);
    return 1;
}

int Create::EnterAccountBalance()
{

    cout << "Enter Account Balance:" << endl;
    cin >> acc.accountBalance;
    return 1;
}

int Create::GenerateAccountNumber()
{
    int lastAccNum = currAccounts.accounts[currAccounts.accounts.size() - 1].accountNumber;
    acc.accountNumber = lastAccNum + 1;
    return 1;
}

int Create::CreateAccount()
{
    cout << "Account Created" << endl;
    acc.accountStatus = "A";
    currAccounts.CreateAccount(acc);
    return 1;
}

Transaction Create::SaveTransaction()
{
    Transaction transaction(5, acc.accountHolderName, acc.accountNumber, acc.accountBalance, "00");
    cout << "Receipt Saved!" << endl;
    return transaction;
}