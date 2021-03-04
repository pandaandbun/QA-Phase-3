#include "login.h"

//Comparison function checking if the name string matches a predefined regex for account names
int User::isValidName(string name)
{
    // Check if name is not null or empty string
    if (name.empty() || name.compare("") == 0)
    {
        return 0;
    }

    // Check if name is at most 20 characters long and at least 1 character long
    if (name.length() > 20)
    {
        return 0;
    }

    // Check if name does not contain digits or illegal characters
    regex regexName("[^\\t\\n\\r\\f\\v0-9\\[\\]!@#$%^&*()_+{}|\\:;\"\'<,>.?/~`]+");
    if (!regex_match(name, regexName))
    {
        return 0;
    }

    return 1;
}

// ----------------------------------------
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
        if (StandardName())
        {
            // Standard Validated
            cout << "Hi " << accountHolderName << endl;
            return 1;
        }

        cout << "Name not valid" << endl;
    } else {
        // Admin Validated
        return 1;
    }

    return 0;
}

// Selecting session where
// admin
// standard
int Login::SelectSession()
{
    string type;

    cout << "Enter session type: (admin / standard)\n";
    cin >> type;

    if (type == "admin" || type == "standard")
    {
        cout << "Login Accepted!\n";

        if (type == "admin")
        {
            isAdmin = 1;
        }
        else if (type == "standard")
        {
            isAdmin = 0;
        }

        return 1;
    }

    return 0;
}

// Ask for standard user name
int Login::StandardName()
{
    string name;
    User user_check;

    cout << "Enter Your Name:" << endl;
    getline(cin >> ws, name);

    // Check if name is valid
    if (user_check.isValidName(name))
    {
        accountHolderName = name;
        return 1;
    }

    // Name not valid
    return 0;
}

// Save login info into a User Class that is then used by other transaction
User Login::saveUserInfo()
{
    User user;
    user.isAdmin = isAdmin;
    user.userName = accountHolderName;

    return user;
}