// Tran Tien Anh Ta
// 100648707

/*
Build & Run Instruction:
    make
    ./bank
--------------------------------------------------------------------------------------
Overall steps:
1. Run Login
2. If Login is valid and a valid session was choosen then a selection screen is shown
3. After Login, The currentbankaccountfile.txt is read and parse
4. Each line is turn into a BankAccount instance. Each instance contains account number, name, status and balance.
5. A while (1) loop is used for a repeating selection screen until the user logged out
6. the selection screen is split into 2 cattegory (ADMIN and STANDARD)
7. Admin screen contain a full menu
8. Standard screen contain a limited menu
--------------------------------------------------------------------------------------
Input: currentbankaccountfile.txt
Output: a transaction file with timestamp of the time the file was created.

--------------------------------------------------------------------------------------
A set of inputs you can run:
1
4
Carl
4449
10.6
0
--------------------------------------------------------------------------------------
^ That should log you in as 
1 - ADMIN 
Select transaction 
4 - Deposit
Enter name
Carl
Enter account number
4449
Enter deposit amount
10.6
This should be the end of the transaction and bring you back the selection screen
You can now log out
0
This should trigger the code to create a transaction file with the current timestamp as file name.
--------------------------------------------------------------------------------------
*/

#include "./Login/login.h"
#include "./Transfer/transfer.h"
#include "./Paybill/paybill.h"
#include "./ChangePlan/changeplan.h"
#include "./Delete/delete.h"
#include "./Create/create.h"
#include "./Disable/disable.h"
#include "./Withdraw/withdraw.h"
#include "./Deposit/deposit.h"
#include "./CurrentBankAccounts/bankaccounts.h"
#include "./Logout/logout.h"

// Paybill
Transaction TransactionPayBill(CurrentBankAccounts accs, User user)
{
    Paybill paybill(accs, user);
    return paybill.RunPaybill();
}

// Transfer
Transaction TransactionTransfer(CurrentBankAccounts accs, User user)
{
    Transfer transfer(accs, user);
    return transfer.RunTransfer();
}

// Change Plan
Transaction TransactionChangePlan(CurrentBankAccounts accs, User user)
{
    ChangePlan changePlan(accs, user);
    return changePlan.RunChangePlan();
}

// Delete
Transaction TransactionDelete(CurrentBankAccounts accs, User user)
{
    Delete del(accs, user);
    return del.RunDelete();
}

// Create
Transaction TransactionCreate(CurrentBankAccounts accs, User user)
{
    Create create(accs, user);
    return create.RunCreate();
}

// Disable
Transaction TransactionDisable(CurrentBankAccounts accs, User user)
{
    Disable disable(accs, user);
    return disable.RunDisable();
}

// Withdraw
Transaction TransactionWithdraw(CurrentBankAccounts accs, User user)
{
    Withdraw withdraw(accs, user);
    return withdraw.RunWithdrawal();
}

// Deposit
Transaction TransactionDeposit(CurrentBankAccounts accs, User user)
{
    Deposit deposit(accs, user);
    return deposit.RunDeposit();
}

// Logout
void TransactionLogout(BankAccountTransaction trans)
{
    Logout logout(trans);
    logout.RunLogout();
}

// ----------------------------------------------
// Selection Menus
Transaction AdminMenu(User user, CurrentBankAccounts accs, BankAccountTransaction sessionTransactions)
{
    Transaction transaction;
    // Display menu for admin user
    int menuSelection;

    cout << endl
         << "MAIN MENU (Admin Privleges ON)\n"
         << "==============================\n"
         << "1. Withdrawal\n"
         << "2. Transfer\n"
         << "3. Pay Bill\n"
         << "4. Deposit\n"
         << "5. Create\n"
         << "6. Delete\n"
         << "7. Disable\n"
         << "8. Change Plan\n"
         << "0. Logout\n"
         << "\n"
         << "Enter Selection: "
         << endl;

    cin >> menuSelection;

    // Withdrawal
    if (menuSelection == 1)
    {
        transaction = TransactionWithdraw(accs, user);
    }

    // Transfer
    else if (menuSelection == 2)
    {
        transaction = TransactionTransfer(accs, user);
    }

    // Paybill
    else if (menuSelection == 3)
    {
        transaction = TransactionPayBill(accs, user);
    }

    // Deposit
    else if (menuSelection == 4)
    {
        transaction = TransactionDeposit(accs, user);
    }

    // Create
    else if (menuSelection == 5)
    {
        transaction = TransactionCreate(accs, user);
    }

    // Delete
    else if (menuSelection == 6)
    {
        transaction = TransactionDelete(accs, user);
    }

    // Disab;e
    else if (menuSelection == 7)
    {
        transaction = TransactionDisable(accs, user);
    }

    // Change Plan
    else if (menuSelection == 8)
    {
        transaction = TransactionChangePlan(accs, user);
    }

    // Logout
    else if (menuSelection == 0)
    {
        TransactionLogout(sessionTransactions);
    }
    else
    {
        cout << "Command not recognized" << endl;
    }

    return transaction;
}

Transaction StandardMenu(User user, CurrentBankAccounts accs, BankAccountTransaction sessionTransactions)
{
    Transaction transaction;
    // Display menu for standard user
    int menuSelection;

    cout << endl
         << "MAIN MENU\n"
         << "===========\n"
         << "1. Withdrawal\n"
         << "2. Transfer\n"
         << "3. Pay Bill\n"
         << "4. Deposit\n"
         << "0. Logout\n"
         << "\n"
         << "Enter Selection: "
         << endl;

    cin >> menuSelection;

    // Withdrawal
    if (menuSelection == 1)
    {
        transaction = TransactionWithdraw(accs, user);
    }

    // Transfer
    else if (menuSelection == 2)
    {
        transaction = TransactionTransfer(accs, user);
    }

    // Paybill
    else if (menuSelection == 3)
    {
        transaction = TransactionPayBill(accs, user);
    }

    // Deposit
    else if (menuSelection == 4)
    {
        transaction = TransactionDeposit(accs, user);
    }

    // Logout
    else if (menuSelection == 0)
    {
        TransactionLogout(sessionTransactions);
    }
    else
    {
        cout << "Command not recognized" << endl;
    }
    return transaction;
}

Transaction Menu(User user, CurrentBankAccounts accs, BankAccountTransaction sessionTransactions)
{
    Transaction transaction;
    // Selection for ADMIN
    if (user.isAdmin)
    {
        transaction = AdminMenu(user, accs, sessionTransactions);
    }

    // Selection for STANDARD
    else
    {
        transaction = StandardMenu(user, accs, sessionTransactions);
    }

    return transaction;
}

// -----------------------------------------
int main(int argc, char **argv)
{
    if (argc >= 3)
    {
        // File names
        string curretBankAccountFileName = argv[1];
        string transactionFileName = argv[2];

        // Logged In
        Login session;

        // Transaction
        BankAccountTransaction sessionTransactions(transactionFileName);

        // Call login method here and return value for isLoggedIn
        if (session.RunLogin())
        {
            // Save current user info
            User user = session.saveUserInfo();

            // Load Current Bank Acccounts
            CurrentBankAccounts accs(curretBankAccountFileName);
            accs.LoadBankAccounts();
            // Selection Screen
            while (1)
            {
                // Transaction
                Transaction transaction;
                // Menu
                transaction = Menu(user, accs, sessionTransactions);

                // Add valid transaction to transaction list
                if (!transaction.accountHolderName.empty())
                {
                    sessionTransactions.transactions.push_back(transaction);
                }
            }
        }
        else
        {
            TransactionLogout(sessionTransactions);
        }
    }
    else
    {
        cout << "Please enter the correct number of arguments" << endl;
    }
}
