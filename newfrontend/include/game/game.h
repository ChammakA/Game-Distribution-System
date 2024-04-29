#ifndef GAME_H
#define GAME_H
#include <string>
#include <list>
#define GAME_NAME_FIELD_LENGTH 25
#define GAME_PRICE_FIELD_LENGTH 6
#define MAX_GAME_PRICE 999.99
/**
 * @brief Class that represents a game.
 */
class Game {
    private:
        std::string name;                                       /* Name of the game */
        std::string seller;                                     /* Seller of the game */
        float price;                                            /* Price of the game */

    public:
        /**
         * @brief Default constructor.
         */
        Game();

        /**
         * @brief Constructor.
         * @param name The name of the game.
         * @param seller The seller of the game.
         * @param price The price of the game.
         */
        Game(std::string name, std::string seller, float price);

        /**
         * @brief Set the name of the game.
         * @param name The name of the game.
         */
        void set_name(std::string name);

        /**
         * @brief Set the seller of the game.
         * @param seller The seller of the game.
         */
        void set_seller(std::string seller);

        /**
         * @brief Set the price of the game.
         * @param price The price of the game.
         */
        void set_price(float price);

        /**
         * @brief Get the name of the game.
         * @return The name of the game.
         */
        std::string get_name();

        /**
         * @brief Get the seller of the game.
         * @return The seller of the game.
         */
        std::string get_seller();

        /**
         * @brief Get the price of the game.
         * @return The price of the game.
         */
        float get_price();
};

#endif // GAME_H