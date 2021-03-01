#include "login.h"

// 0 - Error
// 1 - Success
// Central function that runs all login methods
int Login::RunLogin()
{
    int session = SelectSession();
    if (!session)
    {
        return 0;
    }

    if (!isAdmin)
    {
        StandardName();
        cout << "Hi " << accountHolderName << endl;
    }

    return 1;
}

// Selecting session where
// 1 - admin
// 2 - standard
int Login::SelectSession()
{
    int type;

    cout << "Welcome to the banking system\n";
    cout << "Enter session type: (admin - 1 / standard - 2)\n";
    cin >> type;

    if (type == 1 || type == 2)
    {
        cout << "Login Accepted!\n";

        if (type == 1)
        {
            isAdmin = 1;
        }
        else if (type == 2)
        {
            isAdmin = 0;
        }

        return 1;
    }

    return 0;
}

// Ask for standard user name
void Login::StandardName()
{
    cout << "Enter Your Name:";
    cin >> accountHolderName;
}

// Save login info into a User Class that is then used by other transaction
User Login::saveUserInfo()
{
    User user;
    user.isAdmin = isAdmin;
    user.userName = accountHolderName;

    return user;
}