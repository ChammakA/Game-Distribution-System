#include <string>
#include "../user.h"

/**
 * @brief The FullStandard class represents a full standard user.
 * 
 * This class inherits from the User class and provides additional functionality
 * specific to full standard users.
 */
class FullStandard : public User {
    public:
        /**
         * @brief Default constructor for FullStandard.
         */
        FullStandard();

        /**
         * @brief Constructor for FullStandard.
         * 
         * @param username The username of the user.
         * @param userType The type of the user.
         * @param availableCredit The available credit of the user.
         */
        FullStandard(std::string username, std::string userType, float availableCredit);

        /**
         * @brief Method to buy a game.
         */
        void buy_game();

        /**
         * @brief Method to sell a game.
         */
        void sell_game();
};
