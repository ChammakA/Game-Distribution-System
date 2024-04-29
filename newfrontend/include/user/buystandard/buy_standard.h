#include <string>
#include "../user.h"

/**
 * @brief The BuyStandard class, which is a child of the User class.
 * 
 * This class represents a standard user who can buy games.
 */
class BuyStandard : public User {
    public:
        /**
         * @brief Default constructor for the BuyStandard class.
         */
        BuyStandard();

        /**
         * @brief Constructor for the BuyStandard class.
         * 
         * @param username The username of the user.
         * @param userType The type of the user.
         * @param availableCredit The available credit of the user.
         */
        BuyStandard(std::string username, std::string userType, float availableCredit);

        /**
         * @brief Method to buy a game.
         */
        void buy_game();
};