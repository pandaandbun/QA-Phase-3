#include "paybill.h"

// Constructor accepts the current bank accounts instance
Paybill::Paybill(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

// Where everything come together
Transaction Paybill::RunPaybill()
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
        if (SelectCompany())
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

// If admin, ask for their name
int Paybill::AdminName()
{
    User check_user;
    string name;

    cout << "Enter Your Name:" << endl;
    getline(cin >> ws, name);

    // Name Validation
    if (check_user.isValidName(name))
    {
        currUser.userName = name;
        cout << "Hi " << currUser.userName << endl;
        return 1;
    }

    cout << "Name not valid" << endl;
    return 0;
}

// Where user enter their account number
int Paybill::EnterAccountNumber()
{
    User check_user;
    int accountNum = -1;

    cout << "Enter your account number:" << endl;
    cin >> accountNum;

    if (!check_user.isValidAccountNumber(accountNum))
    {
        cout << "Account number not valid" << endl;
        return 0;
    }

    // Validation for account number and name
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;
        string currAccStatus = currAccounts.accounts[i].accountStatus;
        float currAccBal = currAccounts.accounts[i].accountBalance;

        if (accountNum == currAccNum && currUser.userName == currAccName)
        {
            acc.accountNumber = currUser.bankAccountNumber = accountNum;
            acc.accountHolderName = currAccName;
            acc.accountStatus = currAccStatus;
            acc.accountBalance = currAccBal;

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

// Enter the company to be paid name
int Paybill::SelectCompany()
{
    string company;

    cout << "\nThe Bright Light Electric Company (EC)\n"
         << "Credit Card Company Q (CQ)\n"
         << "Fast Internet, Inc. (FI)\n"
         << endl;
    cout << "Enter the company shorthand you want to pay: " << endl;
    cin >> company;

    if (company == "EC" || company == "CO" || company == "FI")
    {
        companyName = company;
        cout << "Company Found!" << endl;
        return 1;
    }

    cout << "Company Not Found" << endl;
    return 0;
}

// Enter the amount you are paying to the company
int Paybill::EnterAmount()
{
    cout << "Enter the ammount to be paid:" << endl;
    cin >> amountPaid;

    if (amountPaid < 0)
    {
        cout << "Error: Value Error - cannot Paybill less than $0!" << endl;
        return 0;
    }
    else if (amountPaid > 99999.99)
    {
        cout << "Error: Value Error - Paybill value cannot exceed $99999.00!" << endl;
        return 0;
    }
    else if (amountPaid > 2000.00 && !currUser.isAdmin)
    {
        cout << "ERROR: Value Error - Paybill more than $2000!" << endl;
        return 0;
    }
    else if (amountPaid > acc.accountBalance)
    {
        cout << "ERROR: Value Error - Paybill value exceeds account balance!" << endl;
        return 0;
    }

    // Payment successful
    acc.accountBalance -= amountPaid;
    UpdateAccount();
    cout << "Payment Successful!" << endl;

    return 1;
}

// Update bank account file
int Paybill::UpdateAccount()
{
    cout << "Account Updated" << endl;
    currAccounts.UpdateAccount(acc);
    return 1;
}

// Make sure the account balance is not in the negative
int Paybill::CheckAccountBalance()
{
    if (acc.accountBalance < 0)
    {
        cout << "Account negative" << endl;
        return 0;
    }
    return 1;
}

// Save Transaction
Transaction Paybill::SaveTransaction()
{
    Transaction transaction(3, currUser.userName, currUser.bankAccountNumber, amountPaid, "CR");

    cout << "Receipt Saved!" << endl;
    return transaction;
}