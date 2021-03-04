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
    cout << "Enter your account number:" << endl;
    cin >> acc.accountNumber;

    // Validation for account number and name
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        string currAccStatus = currAccounts.accounts[i].accountStatus;
        float currAccBal = currAccounts.accounts[i].accountBalance;

        if (acc.accountNumber == currAccNum && currUser.userName == currAccName)
        {
            currUser.bankAccountNumber = acc.accountNumber;
            if (currAccStatus == "D")
            {
                cout << "Account Disabled!" << endl;
                return 0;
            }
            cout << "Account Found!" << endl;
            acc.accountHolderName = currAccName;
            acc.accountStatus = currAccStatus;
            acc.accountBalance = currAccBal;
            return 1;
        }
    }

    cout << "Account Not Found" << endl;
    return 0;
}

// Enter the amount you are withdrawing
int Withdraw::EnterAmount()
{
    cout << "Enter the amount to withdraw:" << endl;
    cin >> amountWithdraw;

    if (amountWithdraw < 0) {
        cout << "Error: Value Error - cannot withdraw less than $0!" << endl;
        return 0;
    } else if(amountWithdraw > 99999.99) {
        cout << "Error: Value Error - withdraw value cannot exceed $99999.00!" << endl;
        return 0;
    }
    else if (amountWithdraw > 500.00 && !currUser.isAdmin) {
        cout << "ERROR: Value Error - withdraw more than $500!" << endl;
        return 0;
    } else if (amountWithdraw > acc.accountBalance) {
        cout << "ERROR: Value Error - withdraw value exceeds account balance!" << endl;
        return 0;
    }
    else {
        acc.accountBalance -= amountWithdraw;
        UpdateAccount();
        cout << "Payment Successful!" << endl;
    }

    return 1;
}

int Withdraw::UpdateAccount()
{
    cout << "Account Updated" << endl;
    currAccounts.UpdateAccount(acc);
    return 1;
}

// Save Transaction
Transaction Withdraw::SaveTransaction()
{
    Transaction transaction(1, currUser.userName, currUser.bankAccountNumber, amountWithdraw, "CR");

    cout << "Receipt Saved!" << endl;
    return transaction;
}
