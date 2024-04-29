#include <string>
#include "../user.h"

/**
 * @brief The Admin class, which is a child of the User class.
 * 
 * This class represents an admin user in the system.
 */
class Admin : public User {
    public:
        /**
         * @brief Default constructor for the Admin class.
         */
        Admin();

        /**
         * @brief Constructor for the Admin class.
         * 
         * @param username The username of the admin.
         * @param userType The type of the admin user.
         * @param availableCredit The available credit of the admin.
         */
        Admin(std::string username, std::string userType, float availableCredit);

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

        /**
         * @brief Method to buy a game.
         */
        void buy_game();

        /**
         * @brief Method to sell a game.
         */
        void sell_game();
};