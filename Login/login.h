#pragma once
#include <iostream>
#include <string>
#include <regex>

using namespace std;

// User class containing current user info
// for use by other transaction
class User
{
public:
    int bankAccountNumber;
    string userName;
    bool isAdmin;
    int isValidName(string name);
};

// Login class that facilitate and validate login
class Login
{
private:
    bool isAdmin;
    string accountHolderName;

public:
    int RunLogin();
    int SelectSession();
    int StandardName();
    User saveUserInfo();
};