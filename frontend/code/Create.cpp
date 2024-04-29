#include "Create.h"
#include <iostream>
#include <algorithm>
#include <fstream>

// Function to check if the type is valid
bool Create::isValidType(const string& type) {
    return (type == "AA" || type == "FS" || type == "BS" || type == "SS");
}


//function to write to the daily transaction file
void Create::writeToDaily(const string& user, const string& type){
    ofstream dailyTransaction;
    dailyTransaction.open(dailyTransactionFilePath, ios::app);

    if (!dailyTransaction.is_open()){ // Error handling for file not opening
        cout << "Error: Create Daily Transaction File was not able to be opened." << endl;
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

    dailyTransaction << "01_" << userAsString << "_" << typeAsString << "_000.00" << endl;
    dailyTransaction.close();
}


// Function to create a user
void Create::createUser() {
    inputProcessor ip;
    vector<userAccountsInfo> userAccounts = ip.readUserAccounts(); // Reads the user accounts file
    
    string userInput;
    string typeInput;

    bool userExists;
    bool validType = false;

    do {
        userExists = false;
        cout << "Please enter the username of the account being created:" << endl;
        getline(cin, userInput);

        if (userInput.empty()) {
            cout << "Error: Username cannot be empty." << endl;
            userExists = true;
            continue;
        }
        if (ip.ignoreCase(userInput, "cancel")){ // Checks to see if user wants to cancel
            return;
        }
        if (ip.isCommand(userInput)) { // Checks to see if the input is a command
            userExists = true;
            continue;
        }
        if (userInput.length() > 15) {
            cout << "Error: Username cannot be longer than 15 characters." << endl;
            userExists = true;
            continue;
        }
        if (userInput.find_first_of(" ") != string::npos) {
            cout << "Error: Username cannot contain spaces." << endl;
            userExists = true;
            continue;
        }
        if (userInput.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) {
            cout << "Error: Username can only contain letters and numbers." << endl;
            userExists = true;
            continue;
        }
        
        for (auto user : userAccounts) {
            if (user.username == userInput) {
                userExists = true;
                continue;
            }
        }
        if (userExists) {
            cout << "Error: Username already exists. " << endl;
        }

    } while(userExists);

    do {
        cout << "Please enter the type of the user. (AA - Admin, FS - Full-Standard, BS - Buy-Standard, SS - Sell-Standard):" << endl;
        getline(cin, typeInput);

        if (userInput.empty()) {
            cout << "Error: Type cannot be empty." << endl;
            continue;
        }
        if (ip.ignoreCase(typeInput, "cancel")){ // Checks to see if user wants to cancel
            return;
        }
        if (ip.isCommand(typeInput)) { // Checks to see if the input is a command
            userExists = true;
            continue;
        }
        transform(typeInput.begin(), typeInput.end(), typeInput.begin(), ::toupper);
        if (typeInput == "ADMIN"){
            typeInput = "AA";
        } else if (typeInput == "FULL STANDARD"){
            typeInput = "FS";
        } else if (typeInput == "BUY STANDARD"){
            typeInput = "BS";
        } else if (typeInput == "SELL STANDARD"){
            typeInput = "SS";
        }
        if (!isValidType(typeInput)) {
            cout << "Error: Invalid user type." << endl;
        } else {    
            validType = true;
        }
    } while(!validType);

    cout << ip.typeUser(typeInput) << " user: " << userInput << " has been created." << endl;
    writeToDaily(userInput, typeInput); // Writes to the daily transaction file
}
