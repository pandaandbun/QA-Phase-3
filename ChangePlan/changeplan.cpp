#include "changeplan.h"

ChangePlan::ChangePlan(CurrentBankAccounts currAccounts, User currUser)
{
    this->currAccounts = currAccounts;
    this->currUser = currUser;
}

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
                    if (EnterAccountPlan())
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
    }

    Transaction temp;
    return temp;
}

int ChangePlan::EnterAccountHolderName()
{
    cout << "Enter Account Holder Name:" << endl;
    getline(cin >> ws, acc.accountHolderName);
    return 1;
}

int ChangePlan::EnterAccountNumber()
{
    cout << "Enter Account Number:" << endl;
    cin >> acc.accountNumber;
    return 1;
}

int ChangePlan::EnterAccountPlan()
{
    cout << "Enter Account Plan:" << endl;
    cin >> acc.accountPlan;
    return 1;
}

int ChangePlan::CheckValidAccount()
{
    for (int i = 0; i < currAccounts.accounts.size(); i++)
    {
        int currAccNum = currAccounts.accounts[i].accountNumber;
        string currAccName = currAccounts.accounts[i].accountHolderName;

        if (acc.accountNumber == currAccNum && acc.accountHolderName == currAccName)
        {
            cout << "Account Found!" << endl;
            return 1;
        }
    }

    cout << "Account Not Found" << endl;
    return 0;
}

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
    if (acc.accountPlan == "SP"){
        cout << "Set payment plan from student (SP) to non-student (NP)" << endl;
        acc.accountPlan = "NP";
    }
    else if (acc.accountPlan == "NP") {
        cout << "No change was made to payment plan" << endl;
    }
    cout << "Account Change" << endl;

    return 1;
}

Transaction ChangePlan::SaveTransaction()
{
    Transaction transaction(8, acc.accountHolderName, acc.accountNumber, 0, acc.accountPlan);
    cout << "Receipt Saved!" << endl;
    return transaction;
}