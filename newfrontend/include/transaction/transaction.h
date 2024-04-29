
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <unordered_map>
#include <string>
#include <functional>
#include "../session/session.h"
#include "../user/user.h"

class Session;  // Forward Declaration

/**
 * @brief Allowed transaction code names for the system
 * 
 */
enum class TransactionCode {
    INVALID,
    Login,
    Logout,
    Create,
    Delete,
    Sell,
    Buy,
    Refund,
    AddCredit,
    List,
    Search,
    Exit
};

/**
 * @brief The Transaction class represents a transaction object.
 * 
 * This class contains information about the transaction code, the user who initiated the transaction,
 * and a formatted string for output to a file. It also provides functions for different types of transactions,
 * such as login, logout, create user, delete user, sell, buy, refund, add credit, and list.
 * 
 * The class includes methods for parsing a string for a valid transaction code, executing the transaction,
 * getting the formatted transaction string, and checking if a string is a valid transaction code.
 */
class Transaction {
private:
    TransactionCode transactionCode;    // The code of this transaction object i.e. login, list, etc
    Session& currentSession;            // The session that initiated the transaction           
    std::string transactionString;      // A formatted string for output to a file
    bool successStatus;                 // whether transaction was successful or not

    // Transaction Functions
    static std::string login(Transaction &t);
    static std::string logout(Transaction &t);
    static std::string create_user(Transaction &t);
    static std::string delete_user(Transaction &t);
    static std::string sell(Transaction &t);
    static std::string buy(Transaction &t);
    static std::string refund(Transaction &t);
    static std::string add_credit(Transaction &t);
    static std::string list(Transaction &t);
    static std::string exit(Transaction &t);
    static std::string search(Transaction &t);

    // Transaction String Generation Functions

    /**
     * @brief Formats transaction strings for transactions with the current user's username and credit.
     * 
     * @param code 2 digit Transaction code number (if 01 then 1, if 02 then 2, etc.)
     * @param user User who started transaction
     * @return std::string Formatted Transaction string -> XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
     */
    static std::string formatTransactionString(int code, const User &user);

    /**
     * @brief Formats transaction strings for transactions with the buyer, seller and credit amount. e.g. refund transaction.
     * 
     * @param code 2 digit Transaction code number (if 01 then 1, if 02 then 2, etc.)
     * @param buyerName The username of the buyer
     * @param sellerName The username of the seller
     * @param credit The amount of credit involved in the transaction
     * @return std::string Formatted Transaction string -> XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
     */
    static std::string formatTransactionString(int code, const std::string &buyerName, const std::string &sellerName, float credit);

    /**
     * @brief Formats transaction strings for transactions with a seller, buyer, game and price e.g. buy transaction.
     * 
     * @param code 2 digit Transaction code number (if 01 then 1, if 02 then 2, etc.)
     * @param gameName The game in question
     * @param sellerName The seller of the game
     * @param buyerName The buyer of the game
     * @param price The price of the game
     * @return std::string Formatted Transaction string -> XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_PPPPPP
     */
    static std::string formatTransactionString(int code, const std::string &gameName, const std::string &sellerName, const std::string &buyerName, float price);

    /**
     * @brief Formats transaction strings for the sell transaction
     * 
     * @param code 2 digit Transaction code number (if 01 then 1, if 02 then 2, etc.)
     * @param gameName The game to be sold
     * @param sellerName The seller of the game
     * @param price The price of the game
     * @return std::string Formatted Transaction string -> XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
     */
    static std::string formatSellTransactionString(int code, const std::string &gameName, const std::string &sellerName, float price);

    /**
     * @brief Parses a string for a valid transaction code
     * 
     * @param codeStr The string to parse
     * @return TransactionCode The transaction code matching the string, or the invalid transaction code
     */
    static TransactionCode parse_transaction_code(const std::string& codeStr);

    // A map containing a string that matches each transaction code
    static const std::unordered_map<std::string, TransactionCode> transactionCodeMap;

    // A map containing the method to execute for each transaction code
    static const std::unordered_map<TransactionCode, std::function<std::string(Transaction&)>> transactionFunctions;
public:
    /**
     * @brief Construct a new Transaction object
     * 
     * @param codeStr the string representing the transaction code
     * @param user the user initiating the transaction
     */
    Transaction(const std::string& codeStr, Session& session);

    /**
     * @brief Construct a new Transaction object
     * 
     * @param code the transaction code to execute
     * @param user the user initiating the transaction
     */
    Transaction(TransactionCode& code, Session& session);

    /**
     * @brief Executes the transaction according to the code of this transaction object.
     * 
     */
    void execute();

    /**
     * @brief Get the formatted transaction string for the daily transaction file
     * 
     * @return std::string 
     */
    std::string get_transaction_string() const;

    /**
     * @brief Get the transaction code
     * 
     * @return TransactionCode 
     */
    TransactionCode get_transaction_code() const;

    /**
     * @brief Check if a string is a valid transaction code.
     * 
     * @param codeStr The string to check.
     * @return true when the string is a valid transaction code,
     * @return false otherwise
     */
    static bool is_valid_code(const std::string& codeStr);

    /**
     * @brief Check if transaction execution was successful.
     * 
     * @return true If transaction went through with no issue.
     * @return false If something went wrong during the transaction.
     */
    bool success() const;
};

#endif // TRANSACTION_H