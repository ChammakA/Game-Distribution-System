/*
* This program is designed to manage user accounts, available games, and game collections.
* It allows users to create accounts, browse and purchase available games, and manage their game collections.
* 
* Input Files:
* - user_accounts.txt: Contains user account information.
* - games.txt: Contains information about available games.
* - game_collection.txt: Contains information about users' game collections.
* 
* Output Files:
* - user_accounts.txt: Updated user account information.
* - games.txt: Updated information about available games.
* - game_collection.txt: Updated information about users' game collections.
* 
* To run the program, execute the main function. It will initialize the necessary file managers,
* create a session, and start the session. The session will prompt the user for actions and
* perform the corresponding operations based on user input.
*/

#include <iostream>
#include <string>
#include <chrono>
#include "../include/session/session.h"
#include "../include/file/game_collection/game_collection.h"
#include "../include/file/user_accounts/user_accounts.h"
#include "../include/file/available_games/available_games.h"
#include "../include/file/daily_transaction/daily_transaction.h"

#define STORAGE_PATH "./storage/"

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 4 && argc != 5) {
        std::cout << "Usage: ./program <user_accounts_file> <available_games_file> <game_collection_file> [daily_transaction_file]\n";
        return 1;
    }
    
    // Get the file names from the command line arguments
    std::string userAccountsFile = STORAGE_PATH + std::string(argv[1]);
    std::string availableGamesFile = STORAGE_PATH + std::string(argv[2]);
    std::string gameCollectionFile = STORAGE_PATH + std::string(argv[3]);

    // Get the current time to append to daily transaction file
    auto now = std::chrono::system_clock::now();
    auto utc = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    // set daily transaction file name with current time (for this session)
    std::string dailyTransactionFile = argc == 5 ? DAILY_TRANSACTION_FILE_LOCATION + std::string(argv[4]) 
        : (std::string)DAILY_TRANSACTION_FILE_LOCATION + "daily_transaction_" + std::to_string(utc) + ".txt";   // use generated if argument not provided

    // Initialize file managers
    UserAccountsFileManager userAccountsFileManager = UserAccountsFileManager(userAccountsFile);
    AvailableGamesFileManager gamesFileManager = AvailableGamesFileManager(availableGamesFile);
    GameCollectionFileManager gameCollectionFileManager = GameCollectionFileManager(gameCollectionFile);
    DailyTransactionFileManager dailyTransactionFileManager = DailyTransactionFileManager(dailyTransactionFile);

    // Initialize session
    Session session(userAccountsFileManager, gamesFileManager, gameCollectionFileManager, dailyTransactionFileManager);

    // Start session
    session.start();

    return 0;
}