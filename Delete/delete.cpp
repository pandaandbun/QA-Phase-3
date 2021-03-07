#include "delete.h"

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
    getline(cin >> ws, currUser.userName);

    // Check if name is valid
    if (currUser.isValidName(currUser.userName))
    {
        acc.accountHolderName = currUser.userName;
        return 1;
    }

    cout << "Name is invalid" << endl;
    return 0;
}

// Enter account number
int Delete::EnterAccountNumber()
{

    cout << "Enter Account Number:" << endl;
    cin >> currUser.bankAccountNumber;

    // Check if account number is valid
    if (currUser.isValidAccountNumber(currUser.bankAccountNumber))
    {
        acc.accountNumber = currUser.bankAccountNumber;
        return 1;
    }

    cout << "Account number is invalid" << endl;
    return 0;
}

// Check if account is valid
int Delete::CheckValidAccount()
{
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        float currBalance = currAccounts.accounts[i].accountBalance;

        if (acc.accountNumber == currAccNum && acc.accountHolderName == currAccName)
        {
            if (currAccounts.accounts[i].accountStatus == "D")
            {
                cout << "Account Disabled!" << endl;
                return 0;
            }

            cout << "Account Found!" << endl;
            acc.accountBalance = currBalance;
            return 1;
        }
    }

    cout << "Account Not Found" << endl;
    return 0;
}

int Delete::CheckValidBalance()
{
    if (acc.accountBalance > 0)
    {
        cout << "Invalid Balance" << endl;
        return 0;
    }

    return 1;
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
    Transaction transaction(6, currUser.userName, currUser.bankAccountNumber, 0, "00");
    cout << "Receipt Saved!" << endl;
    return transaction;
}