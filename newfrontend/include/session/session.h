// Session.h
#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "../file/file_manager.h"
#include "../user/user.h"
#include "../game/game.h"
#include "../file/user_accounts/user_accounts.h"
#include "../file/available_games/available_games.h"
#include "../file/game_collection/game_collection.h"
#include "../file/daily_transaction/daily_transaction.h"
#include "../user/user.h"
#include "../transaction/transaction.h"

#define SESSION_CREDIT_LIMIT 1000.00

class Transaction;  // Forward Declaration

/**
 * @brief Class that represents a session.
 */
class Session {
public:
    /**
     * @brief Constructor for Session class.
     * @param userAccountsFileManager The user accounts file manager.
     * @param gamesFileManager The available games file manager.
     */
    Session(UserAccountsFileManager &uafm, AvailableGamesFileManager &gfm, GameCollectionFileManager &gcfm, DailyTransactionFileManager &dtfm);

    /**
     * @brief Start method for the session.
     */
    void start();

    void add_to_session_credit(float credit);
    float get_session_credit() const;
    
private:
    UserAccountsFileManager &userAccountsFileManager; 
    AvailableGamesFileManager &gamesFileManager;
    GameCollectionFileManager &gameCollectionFileManager;
    DailyTransactionFileManager &dailyTransactionFileManager;
    User currentUser;
    bool loggedIn;   // whether a user is logged into the session or not
    std::vector<Transaction> sessionTransactions;
    bool ongoingSession;
    float sessionCredit = 10.00;

    /**
     * @brief Process transaction method for the session.
     * @param transactionCode The transaction code to be processed.
     */
    void processTransaction(const std::string& transactionCode);

    /**
     * @brief Get user method for the session.
     * @param username The username of the user.
     * @return The user object.
     */
    User getUser(const std::string& username);

    /**
     * @brief Verifies the files associated with each file manager to see if they are valid for processing. Terminates the session if all are not found to be valid.
     * 
     */
    void verifyFiles();

    friend class Transaction;
};


#endif // SESSION_H
