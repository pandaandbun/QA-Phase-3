#include "deposit.h"

// Constructor accepts the current bank accounts instance
Deposit::Deposit(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

// Where everything come together
Transaction Deposit::RunDeposit()
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

    if (EnterAccountNumber())
    {
        if (EnterAmount())
        {
            if (UpdateAccount())
            {
                return SaveTransaction();
            }
        }
    }

    return temp;
}

// Let admin user enter their name
int Deposit::AdminName()
{
    cout << "Enter Your Name:" << endl;
    getline(cin >> ws, currUser.userName);

    cout << "Hi " << currUser.userName << endl;
    return 1;
}

// Where user enter their account number
int Deposit::EnterAccountNumber()
{
    cout << "Enter your account number:" << endl;
    cin >> acc.accountNumber;

    // Validation of account number and account name
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        string currAccStatus = currAccounts.accounts[i].accountStatus;

        if (acc.accountNumber == currAccNum && currUser.userName == currAccName)
        {
            currUser.bankAccountNumber = acc.accountNumber;
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

// Enter the amount you are depositing
int Deposit::EnterAmount()
{
    cout << "Enter the ammount to be deposit:" << endl;
    cin >> acc.accountBalance;

    cout << "Payment Successful!" << endl;
    return 1;
}

// Update account
int Deposit::UpdateAccount()
{
    cout << "Account Updated" << endl;
    currAccounts.UpdateAccount(acc);
    return 1;
}

// Save Transaction
Transaction Deposit::SaveTransaction()
{
    Transaction transaction(4, currUser.userName, currUser.bankAccountNumber, acc.accountBalance, "DR");

    cout << "Receipt Saved!" << endl;
    return transaction;
}