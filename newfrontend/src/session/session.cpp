#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../include/file/file_manager.h"
#include "../../include/user/user.h"
#include "../../include/game/game.h"
#include "../../include/file/user_accounts/user_accounts.h"
#include "../../include/file/available_games/available_games.h"
#include "../../include/file/daily_transaction/daily_transaction.h"
#include "../../include/session/session.h"
#include "../../include/transaction/transaction.h"

Session::Session(UserAccountsFileManager &uafm, AvailableGamesFileManager &gfm, GameCollectionFileManager &gcfm, DailyTransactionFileManager &dtfm) 
    : userAccountsFileManager(uafm), gamesFileManager(gfm), gameCollectionFileManager(gcfm), dailyTransactionFileManager(dtfm), ongoingSession(true), 
    loggedIn(false) {
    }

void Session::add_to_session_credit(float credit) {
    sessionCredit += credit;
}

float Session::get_session_credit() const {
    return sessionCredit;
}

void Session::start() {
    verifyFiles();

    std::string command;
    while (ongoingSession) {
        std::cout << "Enter command: ";
        std::cin >> command;
        // Convert command to lowercase
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        processTransaction(command);
    }

    // Get the transaction strings
    std::vector<Data<std::string>> transactionStrings;
    for(const auto &t : sessionTransactions) {
        transactionStrings.push_back(Data<std::string>(t.get_transaction_string()));
    }

    if (transactionStrings.size() > 0) dailyTransactionFileManager.write(transactionStrings);
}

void Session::processTransaction(const std::string& transactionCode) {
    // Perform transactions based on user type and transaction code
    if (!Transaction::is_valid_code(transactionCode)) {
        std::cerr << "Invalid transaction code. Please try again." << std::endl;
        return;
    } /*else if (!loggedIn && transactionCode != "login") {   // TODO: maybe change so that transaction handles this?
        std::cerr << "Invalid operation: user not logged in." << std::endl;
        return;
    } */

    Transaction t = Transaction(transactionCode, *this);

    t.execute();

    if (t.success()) {
        sessionTransactions.push_back(t);
    }
}

User Session::getUser(const std::string& username) {
    // Read user accounts file and check if the username exists
    std::vector<Data<User>> users = userAccountsFileManager.read();
    for (const auto& user : users) {
        if (user.get_data().get_username() == username) {
            return user.get_data();
        }
    }
    return User(); // Return an empty User object if the username does not exist
}

void Session::verifyFiles() {
    userAccountsFileManager.read();
    gamesFileManager.read();
    gameCollectionFileManager.read();
    dailyTransactionFileManager.read();

    
    if (!(userAccountsFileManager.isValid() && gamesFileManager.isValid() && gameCollectionFileManager.isValid() 
        && gameCollectionFileManager.isValid() && dailyTransactionFileManager.isValid())) {
            ongoingSession = false;
    }
}