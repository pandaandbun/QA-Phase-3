#include <tuple>
#include "./Login/login.h"
#include "./Transfer/transfer.h"
#include "./Paybill/paybill.h"
#include "./ChangePlan/changeplan.h"
#include "./Delete/delete.h"
#include "./Create/create.h"
#include "./Disable/disable.h"
#include "./Withdrawal/withdrawal.h"
#include "./Deposit/deposit.h"
#include "./CurrentBankAccounts/bankaccounts.h"
#include "./Logout/logout.h"

// Paybill
Transaction TransactionPayBill(CurrentBankAccounts &accs, User user)
{
    Paybill paybill(accs, user);
    return paybill.RunPaybill();
}

// Transfer
Transaction TransactionTransfer(CurrentBankAccounts &accs, User user)
{
    Transfer transfer(accs, user);
    return transfer.RunTransfer();
}

// Change Plan
Transaction TransactionChangePlan(CurrentBankAccounts &accs, User user)
{
    ChangePlan changePlan(accs, user);
    return changePlan.RunChangePlan();
}

// Delete
Transaction TransactionDelete(CurrentBankAccounts &accs, User user)
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
Transaction TransactionDisable(CurrentBankAccounts &accs, User user)
{
    Disable disable(accs, user);
    return disable.RunDisable();
}

// withdrawal
Transaction TransactionWithdraw(CurrentBankAccounts &accs, User user)
{
    withdrawal withdrawal(accs, user);
    return withdrawal.RunWithdrawal();
}

// Deposit
Transaction TransactionDeposit(CurrentBankAccounts accs, User user)
{
    Deposit deposit(accs, user);
    return deposit.RunDeposit();
}

// Logout
int TransactionLogout(BankAccountTransaction trans)
{
    Logout logout(trans);
    return logout.RunLogout();
}

// ----------------------------------------------

// Selection Menus
tuple<Transaction, int> AdminMenu(User user, CurrentBankAccounts &accs, BankAccountTransaction sessionTransactions)
{
    Transaction transaction;
    // Display menu for admin user
    string menuSelection;
    int runSession = 1;

    cout << endl
         << "MAIN MENU (Admin Privileges ON)\n"
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
    if (menuSelection == "withdrawal")
    {
        transaction = TransactionWithdraw(accs, user);
    }

    // Transfer
    else if (menuSelection == "transfer")
    {
        transaction = TransactionTransfer(accs, user);
    }

    // Paybill
    else if (menuSelection == "paybill")
    {
        transaction = TransactionPayBill(accs, user);
    }

    // Deposit
    else if (menuSelection == "deposit")
    {
        transaction = TransactionDeposit(accs, user);
    }

    // Create
    else if (menuSelection == "create")
    {
        transaction = TransactionCreate(accs, user);
    }

    // Delete
    else if (menuSelection == "delete")
    {
        transaction = TransactionDelete(accs, user);
    }

    // Disab;e
    else if (menuSelection == "disable")
    {
        transaction = TransactionDisable(accs, user);
    }

    // Change Plan
    else if (menuSelection == "changeplan")
    {
        transaction = TransactionChangePlan(accs, user);
    }

    // Logout
    else if (menuSelection == "logout")
    {
        runSession = TransactionLogout(sessionTransactions);
    }
    else
    {
        cout << "Command not recognized" << endl;
    }

    return {transaction, runSession};
}

tuple<Transaction, int> StandardMenu(User user, CurrentBankAccounts accs, BankAccountTransaction sessionTransactions)
{
    Transaction transaction;
    // Display menu for standard user
    string menuSelection;
    int runSession = 1;

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
    if (menuSelection == "withdrawal")
    {
        transaction = TransactionWithdraw(accs, user);
    }

    // Transfer
    else if (menuSelection == "transfer")
    {
        transaction = TransactionTransfer(accs, user);
    }

    // Paybill
    else if (menuSelection == "paybill")
    {
        transaction = TransactionPayBill(accs, user);
    }

    // Deposit
    else if (menuSelection == "deposit")
    {
        transaction = TransactionDeposit(accs, user);
    }

    // Logout
    else if (menuSelection == "logout")
    {
        runSession = TransactionLogout(sessionTransactions);
    }
    else
    {
        cout << "Command not recognized" << endl;
    }
    return {transaction, runSession};
}

tuple<Transaction, int> Menu(User user, CurrentBankAccounts &accs, BankAccountTransaction sessionTransactions)
{
    Transaction transaction;
    int runSession = 1;

    // Selection for ADMIN
    if (user.isAdmin)
    {
        tie(transaction, runSession) = AdminMenu(user, accs, sessionTransactions);
    }

    // Selection for STANDARD
    else
    {
        tie(transaction, runSession) = StandardMenu(user, accs, sessionTransactions);
    }

    return {transaction, runSession};
}

void SelectionScreen(string curretBankAccountFileName, string transactionFileName)
{
    // Logged In
    Login session;

    // Transaction
    BankAccountTransaction sessionTransactions(transactionFileName);

    // Call login method here and return value for isLoggedIn
    if (session.RunLogin())
    {
        // Set session to keep running
        int runSession = 1;

        // Save current user info
        User user = session.saveUserInfo();

        // Load Current Bank Acccounts
        CurrentBankAccounts accs(curretBankAccountFileName);
        accs.LoadBankAccounts();

        // Selection Screen
        while (runSession)
        {
            // Transaction
            Transaction transaction;
            // Menu
            tie(transaction, runSession) = Menu(user, accs, sessionTransactions);

            // Clear any bad inputs
            if (!cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }

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

// -----------------------------------------
int main(int argc, char **argv)
{
    if (argc >= 3)
    {
        string loginCommand;
        // Intro message
        cout << "Welcome to the banking system" << endl;

        // loop until user type exit
        while (1)
        {
            // Accept login command
            cin >> loginCommand;

            // Login Command
            if (loginCommand == "login")
            {
                // File names
                string curretBankAccountFileName = argv[1];
                string transactionFileName = argv[2];

                // The actual ATM
                SelectionScreen(curretBankAccountFileName, transactionFileName);
            }
            // break loop
            else if (loginCommand == "exit")
            {
                break;
            }
            else
            {
                cout << "Command not recognized." << endl;
            }
        }
    }
    else
    {
        cout << "Please enter the correct number of arguments" << endl;
    }
}
