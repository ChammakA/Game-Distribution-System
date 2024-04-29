#include "inputProcessor.h"
#include "main.h"
#include <algorithm>
#include <fstream>

set<string> inputProcessor::deletedUsers; // set to store deleted users

// Function to read the available games file and store the values into a vector
vector<gamesAvailableInfo> inputProcessor::readAvailableGames(){
    ifstream availableGamesFile(availableGamesFilePath); // Opens the file in location
    if (!availableGamesFile.is_open()) { // Error handling for file not opening
        cerr << "Error: Available Games File was not able to be opened." << endl;
        return {};
    }
    
    vector<gamesAvailableInfo> availableGamesList; // creates a vector to store the available games
    string line;
    
    while (getline(availableGamesFile, line)) {
        replace(line.begin(), line.end(), '_', ' '); // Replaces the underscores with spaces for formatting
        size_t gamePos = line.find("  "); // Finds the position of the game name ending

        if (gamePos == string::npos){ // If the game name end is not found, the file is not formatted correctly
            cerr << "Error: Invalid Availabel Games File formatting. Type: Game." << endl;
            availableGamesFile.close();
            return {};
        }
        string game = line.substr(0, gamePos); // Gets the game name
        if (game == "END") { // if the game name is END, the file is done being read
            availableGamesFile.close();
            return availableGamesList;
        }

        size_t sellerPos = line.find_first_not_of(" ", gamePos + 1); // Finds the position of the seller name
        if (sellerPos == string::npos) { // if the seller name is not found, the file is not formatted correctly
            cerr << "Error: Invalid Availabel Games File formatting. Type: Seller." << endl;
            availableGamesFile.close();
            return {};
        }
        string seller = line.substr(sellerPos, line.find(" ", sellerPos) - sellerPos); // Gets the seller name

        size_t pricePos = line.rfind(" "); // Finds the position of the price
        if (pricePos == string::npos) { // if the price is not found, the file is not formatted correctly
            cerr << "Error: Invalid Availabel Games File formatting. Type: Price." << endl;
            availableGamesFile.close();
            return {};
        }
        double price = stod(line.substr(pricePos + 1)); // Gets the price
        availableGamesList.push_back({game, seller, price}); // Adds the game to the vector
    }
    availableGamesFile.close(); // Closes the file
    return availableGamesList; // Returns the vector
}

// Function to read the available games file and store the values into a vector
vector<gameCollectionInfo> inputProcessor::readGameCollection(){
    ifstream gameFile(gameCollectionFilePath); // Opens the file in location

    if (!gameFile.is_open()) { // Error handling for file not opening
        cerr << "Error: Game Collection File was not able to be opened." << endl;
        return {};
    }

    vector<gameCollectionInfo> gameCollectionList; // creates a vector to store the game collection
    string line;
    while (getline(gameFile, line)) {

        replace(line.begin(), line.end(), '_', ' '); // Replaces the underscores with spaces for formatting
        size_t gamePos = line.find("  "); // Finds the position of the game name ending

        if (gamePos == string::npos){ // If the game name end is not found, the file is not formatted correctly
            cout << "Error: Invalid Game Collection File formatting. TYPE: GAME." << endl;
            gameFile.close();
        }

        string game = line.substr(0, gamePos); // Gets the game name
        if (game == "END") { // if the game name is END, the file is done being read
            gameFile.close();
            return gameCollectionList;
        }

        size_t ownerPos = line.find_first_not_of(" ", gamePos + 1); // Finds the position of the seller name
        if (ownerPos == string::npos) { // if the seller name is not found, the file is not formatted correctly
            cerr << "Error: Invalid Game Collection File formatting. TYPE: OWNER." << endl;
            gameFile.close();
            return {};
        }
        string owner = line.substr(ownerPos, line.find(" ", ownerPos) - ownerPos); // Gets the seller name
        gameCollectionList.push_back({game, owner}); // Adds the game to the vector
    }
    gameFile.close(); // Closes the file
    return gameCollectionList; // Returns the vector
}

// Function to read the current accounts file and store the values into a vector
vector<userAccountsInfo> inputProcessor::readUserAccounts(){
    ifstream userFile(userAccountsFilePath); // Opens the file in locationh

    if (!userFile.is_open()) { // Error handling for file not opening
        cerr << "Error: User Accounts File was not able to be opened at:" << userAccountsFilePath << endl;
        return {};
    }
    vector<userAccountsInfo> userAccountsList; // creates a vector to store the user accounts
    string line;
    while (getline(userFile, line)) { // Goes through each line of the file and stores the user accounts

        size_t userPos = line.find('_'); // finds the position of the username ending

        if (userPos == string::npos) { // if the username end is not found, the file is not formatted correctly
            cerr << "Error: Invalid User Accounts File formatting. Type: USER." << endl;
            userFile.close();
            return {};
        }
        string user = line.substr(0, userPos); // Gets the username
        if (user == "END") { // if the username is END, the file is done being read
            userFile.close();
            return userAccountsList;
        }

        size_t typePos = line.find_first_not_of('_', userPos + 1); // finds the position of the user type
        if (typePos == string::npos) { // if the user type is not found, the file is not formatted correctly
            cerr << "Error: Invalid User Accounts File formatting. Type: TYPE." << endl;
            userFile.close();
            return {};
        }
        string userType = line.substr(typePos, line.find('_', typePos) - typePos); // Gets the user type

        size_t creditPos1 = line.rfind('_'); // finds the position of the user credit
        if (creditPos1 == string::npos) { // if the user credit is not found, the file is not formatted correctly
            cerr << "Error: Invalid User Accounts File formatting. Type: CREDIT." << endl;
            userFile.close();
            return {};
        }
        double credits = stod(line.substr(creditPos1 + 1)); // Gets the user credit
        userAccountsList.push_back({user, userType, credits}); // Adds the user to the vector
    }
    userFile.close(); // Closes the file
    return userAccountsList; // Returns the vector
}

// Function to convert user type from 2 letter code to string value
string inputProcessor::typeUser(const string& abbreviation) {
    if (abbreviation == "SS") {
        return "Sell Standard";
    } else if (abbreviation == "BS") {
        return "Buy Standard";
    } else if (abbreviation == "FS") {
        return "Full Standard";
    } else if (abbreviation == "AA") {
        return "Admin";
    } 
    else if(abbreviation == "Sell Standard"){
        return "SS";
    } else if(abbreviation == "Buy Standard"){
        return "BS";
    } else if(abbreviation == "Full Standard"){
        return "FS";
    } else if(abbreviation == "Admin"){
        return "AA";
    } else{
        cout << "Error: User type is not a registered type." << endl;
        return "Unknown";
    }
}

// function to ignore case when comparing strings
bool inputProcessor::ignoreCase(string s1, string s2){ 
        transform(s1.begin(), s1.end(), s1.begin(), ::tolower); //using transform to convert the strings to lowercase
        transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
        if (s1 == s2){
            return true;
        }
        else{
            return false;
        }
}

bool inputProcessor::nonASCII(const string& input){
    for (char c : input){
        if (c < 0 || c > 127){
            return true;
        }
    }
    return false;
}



// function to check if input is valid command based on user type
bool inputProcessor::isValidInput(const string& input, const string& userLevel) {
    const vector<string>& commands = (userLevel == "Admin") ? adminCommands :
                                      (userLevel == "Buy Standard") ? buyCommands :
                                      (userLevel == "Sell Standard") ? sellCommands :
                                      fullCommands;
    if (input.empty()){
        cout << "Input cannot be empty." << endl;
        return false;
    }

    for (const string& cmd : commands) {
        if (ignoreCase(input, cmd)) {
            if (!ignoreCase(input, "logout") && !ignoreCase(input, "list") && !ignoreCase(input, "profiles")) {
                cout << cmd << " command accepted. (Type Cancel to terminate the process)\n";
                return true;
            }
            cout << cmd << " command accepted.\n";
            return true;
        }
        else{
            continue;
        }
    }

    cout << "This is not a valid command. ";
    return false;
}

bool inputProcessor::isCommand(const string& input){
    if (ignoreCase(input, "logout")){
        cout << "Error: Input cannot be 'logout'." << endl;
        return true;
    }
    else if (ignoreCase(input, "login")){
        cout << "Error: Input cannot be 'login'." << endl;
        return true;
    }
    else if (ignoreCase(input, "create")){
        cout << "Error: Input cannot be 'create'." << endl;
        return true;
    }
    else if (ignoreCase(input, "delete")){
        cout << "Error: Input cannot be 'delete'." << endl;
        return true;
    }
    else if (ignoreCase(input, "buy")){
        cout << "Error: Input cannot be 'buy'." << endl;
        return true;
    }
    else if (ignoreCase(input, "sell")){
        cout << "Error: Input cannot be 'sell'." << endl;
        return true;
    }
    else if (ignoreCase(input, "addcredit")){
        cout << "Error: Input cannot be 'addcredit'." << endl;
        return true;
    }
    else if (ignoreCase(input, "refund")){
        cout << "Error: Input cannot be 'refund'." << endl;
        return true;
    }
    else if (ignoreCase(input, "list")){
        cout << "Error: Input cannot be 'list'." << endl;
        return true;
    }
    else if (ignoreCase(input, "profiles")){
        cout << "Error: Input cannot be 'profiles'." << endl;
        return true;
    }
    else{
        return false;
    }
}
