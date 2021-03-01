#include "logout.h"

// Constructor for LOGOUT
// Set BankAccountTransaction
Logout::Logout(BankAccountTransaction currTransaction)
{
    this->currTransaction = currTransaction;
}

// Run the logout process
// take the BankAccountTransaction var set by constructor and create a file with the save transaction
// After exit the program
int Logout::RunLogout()
{
    currTransaction.CreateTransactionFile();
    cout << "Session Terminated" << endl;
    exit(0);
}