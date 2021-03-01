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
                return SaveTransaction();
            }
        }
    }

    return temp;
}

// If admin, ask for their name
int Paybill::AdminName()
{
    cout << "Enter Your Name:" << endl;
    getline(cin >> ws, currUser.userName);

    cout << "Hi " << currUser.userName << endl;
    return 1;
}

// Where user enter their account number
int Paybill::EnterAccountNumber()
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

// Enter the company to be paid name
int Paybill::SelectCompany()
{
    string company;

    cout << "Enter the company you want to pay: (EC, CO, FI)" << endl;
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

    cout << "Payment Successful!" << endl;
    return 1;
}

// Save Transaction
Transaction Paybill::SaveTransaction()
{
    Transaction transaction(3, currUser.userName, currUser.bankAccountNumber, amountPaid, "00");

    cout << "Receipt Saved!" << endl;
    return transaction;
}