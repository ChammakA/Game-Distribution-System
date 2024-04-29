/*
 * User.h
 * Daniel Hinbest
 * Created on: Feb 11, 2024
 * A class for the user object
*/
#include <iostream>
#include <string>
#include "../../include/user/user.h"

// default constructor
User::User() {
    username = "";
    user_type = "";
    available_credit = 0;
}

// constructor with parameters
User::User(std::string username, std::string user_type, float available_credit): username(username), user_type(user_type), available_credit(available_credit) {}

void User::set_username(std::string username) {
    bool isValid = false;                                                                               // check if the username is valid
    do {
        if (username.length() >= USERNAME_FIELD_LENGTH) {  
            std::cout << "The username cannot exceed " << USERNAME_FIELD_LENGTH << " characters. Please try again." << std::endl;    // if the username is too long
            isValid = false;                                                                            // the username is not valid
            std::cout << "Please enter a username: ";                                                   // ask for a new username
            std::cin >> username;                                                                       // get the new username
        } else {
            isValid = true;                                                                             // the username is valid
        }
    } while(!isValid);
    this->username = username;                                                                          // set the username
}

// set the user type
void User::set_user_type(std::string user_type) {
    bool isValid = false;                                                                               // check if the user type is valid
    do {
        if (user_type != "AA" && user_type != "FS" && user_type != "BS" && user_type != "SS" && user_type != "AM") {
            std::cout << "The user type must be AA, FS, BS, SS, or AM. Please try again." << std::endl;     // if the user type is not valid
            isValid = false;                                                                            // the user type is not valid
            std::cout << "Please enter a user type: ";                                                  // ask for a new user type
            std::cin >> user_type;                                                                      // get the new user type
        } else {
            isValid = true;                                                                             // the user type is valid
        }
    } while(!isValid);
    this->user_type = user_type;
}

// add credit to the user
void User::add_credit(float added_credits) {
    available_credit += added_credits;                                                                  // add the credits to the available credit
}

// remove credit from the user
void User::remove_credit(float removed_credits) {
    available_credit -= removed_credits;                                                                // remove the credits from the available credit
}

// get the username
std::string User::get_username() const {
    return username;                                                                                    // return the username
}

// get the user type
std::string User::get_user_type() const {
    return user_type;                                                                                   // return the user type
}

// get the available credit
float User::get_credit() const {
    return available_credit;                                                                            // return the available credit
}