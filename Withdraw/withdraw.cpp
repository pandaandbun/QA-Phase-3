#include "withdraw.h"

// Constructor accepts the current bank accounts instance
Withdraw::Withdraw(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

// Where everything come together
Transaction Withdraw::RunWithdrawal()
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
            return SaveTransaction();
        }
    }

    return temp;
}

int Withdraw::AdminName()
{
    cout << "Enter Your Name:" << endl;
    getline(cin >> ws, currUser.userName);

    cout << "Hi " << currUser.userName << endl;
    return 1;
}

// Where user enter their account number
int Withdraw::EnterAccountNumber()
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
            currUser.bankAccountNumber = accountNum;
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

// Enter the amount you are withdrawing
int Withdraw::EnterAmount()
{
    cout << "Enter the amount to withdraw:" << endl;
    cin >> amountWithdraw;

    cout << "Payment Successful!" << endl;
    return 1;
}

// Save Transaction
Transaction Withdraw::SaveTransaction()
{
    Transaction transaction(1, currUser.userName, currUser.bankAccountNumber, amountWithdraw, "00");

    cout << "Receipt Saved!" << endl;
    return transaction;
}
