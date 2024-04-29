#include "Buy.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <sstream>


// Function to write to daily transaction file
void Buy::writeToDaily(const string& gameName, const string& seller, double price, const string& buyer){
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

    string game = gameName;
    string buyerAsString = buyer;
    string sellerAsString = seller;
    
    replace(game.begin(), game.end(), ' ', '_');

    if (buyerAsString.length() < 15){
        buyerAsString = buyerAsString + string(15 - buyerAsString.length(), '_');
    }
    if (sellerAsString.length() < 15){
        sellerAsString = sellerAsString + string(15 - sellerAsString.length(), '_');
    }

    game.resize(25, '_');
    sellerAsString.resize(15, '_');
    buyerAsString.resize(15, '_');

    dailyTransaction << "04_" << game  << "_" << sellerAsString << "_" << buyerAsString << "_" << priceAsString << endl;
    dailyTransaction.close();
}

// Function to check if user already owns the game returns true if the user already owns the game
bool Buy::alreadyOwns(const string& game){
    inputProcessor ip;
    vector<gameCollectionInfo> gameList = ip.readGameCollection(); // Read the user accounts file
    for (auto gameInfo : gameList) {
        if (gameInfo.gameName == game && gameInfo.owner == login.getCurrentUser()) {
            return true;
        }
    }
    return false;
}

// Function to buy a game
void Buy::buyGame(){
    inputProcessor ip;
    vector<gamesAvailableInfo> gameList = ip.readAvailableGames(); // Read the user accounts file

    bool gameExists = false; // Base case for game not existing
    bool sellerExists = false; // Base case for seller not existing
    string inputGameName; // Variable to store the input game name
    string inputSeller; // Variable to store the input seller name
    int gameIndex; // Variable to store the index of the game in the list
    // Loop for user to input the game name
    do{ 
        cout << "Please enter the name of the game you wish to buy:" << endl;
        getline(cin, inputGameName); //stores the input game name

        if (inputGameName.empty()){ // Error handling for empty input
            cout << "Error: Game name must be atleast 1 character." << endl;
            continue;
        }
        else if (ip.ignoreCase(inputGameName, "cancel")){ // Checks to see if user wants to cancel
            return;
        }
        else if (ip.nonASCII(inputGameName)){ // Error handling for Non- ASCII characters
            cout << "Error: Game name cannot contain non-ASCII characters." << endl;
            continue;
        }
        else if(inputGameName.size() > 25){ // Error handling for game name being too long
            cout << "Error: Game name cannot be more than 25 characters." << endl;
            continue;
        }
        else if(alreadyOwns(inputGameName)){ //  Error handling for user already owning the game
            cout << "Error: You already own this game." << endl;
            continue;
        }

        auto existing = find_if(gameList.begin(), gameList.end(), [&](const gamesAvailableInfo& gameInfo) {
            return gameInfo.gameName == inputGameName;} ); // Checks if the game exists

        if (existing == gameList.end()){ // Error handling for game not existing
            cout << "Error: It seems that game does not exist." << endl;
            continue;
        }
        else{ // If the game exists, the game is set as existing and the index is stored
            gameExists = true;
            gameIndex = distance(gameList.begin(), existing);
        }
        
    } while (!gameExists);
    
    
    // Loop for user to input the seller name
    do{
        cout << "Please enter the seller of that game:" << endl;
        getline(cin, inputSeller); //stores the input seller name

        if (inputSeller.empty()){ // Error handling for empty input
            cout << "Error: Seller name must be atleast 1 character." << endl;
            continue;
        }
        else if (ip.ignoreCase(inputSeller, "cancel")){ // Checks to see if user wants to cancel
            return;
        }
        
        if (inputSeller != gameList[gameIndex].seller){ // Error handling for incorrect seller
            cout << "Error: Seems like this is not the seller of this game." << endl;
            continue;
        }
        
        if(ip.isDeletedUser(inputSeller)){ // Error handling for seller being deleted
            cout << "Seems like this seller may have been deleted." << endl;
            return;
        }
        sellerExists = true;
    } while(!sellerExists);

    if (login.getUserCredit() < gameList[gameIndex].price){ // Error handling for user not having enough credit
        cout << "Error: You do not have enough credit to buy this game." << endl;
        return;
    }
    else{ // If the user has enough credit, the game is bought and the user's credit is updated
        login.setUserCredit(login.getUserCredit() - gameList[gameIndex].price);
        cout << "Current Balance: " << login.getUserCredit() << endl; //output current balance
        cout << "Congratulations "<< login.getCurrentUser() <<". You have successfully bought " << inputGameName 
        << " from " << inputSeller << endl; //output successful purchase
        writeToDaily(inputGameName, inputSeller, gameList[gameIndex].price, login.getCurrentUser()); //writes to daily transaction file
    }

}