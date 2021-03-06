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

// Add new account to file
void CurrentBankAccounts::CreateAccount(BankAccount acc)
{
    ifstream in(fileName);
    ofstream out("temp.txt");

    string line;

    // Account Number
    ostringstream ss;
    ss << setw(5) << setfill('0') << acc.accountNumber;
    string paddedAccountNumber = ss.str();

    // Account Holder Name
    string paddedAccountHolderName = acc.accountHolderName;
    int padLength = 20 - acc.accountHolderName.size();
    for (int i = 0; i < padLength; i++)
    {
        paddedAccountHolderName += "_";
    }
    replace(paddedAccountHolderName.begin(), paddedAccountHolderName.end(), ' ', '_');

    // Account Balance
    ostringstream ss2;
    ss2 << setw(8) << setfill('0') << setprecision(2) << fixed << acc.accountBalance;
    string paddedAccountBalance = ss2.str();

    // Adding new account
    string newLine = paddedAccountNumber + "_" + paddedAccountHolderName + "_" + acc.accountStatus + "_" + paddedAccountBalance;
    out << newLine << endl;

    while (getline(in, line))
    {
        out << line << endl;
    }

    // OVerwriting to old file
    const char *p = fileName.c_str();
    remove(p);
    rename("temp.txt", p);
}

// Delete Account from file
void CurrentBankAccounts::DeleteAccount(BankAccount acc)
{
    ifstream in(fileName);
    ofstream out("temp.txt");

    string line;

    // Account Number
    ostringstream ss;
    ss << setw(5) << setfill('0') << acc.accountNumber;
    string paddedAccountNumber = ss.str();

    // Delete account
    while (getline(in, line))
    {
        string accNumber = line.substr(0, 5);
        if (accNumber != paddedAccountNumber)
        {
            out << line << endl;
        }
    }

    // Overwriting old file
    const char *p = fileName.c_str();
    remove(p);
    rename("temp.txt", p);

    // Updating Deleted Account on Memory
    for (int i = 0; i < accounts.size(); i++){
        if (accounts[i].accountHolderName.compare(acc.accountHolderName) == 0 && accounts[i].accountNumber == acc.accountNumber){
            accounts.erase(accounts.begin() + i);
        }
    }
}

// Disable Account from file
void CurrentBankAccounts::DisableAccount(BankAccount acc)
{
    ifstream in(fileName);
    ofstream out("temp.txt");

    string line;

    // Account Number
    ostringstream ss;
    ss << setw(5) << setfill('0') << acc.accountNumber;
    string paddedAccountNumber = ss.str();

    // Disable account
    while (getline(in, line))
    {
        string accNumber = line.substr(0, 5);
        if (accNumber == paddedAccountNumber)
        {
            line[27] = 'D';
        }
        out << line << endl;
    }

    // Overwriting old file
    const char *p = fileName.c_str();
    remove(p);
    rename("temp.txt", p);

    // Updating Disabled Account on Memory
    for (int i = 0; i < accounts.size(); i++){
        if (accounts[i].accountHolderName.compare(acc.accountHolderName) == 0 && accounts[i].accountNumber == acc.accountNumber){
            accounts[i].accountStatus = "D";
        }
    }
}

// Update Account Balance from file
void CurrentBankAccounts::UpdateAccount(BankAccount acc)
{
    ifstream in(fileName);
    ofstream out("temp.txt");

    string line;

    // Account Number
    ostringstream ss;
    ss << setw(5) << setfill('0') << acc.accountNumber;
    string paddedAccountNumber = ss.str();

    // Update account
    while (getline(in, line))
    {
        string accNumber = line.substr(0, 5);
        if (accNumber == paddedAccountNumber)
        {
            // Convert Balance to String
            ostringstream ss2;
            ss2 << setw(8) << setfill('0') << setprecision(2) << fixed << acc.accountBalance;
            string paddedAccountBalance = ss2.str();

            // Update the line
            line.replace(29, 8, paddedAccountBalance);
        }
        out << line << endl;
    }

    // Overwriting old file
    const char *p = fileName.c_str();
    remove(p);
    rename("temp.txt", p);
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

        while (1)
        {
            accountsFile >> line;
            if (accountsFile.eof())
                break;

            if (stoi(line.substr(0, 5)) != 0)
            {
                // Account Number
                BankAccount account;
                account.accountNumber = stoi(line.substr(0, 5));

                // Account Holder Name
                string str = line.substr(6, 20);
                replace(str.begin(), str.end(), '_', ' ');
                trim(str);
                account.accountHolderName = str;

                // Account Status
                account.accountStatus = line[27];

                // Account Balance
                account.accountBalance = stof(line.substr(29, 8));

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
