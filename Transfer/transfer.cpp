#include "transfer.h"

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
                if (CheckAccountBalance())
                {
                    return SaveTransaction();
                }
            }
        }
    }

    return temp;
}

int Transfer::AdminName()
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
int Transfer::FromAccountNumber()
{
    cout << "Enter your account number:" << endl;
    cin >> fromAcc.accountNumber;

    // Check if account number is valid
    if (!currUser.isValidAccountNumber(fromAcc.accountNumber))
    {
        cout << "Account number is invalid" << endl;
        return 0;
    }

    // Validation for account number and name
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        string currAccStatus = currAccounts.accounts[i].accountStatus;
        float currAccBal = currAccounts.accounts[i].accountBalance;

        if (fromAcc.accountNumber == currAccNum && currUser.userName == currAccName)
        {
            if (currAccStatus == "D")
            {
                cout << "Account Disabled!" << endl;
                return 0;
            }

            cout << "Account Found!" << endl;
            fromAcc.accountHolderName = currAccName;
            fromAcc.accountStatus = currAccStatus;
            fromAcc.accountBalance = currAccBal;
            return 1;
        }
    }

    cout << "Account Not Found" << endl;
    return 0;
}

// Enter the account number to transfer money to
int Transfer::ToAccountNumber()
{
    cout << "Enter the account number you want to transfer to:" << endl;
    cin >> toAcc.accountNumber;

    // Check if account number is valid
    if (!currUser.isValidAccountNumber(toAcc.accountNumber))
    {
        cout << "Account number is invalid" << endl;
        return 0;
    }

    // Validate Account Number
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccStatus = currAccounts.accounts[i].accountStatus;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        float currAccBal = currAccounts.accounts[i].accountBalance;

        if (toAcc.accountNumber == currAccNum)
        {
            if (currAccStatus == "D")
            {
                cout << "Account Disabled!" << endl;
                return 0;
            }
            cout << "Account Found!" << endl;
            toAcc.accountHolderName = currAccName;
            toAcc.accountStatus = currAccStatus;
            toAcc.accountBalance = currAccBal;
            return 1;
        }
    }

    cout << "Account Not Found" << endl;
    return 0;
}

// Enter the amount you are transfering
int Transfer::EnterAmount()
{
    cout << "Enter the amount of money to transfer:" << endl;
    cin >> transferAmount;

    if (transferAmount > 1000 && !currUser.isAdmin)
    {
        cout << "Error: Value Error - transfer value cannot exceed $1000.00!" << endl;
        return 0;
    }
    else if (transferAmount > 99999.99)
    {
        cout << "Error: Value Error - cannot transfer more than $99999.99!" << endl;
        return 0;
    }
    else if (transferAmount < 0)
    {
        cout << "Error: Value Error - cannot transfer less than $0!" << endl;
        return 0;
    }
    else if (transferAmount > fromAcc.accountBalance)
    {
        cout << "ERROR: Value Error - transfer value exceeds account balance!" << endl;
        return 0;
    }

    fromAcc.accountBalance -= transferAmount;
    toAcc.accountBalance += transferAmount;
    UpdateAccount();

    cout << "Transfer Successful!" << endl;
    return 1;
}

// Update both Frm Account and To Account
void Transfer::UpdateAccount()
{
    currAccounts.UpdateAccount(fromAcc);
    currAccounts.UpdateAccount(toAcc);

    cout << "Account Updated!" << endl;
}

// Make sure the account balance is not in the negative
int Transfer::CheckAccountBalance()
{
    if (fromAcc.accountBalance < 0 or toAcc.accountBalance < 0)
    {
        cout << "Account negative" << endl;
        return 0;
    }
    return 1;
}

// Save Transaction
Transaction Transfer::SaveTransaction()
{
    Transaction transaction(2, currUser.userName, fromAcc.accountNumber, transferAmount, "CR");

    cout << "Receipt Saved!" << endl;
    return transaction;
}
