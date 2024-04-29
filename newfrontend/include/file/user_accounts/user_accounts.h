#ifndef USER_ACCOUNTS_FILE_MANAGER_H
#define USER_ACCOUNTS_FILE_MANAGER_H

#include <string>
#include <vector>
#include "../file_manager.h" // Include base class header
#include "../../user/user.h"

#define CURRENT_USER_ACCOUNTS_PATH "./storage/current_user_accounts.txt"

/**
 * @class UserAccountsFileManager
 * @brief A class for managing user accounts file.
 * 
 * This class inherits from FileManager<User> and provides functionality to read and write user accounts data.
 * It also includes a destructor to clean up resources.
 */
class UserAccountsFileManager : public FileManager<User> {
public:
    /**
     * @brief Constructs a UserAccountsFileManager object with the specified filename.
     * 
     * @param filename The name of the user accounts file.
     */
    UserAccountsFileManager(const std::string& filename);

    /**
     * @brief Reads user accounts data from the file.
     * 
     * @return A vector of Data<User> objects containing the read user accounts data.
     */
    std::vector<Data<User>> read() override;

    /**
     * @brief Writes user accounts data to the file.
     * 
     * @param data A vector of Data<User> objects containing the user accounts data to be written.
     * @return True if the write operation is successful, false otherwise.
     */
    bool write(const std::vector<Data<User>>& data) override;

    /**
     * @brief Checks if the file is valid e.g. if it exists or matches the valid format or both
     * 
     * @return true If the file is valid
     * @return false If it is not valid
     */
    bool isValid() const override;

    /**
     * @brief Destructs the UserAccountsFileManager object.
     * 
     * This destructor cleans up any resources used by the UserAccountsFileManager object.
     */
    virtual ~UserAccountsFileManager() override;
};

#endif // USER_ACCOUNTS_FILE_MANAGER_H
