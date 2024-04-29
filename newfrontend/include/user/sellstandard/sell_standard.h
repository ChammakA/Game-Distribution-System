#include <string>
#include "../user.h"

/**
 * SellStandard class is a child of User class.
 * It represents a user with standard selling privileges.
 */
class SellStandard : public User {
    public:
        /**
         * Default constructor.
         */
        SellStandard();

        /**
         * Constructor.
         * @param username The username of the user.
         * @param userType The type of the user.
         * @param availableCredit The available credit of the user.
         */
        SellStandard(std::string username, std::string userType, float availableCredit);

        /**
         * Method to sell a game.
         */
        void sell_game();
};