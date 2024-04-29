/*
 * User.h
 * Daniel Hinbest
 * Created on: Feb 11, 2024
 * A class for the user object
*/
#ifndef USER_H
#define USER_H
#include <string>

#define USERNAME_FIELD_LENGTH 15
#define CREDIT_FIELD_LENGTH 9
#define MAX_CREDIT_LIMIT 999999.99
/**
 * @class User
 * @brief Represents a user in the system.
 */
class User {
    private:
        std::string username; /**< The username of the user. */
        std::string user_type; /**< The type of the user. */
        float available_credit; /**< The available credit of the user. */
    public:
        /**
         * @brief Default constructor for User.
         */
        User();

        /**
         * @brief Constructor for User.
         * @param username The username of the user.
         * @param user_type The type of the user.
         * @param available_credit The available credit of the user.
         */
        User(std::string username, std::string user_type, float available_credit);

        /**
         * @brief Sets the username of the user.
         * @param username The username to set.
         */
        void set_username(std::string username);

        /**
         * @brief Sets the user type of the user.
         * @param user_type The user type to set.
         */
        void set_user_type(std::string user_type);

        /**
         * @brief Adds credits to the user's available credit.
         * @param added_credits The credits to add.
         */
        void add_credit(float added_credits);

        /**
         * @brief Removes credits from the user's available credit.
         * @param removed_credits The credits to remove.
         */
        void remove_credit(float removed_credits);

        /**
         * @brief Gets the username of the user.
         * @return The username of the user.
         */
        std::string get_username() const;

        /**
         * @brief Gets the user type of the user.
         * @return The user type of the user.
         */
        std::string get_user_type() const;

        /**
         * @brief Gets the available credit of the user.
         * @return The available credit of the user.
         */
        float get_credit() const;
};

#endif // USER_H

