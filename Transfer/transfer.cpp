#include "transfer.h"

// Constructor accepts the current bank accounts instance
Transfer::Transfer(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

// Where everything come together
Transaction Transfer::RunTransfer()
{
    Transaction temp;

    // Check if the user is admin
    // Check if the admin enter a valid name
    if (currUser.isAdmin)
    {
        if (!AdminName())
        {
            return temp;
        }
    }

    if (FromAccountNumber())
    {
        if (ToAccountNumber())
        {
            if (EnterAmount())
            {
                return SaveTransaction();
            }
        }
    }

    return temp;
}

int Transfer::AdminName()
{
    cout << "Enter Your Name:" << endl;
    getline(cin >> ws, currUser.userName);

    cout << "Hi " << currUser.userName << endl;
    return 1;
}

// Where user enter their account number
int Transfer::FromAccountNumber()
{
    int accountNum;

    cout << "Enter your account number:" << endl;
    cin >> accountNum;

    // Validation for account number and name
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        string currAccStatus = currAccounts.accounts[i].accountStatus;

        if (accountNum == currAccNum && currUser.userName == currAccName)
        {
            fromAccountNumber = accountNum;
            if (currAccStatus == "D")
            {
                cout << "Account Disabled!" << endl;
                return 0;
            }
            cout << "Account Found!" << endl;
            return 1;
        }
    }

    cout << "Acount Not Found" << endl;
    return 0;
}

// Enter the account number to transfer money to
int Transfer::ToAccountNumber()
{
    int accountNum;

    cout << "Enter the account number you want to transfer to:" << endl;
    cin >> accountNum;

    // Validate Account Number
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccStatus = currAccounts.accounts[i].accountStatus;

        if (accountNum == currAccNum)
        {
            toAccountNumber = accountNum;
            if (currAccStatus == "D")
            {
                cout << "Account Disabled!" << endl;
                return 0;
            }
            cout << "Account Found!" << endl;
            return 1;
        }
    }

    cout << "Acount Not Found" << endl;
    return 0;
}

// Enter the amount you are transfering
int Transfer::EnterAmount()
{
    cout << "Enter the amount of money to transfer:" << endl;
    cin >> transferAmount;

    cout << "Transfer Successful!" << endl;
    return 1;
}

// Save Transaction
Transaction Transfer::SaveTransaction()
{
    Transaction transaction(2, currUser.userName, fromAccountNumber, transferAmount, "00");

    cout << "Receipt Saved!" << endl;
    return transaction;
}