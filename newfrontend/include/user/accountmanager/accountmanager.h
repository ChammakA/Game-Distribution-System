#include <string>
#include "../user.h"

/**
 * @brief The AccountManager class, which is a child of the User class.
 * 
 * This class represents an AccountManager user in the system.
 */
class AccountManager : public User {
    public:
        /**
         * @brief Default constructor for the AccountManager class.
         */
        AccountManager();

        /**
         * @brief Constructor for the AccountManager class.
         * 
         * @param username The username of the AccountManager.
         * @param userType The type of the AccountManager user.
         * @param availableCredit The available credit of the AccountManager.
         */
        AccountManager(std::string username, std::string userType, float availableCredit);

        /**
         * @brief Method to create a user.
         */
        void create_user();

        /**
         * @brief Method to delete a user.
         */
        void delete_user();

        /**
         * @brief Method to refund credits.
         */
        void refund_credits();
};