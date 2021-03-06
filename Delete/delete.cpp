#include "delete.h"

// Constructor
Delete::Delete(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

// Where everything is run
Transaction Delete::RunDelete()
{
    if (currUser.isAdmin)
    {

        if (EnterAccountHolderName())
        {

            if (EnterAccountNumber())
            {
                if (CheckValidAccount())
                {
                    if (CheckValidBalance())
                    {
                        DeleteAccount();
                        return SaveTransaction();
                    }
                }
            }
        }
    }

    Transaction temp;
    return temp;
}

// Enter account holder name
int Delete::EnterAccountHolderName()
{
    cout << "Enter Account Holder Name:" << endl;
    getline(cin >> ws, acc.accountHolderName);
    return 1;
}

// Enter account number
int Delete::EnterAccountNumber()
{

    cout << "Enter Account Number:" << endl;
    cin >> acc.accountNumber;
    return 1;
}

// Check if account is valid
int Delete::CheckValidAccount()
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

int Delete::CheckValidBalance()
{
    if (acc.accountBalance == 0)
    {
        cout << "Invalid Balance" << endl;
        return 1;
    }
    else{
        return 0;
    }
}

// Delete account
int Delete::DeleteAccount()
{
    cout << "Account Deleted" << endl;
    currAccounts.DeleteAccount(acc);
    return 1;
}

// Save this transaction
Transaction Delete::SaveTransaction()
{
    Transaction transaction(6, acc.accountHolderName, acc.accountNumber, 0, "00");
    cout << "Receipt Saved!" << endl;
    return transaction;
}