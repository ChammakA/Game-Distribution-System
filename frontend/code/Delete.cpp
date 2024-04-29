#include "Delete.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>

void Delete::writeToDaily(const string& user, const string& type, double price){
    ofstream dailyTransaction;
    dailyTransaction.open(dailyTransactionFilePath, ios::app);

    if (!dailyTransaction.is_open()){ // Error handling for file not opening
        cout << "Error: Delete Daily Transaction File was not able to be opened." << endl;
    }
    stringstream ss; // Convert price to string with 2 decimal places
    ss << fixed << setprecision(2) << price;
    string priceAsString = ss.str();

    size_t decimalPos = priceAsString.find('.'); // Find the position of the decimal point
    // Count the number of digits after the decimal point

    // Add leading zeros before the decimal point to make the total length 9 characters
    if (decimalPos < 6) {
        priceAsString = string(6 - decimalPos, '0') + priceAsString;
    }

    string userAsString = user;
    string typeAsString = type;

    if (userAsString.length() < 15){
        userAsString = userAsString + string(15 - userAsString.length(), '_');
    }
    if (typeAsString.length() < 2){
        typeAsString = typeAsString + string(2 - typeAsString.length(), '_');
    }

    userAsString.resize(15, '_');
    typeAsString.resize(2, '_');


    dailyTransaction << "02_" << userAsString << "_" << typeAsString << "_" << priceAsString << endl;
    dailyTransaction.close();
}

void Delete::deleteUser(){
    inputProcessor ip;
    vector<userAccountsInfo> userAccounts = ip.readUserAccounts(); // Reads the user accounts file
    
    string userInput;
    string type;
    double credits;

    bool userExists;

    do {
        userExists = false;
        cout << "Please enter the username of the account being deleted:" << endl;
        getline(cin, userInput);

        if (userInput.empty()) {
            cout << "Error: Username cannot be empty." << endl;
            continue;
        }
        if (ip.ignoreCase(userInput, "cancel")){ // Checks to see if user wants to cancel
            return;
        }
        if (ip.isCommand(userInput)) { // Checks to see if the input is a command
            continue;
        }
        if (userInput.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) {
            cout << "Error: Username can only contain letters and numbers." << endl;
            continue;
        }
        if (userInput == login.getCurrentUser()) {
            cout << "Error: Cannot delete the currently logged in user." << endl;
            continue;
        }
        for (auto user : userAccounts) {
            if (user.username == userInput) {
                userExists = true;
                type = user.userType;
                credits = user.credits;
                break;
            }
        }
        if (!userExists) {
            cout << "Error: Username doesn't exist. " << endl;
        }

    } while(!userExists);

    ip.addDeletedUser(userInput);
    cout << "User '" << userInput << "' has been deleted." << endl;
    writeToDaily(userInput, type, credits);
}