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
            return SaveTransaction();
        }
    }

    return temp;
}

// Let admin user enter their name
int Deposit::AdminName()
{
    cout << "Enter Your Name:" << endl;
    getline(cin >> ws, currUser.userName);

    // Check if name is valid
    if (currUser.isValidName(currUser.userName))
    {
        cout << "Hi " << currUser.userName << endl;
        return 1;
    }

    cout << "Name is invalid" << endl;
    return 0;
}

// Where user enter their account number
int Deposit::EnterAccountNumber()
{
    cout << "Enter your account number:" << endl;
    cin >> acc.accountNumber;

    // Check if account number is valid
    if (!currUser.isValidAccountNumber(acc.accountNumber))
    {
        cout << "Account number is invalid" << endl;
        return 0;
    }

    // Validation of account number and account name
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        string currAccStatus = currAccounts.accounts[i].accountStatus;
        float currAccBal = currAccounts.accounts[i].accountBalance;

        if (acc.accountNumber == currAccNum && currUser.userName == currAccName)
        {
            if (currAccStatus == "D" || currAccStatus == "C")
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

// Enter the amount you are depositing
int Deposit::EnterAmount()
{
    cout << "Enter the amount to be deposit:" << endl;
    cin >> depositAmount;

    if (depositAmount < 0)
    {
        cout << "Error: Value Error - cannot deposit less than $0!" << endl;
        return 0;
    }
    else if (depositAmount > 99999.00)
    {
        cout << "Error: Value Error - deposit value cannot exceed $99999.00!" << endl;
        return 0;
    }

    acc.accountBalance += depositAmount;
    UpdateAccount();
    cout << "Payment Successful!" << endl;
    return 1;
}

// Update account
int Deposit::UpdateAccount()
{
    cout << "Account Updated" << endl;
    // currAccounts.UpdateAccount(acc);
    return 1;
}

// Save Transaction
Transaction Deposit::SaveTransaction()
{
    Transaction transaction(4, currUser.userName, acc.accountNumber, depositAmount, "DR");

    cout << "Receipt Saved!" << endl;
    return transaction;
}
