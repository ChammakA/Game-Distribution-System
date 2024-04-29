#include "Refund.h"
#include "inputProcessor.h"

#include <fstream>
#include <iomanip>
#include <sstream>

void Refund::writeToDaily(const string& username, const string& seller, double price){
    ofstream dailyTransaction;
    dailyTransaction.open(dailyTransactionFilePath, ios::app);

    if (!dailyTransaction.is_open()){ // Error handling for file not opening
        cout << "Error: Buy Daily Transaction File was not able to be opened." << endl;
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
    string sellerAsString = seller;

    if (user.length() < 15){
        user = user + string(15 - user.length(), '_');
    }
    if (sellerAsString.length() < 15){
        sellerAsString = sellerAsString + string(15 - sellerAsString.length(), '_');
    }

    user.resize(15, '_');
    sellerAsString.resize(15, '_');

    dailyTransaction << "05_" << user << "_" << sellerAsString << "_" << priceAsString << endl;
    dailyTransaction.close();
}

// Function to handle refund
void Refund::refundTransaction() {
    inputProcessor ip;
    vector<userAccountsInfo> userAccounts = ip.readUserAccounts(); // Reads the user accounts file

    string amountInput;
    double amount;
    bool validAmount = false;

    bool buyerExists = false;
    bool sellerExists = false; 

    do {
        cout << "Enter the Buyer's username:" << endl;
        getline(cin, BuyerName);

        if (BuyerName.empty()) {
            cout << "Error: Buyer's username cannot be empty." << endl;
            continue;
        }
        if (ip.ignoreCase(BuyerName, "cancel")) {
                return;
        }
        if (ip.isCommand(BuyerName)) {
            continue;
        }
        
        for (auto user : userAccounts) {
            if (user.username == BuyerName && user.userType != "SS") {
                buyerExists = true;
                continue;
            }
        }
        if (!buyerExists){
            cout << "Error: Not a valid Buyer. ";
            continue;
        }
    } while(!buyerExists);

    do {
        cout << "Enter the Seller's username:" << endl;
        getline(cin, SellerName);

        if (SellerName.empty()) {
            cout << "Error: Seller's username cannot be empty." << endl;
            continue;
        }
        if (ip.ignoreCase(SellerName, "cancel")) {
                return;
        }
        if (ip.isCommand(SellerName)) {
            continue;
        }
        if (ip.ignoreCase(SellerName, BuyerName)){ // Error handling for empty input
            cout << "Error: Seller must be different from Buyer" << endl;
            continue;
        }
        for (auto user : userAccounts) {
            if (user.username == SellerName && user.userType != "BS") {
                sellerExists = true;
                continue;
            }
        }
        
        
        if (!sellerExists){
            cout << "Error: Not a valid Seller. " << endl;
            continue;
        }
    } while(!sellerExists);

    // Ask for the amount of credit to transfer
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
                else if (amount > 999.99){
                    cout << "Error: Credit amount cannot be more than 999.99." << endl;
                    continue;
                }
                else{
                    validAmount = true;
                }
            } catch (invalid_argument e) {
                cout << "Error: Credit amount must be a number." << endl;
            }
        } while (!validAmount);

    // Add the specified amount to the buyer's credit balance

    writeToDaily(BuyerName, SellerName, amount);
    cout << amount << " credit(s) will be refunded to " << BuyerName << " from " << SellerName << endl;

    
}