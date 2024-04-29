#include "AddCredit.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

void AddCredit::writeToDaily(const string& username, const string& type, double price){
    ofstream dailyTransaction;
    dailyTransaction.open(dailyTransactionFilePath, ios::app);

    if (!dailyTransaction.is_open()){ // Error handling for file not opening
        cout << "Error: Buy Daily Transaction File was not able to be opened." << endl;
        return;
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


    string user = username;
    string typeAsString = type;

    //priceAsString = string(6 - priceAsString.length(), '0') + priceAsString;

    if (user.length() < 15){ // Add trailing underscores to make the total length 15 characters
        user = user + string(15 - user.length(), '_');
    }
    if (typeAsString.length() < 2){ // Add trailing underscores to make the total length 2 characters
        typeAsString = typeAsString + string(2 - typeAsString.length(), '_');
    }

    user.resize(15, '_'); // Resize the string to 15 characters
    typeAsString.resize(2, '_'); // Resize the string to 2 characters

    dailyTransaction << "06_" << user << "_" << typeAsString << "_" << priceAsString << endl; // Write to the daily transaction file
    dailyTransaction.close();
}

// Function to handle the AddCredit command
void AddCredit::addCreditCommand() {
    inputProcessor ip; // Assuming login is a member of the AddCredit class
    vector<userAccountsInfo> userAccounts = ip.readUserAccounts(); // Reads the user accounts file
    bool validUser = false;

    double amount; // Initialize amount to -1
    bool validAmount = false;
    string amountInput;
    string username;
    string userType;

    if (login.getUserLevel() == "Admin") { // If the user is an admin, they can add credit to any user
    
        do {
            cout << "Enter the username to add credit to:" << endl;
            getline(cin, username);

            if (username.empty()) {
                cout << "Username cannot be empty." << endl;
                continue;
            }

            if (ip.ignoreCase(username, "cancel")) {
                return;
            }

            for (auto user : userAccounts) { // Check if the user exists
                if (user.username == username) {
                    userType = user.userType;
                    validUser = true;
                }
            }
            if (!validUser) {
                cout << "Error: User does not exist. ";
            }
        } while (!validUser); // Loop until a valid user is entered

        do {
            cout << "Enter the amount of credit to add:" << endl; // Prompt user for the amount of credit to add
            getline(cin, amountInput);
            if (amountInput.empty()) {
                cout << "Amount cannot be empty." << endl;
                continue;
            }
            if (ip.ignoreCase(amountInput, "cancel")) {
                return;
            }
            try { // Error handling for invalid input
                amount = stod(amountInput);
                if (amount < 0) {
                    cout << "Error: Credit amount cannot be negative." << endl;
                    continue;
                }
                else if (amount > 999.99) {
                    cout << "Error: Credit amount cannot exceed 999.99." << endl;
                    continue;
                }
                else{
                    validAmount = true;}
            } catch (invalid_argument e) {
                cout << "Error: Credit amount must be a number." << endl;
            }
        } while (!validAmount);

        if (login.getUserCredit() + amount > 999.99){
            amount = 999.99;
            login.setUserCredit(999.99);
        }else {
            login.setUserCredit(login.getUserCredit() + amount); // Add the credit to the user's account
        }

        // Update user credit
        writeToDaily(username, userType, amount); // Call writeToDaily
        cout << amount << " credit(s) added to " << username << "'s account." << endl;
    } else {

        do {
            cout << "Enter the amount of credit to add:" << endl;
            getline(cin, amountInput);
            if (amountInput.empty()) {
                cout << "Amount cannot be empty." << endl;
                continue;
            }
            if (ip.ignoreCase(amountInput, "cancel")) {
                return;
            }
            try {
                amount = stod(amountInput);
                if (amount < 0) {
                    cout << "Error: Credit amount cannot be negative." << endl;
                    continue;
                }
                else if (amount > 999.99) {
                    cout << "Error: Credit amount cannot exceed 999.99." << endl;
                    continue;
                }
                else{
                    validAmount = true;
                }
            } catch (invalid_argument e) {
                cout << "Error: Credit amount must be a number." << endl;
            }
        } while (!validAmount);

        // Update user credit
        login.setUserCredit(login.getUserCredit() + amount);
        writeToDaily(login.getCurrentUser(), ip.typeUser(login.getUserLevel()), amount); 

        cout << amount << " credit(s) added to your account." << endl;
        cout << "Your current credit balance is: " << login.getUserCredit() << endl;
    }
    
}
