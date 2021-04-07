#include "changeplan.h"

// This is where everything is run
Transaction ChangePlan::RunChangePlan()
{
    if (currUser.isAdmin)
    {
        if (EnterAccountHolderName())
        {
            if (EnterAccountNumber())
            {
                if (CheckValidAccount())
                {

                    if (CheckValidPlan())
                    {
                        ChangeAccount();
                        return SaveTransaction();
                    }
                }
            }
        }
    }

    Transaction temp;
    return temp;
}

// Enter account holder name
int ChangePlan::EnterAccountHolderName()
{
    cout << "Enter Account Holder Name:" << endl;
    getline(cin >> ws, currUser.userName);

    // Check if name is valid
    if (currUser.isValidName(currUser.userName))
    {
        acc.accountHolderName = currUser.userName;
        return 1;
    }

    cout << "Name is invalid" << endl;
    return 0;
}

// Enter account number
int ChangePlan::EnterAccountNumber()
{
    cout << "Enter Account Number:" << endl;
    cin >> currUser.bankAccountNumber;

    // Check if account number is valid
    if (currUser.isValidAccountNumber(currUser.bankAccountNumber))
    {
        acc.accountNumber = currUser.bankAccountNumber;
        return 1;
    }

    cout << "Account number is invalid" << endl;
    return 0;
}

// Check if account is valid
int ChangePlan::CheckValidAccount()
{
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;

        if (acc.accountNumber == currAccNum && acc.accountHolderName == currAccName)
        {
            if (currAccounts.accounts[i].accountStatus == "D" || currAccounts.accounts[i].accountStatus == "C")
            {
                cout << "Account Disabled!" << endl;
                return 0;
            }

            cout << "Account Found!" << endl;
            acc.accountPlan = currAccounts.accounts[i].accountPlan;
            return 1;
        }
    }

    cout << "Account Not Found" << endl;
    return 0;
}

// Check if plan is valid
int ChangePlan::CheckValidPlan()
{
    if (acc.accountPlan == "SP" || acc.accountPlan == "NP")
    {
        return 1;
    }

    cout << "Plan not valid" << endl;
    return 0;
}

// TODO: Figure out where student plan is set
int ChangePlan::ChangeAccount()
{
    if (acc.accountPlan == "SP")
    {
        cout << "Set payment plan from student (SP) to non-student (NP)" << endl;
        acc.accountPlan = "NP";
    }
    else if (acc.accountPlan == "NP")
    {
        cout << "Set payment plan from non-student (NP) to student (SP)" << endl;
        acc.accountPlan = "SP";
    }
    cout << "Account Change" << endl;

    return 1;
}

// Save transaction
Transaction ChangePlan::SaveTransaction()
{
    Transaction transaction(8, currUser.userName, currUser.bankAccountNumber, 0, acc.accountPlan);
    cout << "Receipt Saved!" << endl;
    return transaction;
}