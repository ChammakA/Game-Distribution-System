#ifndef DAILY_TRANSACTION_FILE_MANAGER_H
#define DAILY_TRANSACTION_FILE_MANAGER_H

#include <string>
#include <vector>
#include "../file_manager.h"
#include "../../user/user.h"

#define DAILY_TRANSACTION_FILE_LOCATION "./storage/daily_transactions/"

/**
 * @brief Class that represents a file manager for daily transactions.
 */
class DailyTransactionFileManager : public FileManager<std::string> {
public:
    /**
     * @brief Constructor for DailyTransactionFileManager.
     * @param filename The name of the file.
     */
    DailyTransactionFileManager(const std::string& filename);

    /**
     * @brief Read method for DailyTransactionFileManager.
     * @return A vector of Data objects.
     */
    std::vector<Data<std::string>> read() override;

    /**
     * @brief Write method for DailyTransactionFileManager.
     * @param data A vector of Data objects.
     * @return True if the write operation is successful, false otherwise.
     */
    bool write(const std::vector<Data<std::string>>& data) override;

    /**
     * @brief Checks if the file is valid e.g. if it exists or matches the valid format or both
     * 
     * @return true If the file is valid
     * @return false If it is not valid
     */
    bool isValid() const override;

    /**
     * @brief Destructor for DailyTransactionFileManager.
     */
    virtual ~DailyTransactionFileManager() override;
};

#endif // DAILY_TRANSACTION_FILE_MANAGER_H
