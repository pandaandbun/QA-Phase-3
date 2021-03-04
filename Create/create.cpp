#include "create.h"

// Constructor
Create::Create(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

// Where everything is run
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
                    if (CreateAccount())
                    {
                        return SaveTransaction();
                    }
                }
            }
        }
    }

    Transaction temp;
    return temp;
}

// Enter Account Holder Name
int Create::EnterAccountHolderName()
{
    string name;

    cout << "Enter Account Holder Name:" << endl;
    getline(cin >> ws, name);

    // Check if name is valid
    if (currUser.isValidName(name))
    {
        acc.accountHolderName = name;
        return 1;
    }

    // Name not valid
    cout << "Name not valid" << endl;
    return 0;
}

// Enter Account Balance
int Create::EnterAccountBalance()
{
    float newAccountBalance = -1.0;

    cout << "Enter Account Balance:" << endl;
    cin >> newAccountBalance;

    // Check if balance is valid
    return CheckValidAccountBalance(newAccountBalance);
}

int Create::CheckValidAccountBalance(float newAccountBalance)
{
    // Check if user didnt input a balance or input a negative balance or put over the max limit
    if (newAccountBalance < 0.0 || newAccountBalance > 99999.99)
    {
        cout << "Invalid Account Balance" << endl;
        return 0;
    }

    // Balance is valid, set new account balance
    acc.accountBalance = newAccountBalance;
    return 1;
}

// Generate New Account Number
int Create::GenerateAccountNumber()
{
    // Find the highest account number
    int highestAccNumber = 0;
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccountNum = currAccounts.accounts[i].accountNumber;
        if (highestAccNumber < currAccountNum)
        {
            highestAccNumber = currAccountNum;
        }
    }

    // Set the new account number as the highest + 1
    int newAccountNumber = highestAccNumber + 1;
    acc.accountNumber = newAccountNumber;

    return 1;
}

// Create Account
int Create::CreateAccount()
{
    cout << "Account Created" << endl;
    acc.accountStatus = "A";
    currAccounts.CreateAccount(acc);
    return 1;
}

// Save Transaction
Transaction Create::SaveTransaction()
{
    Transaction transaction(5, acc.accountHolderName, acc.accountNumber, acc.accountBalance, "00");
    cout << "Receipt Saved!" << endl;
    return transaction;
}