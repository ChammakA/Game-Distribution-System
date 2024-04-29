#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../../include/file/file_manager.h"
#include "../../../include/user/user.h"
#include "../../../include/file/user_accounts/user_accounts.h"


UserAccountsFileManager::UserAccountsFileManager(const std::string& filename){
    this->filename = filename;
    this->valid = true;
}

/**
 * @brief Reads user accounts data from a file and returns a vector of user data.
 * 
 * @return std::vector<Data<User>> - A vector containing user data.
 */
std::vector<Data<User>> UserAccountsFileManager::read() {
    std::vector<Data<User>> users;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open user accounts file " << filename << std::endl;
        valid = false;
        return users; // Return empty vector
    }

    
    // Iterate through each line in the file and extract user data.
    std::string line;
    while (std::getline(file, line)) {
        if (line == "END") {
            break;
        }
        try {
            std::string name_string = line.substr(0, USERNAME_FIELD_LENGTH+1);
            size_t lastNonUnderscore = name_string.find_last_not_of('_');
            if (lastNonUnderscore != std::string::npos) {
                name_string = name_string.substr(0, lastNonUnderscore + 1);
            }
            std::string username = name_string;
            std::string user_type = line.substr(USERNAME_FIELD_LENGTH+1, 2);
            std::string credit_str = line.substr(19, 9);
            float available_credit = std::stof(credit_str);
            User user(username, user_type, available_credit);
            users.emplace_back(user);
        } catch (std::exception &e) {
            std::cerr << "Error: Unexpected error while reading User Accounts file! It might be corrupted!" << std::endl;
            valid = false;
        }
    }
    return users;
}

bool UserAccountsFileManager::write(const std::vector<Data<User>>& data) {
    // Return false as write operation is not supported
    return false;
}

/**
 * @brief Checks if the file is valid e.g. if it exists or matches the valid format or both
 * 
 * @return true 
 * @return false 
 */
bool UserAccountsFileManager::isValid() const {
    return valid;
}

UserAccountsFileManager::~UserAccountsFileManager() {}