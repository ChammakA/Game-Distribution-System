#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <iomanip>
#include <sstream>
#include "../../include/transaction/transaction.h"
#include "../../include/session/session.h"
#include "../../include/user/user.h"
#include "../../include/game/game.h"

Transaction::Transaction(const std::string& codeStr, Session& session) : transactionCode(Transaction::parse_transaction_code(codeStr)), currentSession(session), successStatus(false) {}
Transaction::Transaction(TransactionCode& code, Session& session): transactionCode(code), currentSession(session), successStatus(false) {}

const std::unordered_map<std::string, TransactionCode> Transaction::transactionCodeMap = {
    {"login", TransactionCode::Login},
    {"logout", TransactionCode::Logout},
    {"create", TransactionCode::Create},
    {"delete", TransactionCode::Delete},
    {"sell", TransactionCode::Sell},
    {"buy", TransactionCode::Buy},
    {"refund", TransactionCode::Refund},
    {"addcredit", TransactionCode::AddCredit},
    {"list", TransactionCode::List},
    {"exit", TransactionCode::Exit},
    {"search", TransactionCode::Search}
};

TransactionCode Transaction::parse_transaction_code(const std::string& codeStr) {
    auto iter = transactionCodeMap.find(codeStr);
    return (iter != transactionCodeMap.end()) ? iter->second : TransactionCode::INVALID;
}

void Transaction::execute() {
    if (transactionFunctions.find(this->transactionCode) != transactionFunctions.end()) {
        this->transactionString = transactionFunctions.at(this->transactionCode)(*this);
    } else {
        std::cerr << "Invalid transaction code. Please try again." << std::endl;
    }
}

std::string Transaction::get_transaction_string() const { return this->transactionString; }

TransactionCode Transaction::get_transaction_code() const {return this->transactionCode; }

bool Transaction::success() const {return this->successStatus;}

bool Transaction::is_valid_code(const std::string& codeStr) {
    return Transaction::parse_transaction_code(codeStr) != TransactionCode::INVALID;
}

const std::unordered_map<TransactionCode, std::function<std::string(Transaction&)>> Transaction::transactionFunctions = {
    {TransactionCode::Login, Transaction::login},
    {TransactionCode::Logout, Transaction::logout},
    {TransactionCode::Create, Transaction::create_user},
    {TransactionCode::Delete, Transaction::delete_user},
    {TransactionCode::Sell, Transaction::sell},
    {TransactionCode::Buy, Transaction::buy},
    {TransactionCode::Refund, Transaction::refund},
    {TransactionCode::AddCredit, Transaction::add_credit},
    {TransactionCode::List, Transaction::list},
    {TransactionCode::Exit, Transaction::exit},
    {TransactionCode::Search, Transaction::search}
};

// Format Transaction String Functions

std::string Transaction::formatTransactionString(int code, const User &user) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << code << "_" << std::setw(USERNAME_FIELD_LENGTH) << std::setfill('_') << std::left << user.get_username() 
    << "_" << user.get_user_type() << "_" << std::setw(CREDIT_FIELD_LENGTH) 
    << std::setfill('0') << std::right << std::fixed << std::setprecision(2) << user.get_credit();  
    return ss.str();    // XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
}

std::string Transaction::formatTransactionString(int code, const std::string &buyerName, const std::string &sellerName, float credit) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << code << "_" << std::setw(USERNAME_FIELD_LENGTH) << std::setfill('_') << std::left << buyerName 
    << "_" << std::setw(USERNAME_FIELD_LENGTH) << std::setfill('_') << std::left << sellerName << "_" 
    << std::setw(CREDIT_FIELD_LENGTH) << std::setfill('0') << std::right << std::fixed << std::setprecision(2) << credit;  
    return ss.str();    // XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
}

std::string Transaction::formatTransactionString(int code, const std::string &gameName, const std::string &sellerName, const std::string &buyerName, float price) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << code << "_" << std::setw(GAME_NAME_FIELD_LENGTH) << std::setfill('_') << std::left << gameName
    << "_" << std::setw(USERNAME_FIELD_LENGTH) << std::setfill('_') << std::left << sellerName << "_"
    << std::setw(USERNAME_FIELD_LENGTH) << std::setfill('_') << std::left << buyerName << "_"
    << std::setw(GAME_PRICE_FIELD_LENGTH) << std::setfill('0') << std::right << std::fixed << std::setprecision(2) << price; 
    return ss.str();    // XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUUU_PPPPPP
}

std::string Transaction::formatSellTransactionString(int code, const std::string &gameName, const std::string &sellerName, float price) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << code << "_" << std::setw(GAME_NAME_FIELD_LENGTH) << std::setfill('_') << std::left << gameName
    << "_" << std::setw(USERNAME_FIELD_LENGTH) << std::setfill('_') << std::left << sellerName << "_"
    << std::setw(GAME_PRICE_FIELD_LENGTH) << std::setfill('0') << std::right << std::fixed << std::setprecision(2) << price; 
    return ss.str();    // XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSS_PPPPPP
}

// Transaction Functions

// maybe we do want failure codes even if they aren't written to the dtf?

std::string Transaction::login(Transaction& t) {
    if (t.currentSession.loggedIn) {
        std::cout << "User already logged in!" << std::endl;
        t.successStatus = false;
        return "";
    }

    std::string username;
    std::cout << "Please enter your username: ";
    std::cin >> username;

    // Log in the user by setting the current user to the user with the given username.
    t.currentSession.currentUser= t.currentSession.getUser(username);

    // Validate that the user is logged in.
    if (t.currentSession.currentUser.get_username() != "") {
        t.currentSession.loggedIn = true;
        t.successStatus = true;
        std::cout << "Welcome, " << t.currentSession.currentUser.get_username() + "." << std::endl;
    } else {
        // Write username with error message to console.
        std::cerr << "Invalid Username: " << username << " User not found." << std::endl;
    }

    return formatTransactionString(99, t.currentSession.currentUser);
}

std::string Transaction::logout(Transaction& t) {
    // Check that the user is logged in.
    if (!t.currentSession.loggedIn) {
        std::cerr << "Transaction failed: Please login before submitting transactions" << std::endl;
        return "";
    }

    t.currentSession.loggedIn = false;
    t.currentSession.ongoingSession = false;
    t.successStatus = true;
    std::cout << "Logout successful." << std::endl;

    return formatTransactionString(0, t.currentSession.currentUser);
}

std::string Transaction::create_user(Transaction& t) {
    // Check that the user is logged in.
    if (!t.currentSession.loggedIn) {
        std::cerr << "Transaction failed: Please login before submitting transactions" << std::endl;
        return "";
    }

    // Validate that the user is an admin user or Account Manager.
    if (t.currentSession.currentUser.get_user_type() != "AA" && t.currentSession.currentUser.get_user_type() != "AM") {
        std::cerr << "Error: Unauthorized. Only admin or account manager users can create accounts." << std::endl;
        return "";
    }

    // Prompt user for username
    std::string username;
    std::cout << "Enter username: ";
    std::cin >> username;

    // Validate that username does not exceed 15 characters
    if (username.length() > 15) {
        std::cerr << "Error: Username exceeds 15 characters." << std::endl;
        return "";
    }

    // Check if username already exists
    std::vector<Data<User>> users = t.currentSession.userAccountsFileManager.read();
    for (const auto& data : users) {
        User user = data.get_data();
        if (user.get_username() == username) {
            std::cerr << "Error: User already exists." << std::endl;
            return "";
        }
    }

    // Prompt user for user type
    std::string userType;
    std::cout << "Enter user type (AA, FS, BS, SS, AM): ";
    std::cin >> userType;

    // Validate user type
    if (userType != "AA" && userType != "FS" && userType != "BS" && userType != "SS" && userType != "AM") {
        std::cerr << "Error: The user type must be AA, FS, BS, SS, or AM." << std::endl;
        return "";
    }

    // Validate non-admin creation for Account Managers
    if (userType == "AA" && t.currentSession.currentUser.get_user_type() == "AM") {
            std::cerr << "Error: Account Managers cannot create an Admin user. user type must be FS, BS, SS, or AM." << std::endl;
            return "";
    }

    // Prompt user for credit
    float credit;
    std::cout << "Enter credit amount: ";
    std::cin >> credit;

    // Validate that entered credit amount does not exceed 999,999.99
    if (credit > MAX_CREDIT_LIMIT) {
        std::cerr << "Error: Credit amount cannot exceed $999,999.99." << std::endl;
        return "";
    }

    // Create user object
    User newUser = User(username, userType, credit);

    t.successStatus = true;

    // Return transaction string with logged in username, and the details of the new user.
    return formatTransactionString(1, newUser);
}

std::string Transaction::delete_user(Transaction& t) {
    // Check that the user is logged in as an admin
    if (!t.currentSession.loggedIn) {
        std::cerr << "Transaction failed: Please login before submitting transactions" << std::endl;
        return "";
    } else if (t.currentSession.currentUser.get_user_type() != "AA" && t.currentSession.currentUser.get_user_type() != "AM") {
        std::cerr << "Transaction failed: Only admin or account manager users can delete another user" << std::endl;
        return "";
    }
        // Prompt for a username
        std::string username;
        std::cout << "Enter username: ";
        std::cin >> username;
        if (t.currentSession.currentUser.get_username() == username) {
            std::cerr << "Transaction failed: You cannot delete your own account" << std::endl;
            return "";
        }

    // Search for the user in the user accounts file
    std::vector<Data<User>> users = t.currentSession.userAccountsFileManager.read();
    for (auto iter = users.begin(); iter != users.end(); ++iter) {
        // Only delete if: 
        //      1) we're an admin
        //      2) we're an account manager deleting a non-admin
        if ((t.currentSession.currentUser.get_user_type() == "AM" &&          
            iter->get_data().get_user_type() != "AA" && 
            iter->get_data().get_username() == username) ||                      
            (t.currentSession.currentUser.get_user_type() == "AA" &&
            iter->get_data().get_username() == username)) { 
            t.successStatus = true;
            std::cout << "Transaction complete: " + username + " successfully deleted." << std::endl;
            // return transaction string with the username of the deleted user
            return formatTransactionString(2, iter->get_data());
        } else if ((t.currentSession.currentUser.get_user_type() != "AA" &&          
            iter->get_data().get_user_type() == "AA" && 
            iter->get_data().get_username() == username)) {
                std::cerr << "Transaction failed: Only admin users can delete another admin user" << std::endl;
                return ""; 

            }
    }    

    // TODO: Should probably print can't find user to delete

    return "";
}

std::string Transaction::sell(Transaction& t) {
    // Check that the user is logged in.
    if (!t.currentSession.loggedIn) {
        std::cerr << "Transaction failed: Please login before submitting transactions" << std::endl;
        return "";
    }

    // Check that the user is not a buy standard user.
    if (t.currentSession.currentUser.get_user_type() == "BS") {
        std::cerr << "Unauthorized transaction: Buy-standard accounts are ineligble to put games up for sale." << std::endl;
        return "03_GAME_NOT_ADDED";
    }

    // Prompt for the name of the game to sell
    std::string gameName;
    std::cout << "Name of game for sale: " << std::flush;
    std::cin >> gameName;

    // Check that game name does not exceed 25 characters.
    if (gameName.length() > 25) {
        std::cerr << "Error: Game name exceeds 25 characters." << std::endl;
        return "03_GAME_NOT_ADDED";
    }

    // Check that the game name is not already in the available games file.
    std::vector<Data<Game>> games = t.currentSession.gamesFileManager.read();
    for (auto iter = games.begin(); iter != games.end(); ++iter) {
        if (iter->get_data().get_name() == gameName) {
            std::cerr << "Error: Game name already exists in the system." << std::endl;
            return "03_GAME_NOT_ADDED";
        }
    }

    // Prompt for the price of the game
    std::string priceStr;
    std::cout << "Sale price: " << std::flush;
    std::cin >> priceStr;

    // Validate that price is a float
    float price = 0.0;
    try {
        price = std::stof(priceStr);
    } catch (const std::exception& e) {
        std::cerr << "Invalid price. Please try again." << std::endl;
        return "03_GAME_NOT_ADDED";
    }

    if (price < 0) {
        std::cerr << "Error: Game price must be positive" << std::endl;
        return "";
    } else if (price > MAX_GAME_PRICE) {
        std::cerr << "Error: Game price cannot exceed $" << MAX_GAME_PRICE << "." << std::endl;
        return "";
    }

    // Create a game object
    Game newGame = Game(gameName, t.currentSession.currentUser.get_username(), price);

    std::cout << "Thank you, your game has been listed for sale!" << std::endl;
    t.successStatus = true;

    // Return transaction string with the details of the new game
    return formatSellTransactionString(3, newGame.get_name(), newGame.get_seller(), newGame.get_price());
}

std::string Transaction::buy(Transaction& t) {
    // Check that the user is logged in.
    if (!t.currentSession.loggedIn) {
        std::cerr << "Transaction failed: Please login before submitting transactions" << std::endl;
        return "";
    }

    // Check that the user is not a sell standard user.
    if (t.currentSession.currentUser.get_user_type() == "SS") {
        std::cerr << "Unauthorized transaction: Sell-standard accounts are ineligble to purchase games." << std::endl;
        return "04_GAME_NOT_PURCHASED";
    }

    // Prompt for the name of the game to buy
    std::string gameName;
    std::cout << "Name of game to buy: ";
    std::cin >> gameName;

    std::string transaction;
    bool found = false;

    // Search for the game in the available games file
    std::vector<Data<Game>> games = t.currentSession.gamesFileManager.read();
    for (auto game = games.begin(); game != games.end(); ++game) {
        if (game->get_data().get_name() == gameName) {
            

            // Check if the buyer has enough credit to purchase the game
            if (t.currentSession.currentUser.get_credit() < game->get_data().get_price()) {
                std::cerr << "Error: Insufficient credits." << std::endl;
                return "";
            }

            // Check that the user does not own the game by looping through game collection file.
            std::vector<Data<Collection>> gamesCollection = t.currentSession.gameCollectionFileManager.read();
            // If the current user already owns this game then we will send an error message to the console.
            for (auto iter = gamesCollection.begin(); iter != gamesCollection.end(); ++iter) {
                // Print the username and game name for debugging.
                // std::cout << "Username: " << iter->get_data().get_owner() << std::endl;
                // std::cout << "Game name: " << iter->get_data().get_game_name() << std::endl;

                if (iter->get_data().get_owner() == t.currentSession.currentUser.get_username() && iter->get_data().get_game_name() == gameName) {
                    std::cerr << "Error: Game already owned." << std::endl;
                    return "";
                }
            }

            // return transaction string with the name of the buyer, seller, the game, and the price.
            found = true;

            // TODO: should update the buyer's credit amount pretty sure (current session user credit), same reasons as below 
            transaction = formatTransactionString(4, game->get_data().get_name(), game->get_data().get_seller(), 
                t.currentSession.currentUser.get_username(), game->get_data().get_price());
        }
    }

    // If the game is not found, write an error message to the console.
    if (!found) {
        std::cerr << "Error: Game not found, please check your spelling." << std::endl;
        return "";
    }

    t.successStatus = true;

    // Print message game was purchased successfully.
    std::cout << "Game purchased, happy gaming!" << std::endl;

    // Otherwise, return the transaction string.
    return transaction;
}

std::string Transaction::refund(Transaction& t) {
    // Check that the user is logged in.
    if (!t.currentSession.loggedIn) {
        std::cerr << "Transaction failed: Please login before submitting transactions" << std::endl;
        return "";
    }

    // Check that the user is an admin or account manager
    if (t.currentSession.currentUser.get_user_type() != "AA" && t.currentSession.currentUser.get_user_type() != "AM")
    {
        std::cerr << "Permission Denied: You don't have access to this command" << std::endl;
        return "";
    } else {
        // If the logged in user is an admin, ask for the username of the buyer and the seller, and the amount of credit to refund.
        std::string buyer;
        std::cout << "Enter the buyer's username: ";
        std::cin >> buyer;

        // Validate that the buyer exists
        std::vector<Data<User>> users = t.currentSession.userAccountsFileManager.read();
        bool buyerExists = false;
        for (auto iter = users.begin(); iter != users.end(); ++iter) {
            if (iter->get_data().get_username() == buyer) {
                buyerExists = true;
                break;
            }
        }
        if (!buyerExists) {
            std::cerr << "Error: Buyer does not exist" << std::endl;
            return "";
        }

        std::string seller;
        std::cout << "Enter the seller's username: ";
        std::cin >> seller;

        // Validate that the seller exists.
        bool sellerExists = false;
        for (auto iter = users.begin(); iter != users.end(); ++iter) {
            if (iter->get_data().get_username() == seller) {
                sellerExists = true;
                break;
            }
        }
        if (!sellerExists) {
            std::cerr << "Error: Seller does not exist" << std::endl;
            return "";
        }

        // Prompt for the amount of credit to refund. 
        float credit;
        std::cout << "Enter the refund amount: ";
        try {
            // Validate that the credit is a float.
            std::cin >> credit;
            if (std::cin.fail()) {
                throw std::runtime_error("Invalid input. Please enter a numerical value.");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return "";
        }

        // Validate that the credit is a positive number.
        if (credit <= 0) {
            std::cerr << "Error: Credit must be a positive number." << std::endl;
            return "";
        }

        // Check that the seller has enough credit to refund
        for (auto iter = users.begin(); iter != users.end(); ++iter) {
            if (iter->get_data().get_username() == seller) {
                if (iter->get_data().get_credit() < credit) {
                    std::cerr << "Error: Seller does not have enough credit to refund." << std::endl;
                    return "";
                }
            }
        }

        
        // TODO: should update the buyer's credit amount (on the current session user) so addcredit and refund doesn't result in credit overflow
        t.successStatus = true;
        // return transaction string with the buyer, seller, and the amount of credit refunded.
        return formatTransactionString(5, buyer, seller, credit);
    }

    return "";
}

std::string Transaction::add_credit(Transaction &t)
{
    float credit;
    std::string creditStr;
    User *requester = &t.currentSession.currentUser;

    // If the logged in user is an admin, ask for the username and the amount of credit to add
    if (requester->get_user_type() == "AA" || requester->get_user_type() == "AM")
    {
        std::string username;
        std::cout << "Enter username to add credit to: ";
        std::cin >> username;

        // Search for the user in the current user file
        std::vector<Data<User>> users = t.currentSession.userAccountsFileManager.read();
        for (auto iter = users.begin(); iter != users.end(); ++iter)
        {
            if (iter->get_data().get_username() == username)
            {
                // Found user, prompt for credit amount
                std::cout << "Enter credit amount: ";
                std::cin >> creditStr;

                // Validate credit amount input
                try
                {
                    credit = std::stof(creditStr);
                    // Credit exceeds session limit
                    if (credit > SESSION_CREDIT_LIMIT)
                    {
                        std::cout << "Error: Credit amount exceeds user limit." << std::endl;
                        return "06_CREDIT_NOT_ADDED";
                    }
                    if (t.currentSession.get_session_credit() + credit > SESSION_CREDIT_LIMIT)
                    {
                        std::cout << "Error: Credit amount exceeds session limit." << std::endl;
                        return "06_CREDIT_NOT_ADDED";
                    }
                    if (credit <= 0)
                    {
                        std::cout << "Error: An invalid credit amount was entered." << std::endl;
                        return "06_CREDIT_NOT_ADDED";
                    }

                    float availableCredits = iter->get_data().get_credit();
                    // Credit is out of user bounds
                    if ((availableCredits + credit) > MAX_CREDIT_LIMIT)
                    {
                        std::cout << "Error: Credit amount exceeds user limit." << std::endl;
                        return "06_CREDIT_NOT_ADDED";
                    }

                    /// TODO: ADD SESSION CREDIT LIMIT OF 1000
                }
                catch (const std::exception &e) // Not a float
                {
                    std::cerr << "Error: Credit amount must be a number." << std::endl;
                    return "06_CREDIT_NOT_ADDED";
                }

                // Add credit to user
                iter->get_data().add_credit(credit);
                t.successStatus = true;
                std::cout << "Credit added successfully." << std::endl;
                // return transaction string with the username and available credit
                return formatTransactionString(6, iter->get_data().get_username(), iter->get_data().get_user_type(), credit);
            }
        }

        // User was not found
        std::cerr << "Error: Username was not found." << std::endl;
        return "06_CREDIT_NOT_ADDED";

        // Otherwise, ask for the credit amount and attempt to add it to the current user
    }
    else
    {
        std::cout << "Enter credit amount: ";
        std::cin >> creditStr;

        // Validate credit amount input
        try
        {
            credit = std::stof(creditStr);
            // Credit exceeds session limit
            if (credit > SESSION_CREDIT_LIMIT)
            {
                std::cout << "Error: Credit amount exceeds your session limit." << std::endl;
                return "06_CREDIT_NOT_ADDED";
            }
            if (t.currentSession.get_session_credit() + credit > SESSION_CREDIT_LIMIT)
            {
                std::cout << "Error: Credit amount exceeds session limit." << std::endl;
                return "06_CREDIT_NOT_ADDED";
            }
            if (credit <= 0)
            {
                std::cout << "Error: An invalid credit amount was entered." << std::endl;
                return "06_CREDIT_NOT_ADDED";
            }

            float availableCredits = requester->get_credit();
            // Credit is out of user bounds
            if ((availableCredits + credit) > MAX_CREDIT_LIMIT)
            {
                std::cout << "Error: Credit amount exceeds your account limit." << std::endl;
                return "06_CREDIT_NOT_ADDED";
            }

            /// TODO: ADD SESSION CREDIT LIMIT OF 1000
        }
        catch (const std::exception &e) // Not a float
        {
            std::cerr << "Error: Credit amount must be a number." << std::endl;
            return "06_CREDIT_NOT_ADDED";
        }

        // Passed validation, add credit to user
        requester->add_credit(credit);
        t.successStatus = true;
        std::cout << "Credit added successfully." << std::endl;
        // return transaction string with the username and the amount of credit added.
        return formatTransactionString(6, requester->get_username(), requester->get_user_type(), requester->get_credit());
    }
}

std::string Transaction::list(Transaction& t) {
    // Implement list

    // prompt user for list type
    if (t.currentSession.loggedIn) {
        std::string listType;
        std::cout << "What would you like to list (games, users): ";
        std::cin >> listType;

        // Write a switch statement that takes the list type and either executes the list of games or the list of users.
        if (listType == "games" || listType == "Games") {
            // read games file and print out the list of games
            std::cout << "List of games" << std::endl;
            std::vector<Data<Game>> games = t.currentSession.gamesFileManager.read();
            // Set the games variable to read from the games file and output it to the console.
            for (const auto& game : games) {
                std::cout << game.get_data().get_name() << " " << game.get_data().get_seller() << " " << game.get_data().get_price() << std::endl;
            }


        } else if (listType == "users" || listType == "Users") {
            // Do the same for users as games.
            if (t.currentSession.currentUser.get_user_type() == "AA" || t.currentSession.currentUser.get_user_type() == "AM") {                
                std::cout << "List of users" << std::endl;
                std::vector<Data<User>> users = t.currentSession.userAccountsFileManager.read();
                for (const auto& user : users) {
                    std::cout << user.get_data().get_username() << " " << user.get_data().get_user_type() << " " << user.get_data().get_credit() << std::endl;
                }
            } else {
                std::cerr << "Unauthorized transaction: Only admin accounts are eligible to list users." << std::endl;
                return "";
            }
        
        } else {
            std::cerr << "Invalid list type. Please try again." << std::endl;
            return "";
        }
    } else { // user tried to list without logging in first
        std::cerr << "Transaction failed: Please login before submitting transactions" << std::endl;
        return "";
    }

    t.successStatus = true;

    return formatTransactionString(7, t.currentSession.currentUser);
}

// function to search for users and games
std::string Transaction::search(Transaction &t){
     if (!t.currentSession.loggedIn) {
        std::cerr << "Transaction failed: Please login before submitting transactions" << std::endl;
        return "";
    }
    // Prompt user for search query
    std::string query;
    std::cout << "Enter the search query: ";
    std::getline(std::cin >> std::ws, query);

    std::transform(query.begin(), query.end(), query.begin(), ::tolower);

    //creat varaibles for later use
    std::string result;
    bool adminSell, userFound, gameFound;
    std::vector<Data<User>> users = t.currentSession.userAccountsFileManager.read();
    std::vector<Data<Game>> games = t.currentSession.gamesFileManager.read();

   
    // adds the users that contain the characters in the query
    result += "Users: \n";
    // goes through all users
    for (const auto& user: users){
        if (user.get_data().get_user_type() == "AA") { // if they are of admin type
            if (t.currentSession.currentUser.get_user_type() == "AA") { // and the current user is also and admin
                for (char c : query) {// add the result to the string
                    std::string username = user.get_data().get_username();
                    for (char& c : username){
                        c = std::tolower(c);
                    }
                    if (username.find(c) != std::string::npos){
                        result += user.get_data().get_username() + "\n";
                        break;
                    }
                
                }
            }
            else { // if the curent user, is not admin then do not add those users
                adminSell = false;
                for (const auto& game: games){ 
                    if (game.get_data().get_seller() == user.get_data().get_username()){ // unless they are selling a game
                        adminSell = true;
                        break;
                    }
                }
                if (adminSell){
                    result += user.get_data().get_username() + "\n";
                    break;
                }
            }
        }
        else { // if the user is not an admin type
            userFound = false;
            for (char c : query){ // searches for if the username contains the characters in the query
                std::string username = user.get_data().get_username();
                for (char& c : username){
                    c = std::tolower(c);
                }
                if (username.find(c) != std::string::npos){
                    userFound = true;
                    break;
                }
            }
            if (userFound){ // if they do add it to result
                result += user.get_data().get_username() + "\n";
            }
        }
    }
    // now adding onto the games
    result += "\nGames: \n";
    // go through all games
    for (const auto& game: games){
        gameFound = false;
        // if the game name contains the characters in the query
        for (char c : query) {
            std::string gameName = game.get_data().get_name();
            for (char& c : gameName){
                c = std::tolower(c);
            }
            if (gameName.find(c) != std::string::npos){
                gameFound = true;
                break;
            }
        }
        if (gameFound){
            result += game.get_data().get_name() + "\n"; // add it to the result
        }
    }
    std::cout << result << std::endl; // print the result
    return formatTransactionString(8, t.currentSession.currentUser);
}

std::string Transaction::exit(Transaction& t) {
    // Check if the user is logged in. If not, return an empty string. Otherwise, call logout.
    if (!t.currentSession.loggedIn) {
        t.currentSession.ongoingSession = false;
        return "";
    } else {
        return Transaction::logout(t);
    }
}