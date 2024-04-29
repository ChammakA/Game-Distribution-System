#include "Sell.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>


void Sell::writeToDaily(const string& gameName, const string& seller, double price){
    ofstream dailyTransaction;
    dailyTransaction.open(dailyTransactionFilePath, ios::app);

    if (!dailyTransaction.is_open()){ // Error handling for file not opening
        cout << "Error: Sell Daily Transaction File was not able to be opened." << endl;
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

    string game = gameName;
    string sellerAsString = seller;


    if (game.length() < 25){
        game = game + string(25 - game.length(), '_');
    }
    if (sellerAsString.length() < 15){
        sellerAsString = sellerAsString + string(15 - sellerAsString.length(), '_');
    }

    game.resize(25, '_');
    sellerAsString.resize(15, '_');

    dailyTransaction << "03_" << game << "_" << sellerAsString << "_" << priceAsString << endl;
    dailyTransaction.close();
}

bool Sell::alreadyAvailable(const string& gameName){
    inputProcessor ip;
    vector<gamesAvailableInfo> gameList = ip.readAvailableGames(); // Read the user accounts file
    for (int i = 0; i < gameList.size(); i++){
        if (ip.ignoreCase(gameList[i].gameName, gameName)){
            cout << "Error: Game is already available for sale." << endl;
            return true;
        }
    }
    return false;
}

void Sell::sellGame(){
    inputProcessor ip;
    
    vector<gamesAvailableInfo> gameList = ip.readAvailableGames(); // Read the user accounts file
    
    string gameInput;
    string priceInput;
    double amount = -1;
    bool gameListed = false;
    bool priceValid = false;

    do {
        cout << "Please enter the name of the game you wish to sell:  " << endl;
        getline(cin, gameInput); //stores the input game name

        if (gameInput.empty()){
            cout << "Error: Game name must be atleast 1 character." << endl;
        }
        else if (ip.ignoreCase(gameInput, "cancel")){
            return;
        }
        else if(ip.isCommand(gameInput)){
            continue;
        }
        else if (gameInput.size() > 25){
            cout << "Error: Game name cannot be more than 25 characters." << endl;
            continue;
        }
        else if (ip.nonASCII(gameInput)){
            cout << "Error: Game name cannot contain non-ASCII characters." << endl;
            continue;
        }
        else if (alreadyAvailable(gameInput)){
            continue;
        }
        else{
            gameListed = true;
        }
    } while (!gameListed);

    do {
        cout << "Please enter the price you wish to sell it at:  (Between 0 - 1000)" << endl;
        getline(cin, priceInput); //stores the input price
        
        if (priceInput.empty()){
            cout << "Error: Price must be atleast 1 character." << endl;
        }
        else if (ip.ignoreCase(priceInput, "cancel")){
            return;
        }
        try {
            amount = stod(priceInput);
            if (amount < 0) {
                cout << "Error: Credit amount cannot be negative." << endl;
                continue;
            }
            else if (amount > 999.99){
                cout << "Error: Price cannot be more than 999.99." << endl;
                continue;
            }
            else{
                priceValid = true;
            }
        } catch (invalid_argument e) {
            cout << "Error: Credit amount must be a number." << endl;
        } catch (out_of_range e){
            cout << "Error: Credit amount must be a number." << endl;
        }
                
    } while (!priceValid);

    cout << "Game '" << gameInput << "' has been listed for sale at " << amount << " credits." << endl;
    writeToDaily(gameInput, login.getCurrentUser(), amount); // Call writeToDaily

}