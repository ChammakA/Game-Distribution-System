#include "Login.h"

#include <iostream>
#include <fstream>
#include <string>

// function to check if input is login command
bool Login::isLogin(const string& input) {
    inputProcessor ip;
    if (input.empty()){
        cout << "Input cannot be empty." << endl;
        return false;
    }
    if (ip.ignoreCase(input, "login")) {
        cout << "Login command accepted.\n";
        return true;
    }
    else {
        cout << "Invalid command." << endl;
        return false;
    }
}

// Function to check if user exists and log them in if they do
bool Login::loginUser(const string& username){
    inputProcessor ip;
    vector<userAccountsInfo> userAccounts = ip.readUserAccounts(); // Reads the user accounts file
    bool userExists = false; // Base case for user not existing

    if (username.empty()){ // Check if username is empty
        cout << "Error: Username cannot be empty" << endl;
        return false;
    }

    for (auto user : userAccounts){
        if (user.username == username){ // If the username is found, the user is logged in
            currentUser = user.username; // Sets the current user
            level = ip.typeUser(user.userType); // Sets the user type
            credit = user.credits; // Sets the user credit
            LoggedIn = true; // Sets the user as logged in
            userExists = true; // Sets the user as existing
            return true;
        }
    }
    
    cout << "Error: User does not exist." << endl;
    return false;
}

// Function to log the user out
void Login::logoutUser(){ 
    LoggedIn = false;
    currentUser = "";
    cout << "Logging Out..." << endl;

    // adds 00 to signify logout in the daily transaction file
    ofstream dailyTransaction;
    dailyTransaction.open(dailyTransactionFilePath, ios::app);

    if (!dailyTransaction.is_open()){ // Error handling for file not opening
        cout << "Error: Logout Daily Transaction File was not able to be opened." << endl;
    }
    dailyTransaction << "00" << endl;
}