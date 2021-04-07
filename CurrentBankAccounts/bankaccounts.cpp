#include "bankaccounts.h"

// trim from start (in place)
void ltrim(string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
}

// trim from end (in place)
void rtrim(string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(),
            s.end());
}

// trim from both ends (in place)
void trim(string &s)
{
    ltrim(s);
    rtrim(s);
}

// ---------------------------------------

// Default Constructor
CurrentBankAccounts::CurrentBankAccounts() {}

CurrentBankAccounts::CurrentBankAccounts(string fileName)
{
    this->fileName = fileName;
}

// ---------------------------------------

// Read the file
// Find how many bank account there is
// Create an array of bank account that size
int CurrentBankAccounts::ReadCurrentBankAccounts()
{
    ifstream accountsFile(fileName);

    if (!accountsFile)
    {
        cout << "No such file" << endl;
    }
    else
    {
        string line;

        while (getline(accountsFile, line))
        {
            if (stoi(line.substr(0, 5)) != 0)
            {
                // Account Number
                BankAccount account;
                account.accountNumber = stoi(line.substr(0, 5));

                // Account Holder Name
                string str = line.substr(6, 20);
                // replace(str.begin(), str.end(), '_', ' ');
                trim(str);
                account.accountHolderName = str;

                // Account Status
                account.accountStatus = line[27];

                // Account Balance
                account.accountBalance = stof(line.substr(29, 8));

                // Account Plan
                if (account.accountStatus == "A")
                {
                    account.accountPlan = "SP";
                }
                else if (account.accountStatus == "B")
                {
                    account.accountPlan = "NP";
                }

                accounts.push_back(account);
            }
        }

        return 1;
    }

    accountsFile.close();
    return 0;
}

// Load current bank accounts file
int CurrentBankAccounts::LoadBankAccounts()
{
    cout << "…...Please wait while we load Current Bank Accounts……" << endl;

    if (ReadCurrentBankAccounts())
    {
        cout << "Success! Please have a great time Banking with us" << endl;
        return 1;
    }

    cout << "Error Loading Current Accounts" << endl;
    return 0;
}
