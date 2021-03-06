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
    cout << "Enter your account number:" << endl;
    cin >> fromAcc.accountNumber;

    // Validation for account number and name
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        string currAccStatus = currAccounts.accounts[i].accountStatus;
        float currAccBal = currAccounts.accounts[i].accountBalance;

        if (fromAcc.accountNumber == currAccNum && currUser.userName == currAccName)
        {
            fromAccountNumber = fromAcc.accountNumber;
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

    // Validate Account Number
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccStatus = currAccounts.accounts[i].accountStatus;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        float currAccBal = currAccounts.accounts[i].accountBalance;
        
        if (toAcc.accountNumber == currAccNum)
        {
            toAccountNumber = toAcc.accountNumber;
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

    if(transferAmount > 1000 && !currUser.isAdmin){
        cout << "Error: Value Error - transfer value cannot exceed $1000.00!" << endl;
        return 0;
    }
    else if(transferAmount > 99999.99) {
        cout << "Error: Value Error - cannot transfer more than $99999.99!" << endl;
            return 0;
    }
    else if(transferAmount < 0){
        cout << "Error: Value Error - cannot transfer less than $0!" << endl;
        return 0;
    } else if(transferAmount > fromAcc.accountBalance) {
        cout << "ERROR: Value Error - transfer value exceeds account balance!" << endl;
        return 0;
    }

    cout << "Transfer Successful!" << endl;
    return 1;
}

// Save Transaction
Transaction Transfer::SaveTransaction()
{
    Transaction transaction(2, currUser.userName, fromAccountNumber, transferAmount, "CR");

    cout << "Receipt Saved!" << endl;
    return transaction;
}
