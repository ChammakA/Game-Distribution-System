#include <string>
#include "../../../include/user/accountmanager/accountmanager.h"
// #include "../include/user/User.h"

AccountManager::AccountManager() : User() {

}

AccountManager::AccountManager(std::string username, std::string userType, float availableCredits) : User (username, userType, availableCredits) {

}

void AccountManager::create_user() {

}

void AccountManager::delete_user() {

}

void AccountManager::refund_credits() {

}
