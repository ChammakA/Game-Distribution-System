#include <fstream>
#include <iostream>
#include "../../../include/file/daily_transaction/daily_transaction.h"

/**
 * @brief DailyTransactionFileManager constructor.
 * 
 * @param filename The name of the daily transaction file.
 */
DailyTransactionFileManager::DailyTransactionFileManager(const std::string& filename) {
    this->filename = filename;
    this->valid = true;
}

/**
 * @brief Read function for the daily transaction file.
 * 
 * @return An empty vector since reading from the daily transaction file is not allowed.
 */
std::vector<Data<std::string>> DailyTransactionFileManager::read() {
    std::vector<Data<std::string>> strings;

    std::ifstream file(filename);
    if (!file.is_open()) {
        valid = true;
        return strings;
    }

    // Iterate through each line in the file and extract dtf data.
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            std::cerr << "Error: Expected an empty daily transaction file." << std::endl;
            valid = false;
        }
        strings.emplace_back(line);
    }
    return strings;
}

/**
 * @brief Write function for the daily transaction file.
 * 
 * @param data The vector of data to be written to the file.
 * @return True if the write operation is successful, false otherwise.
 */
bool DailyTransactionFileManager::write(const std::vector<Data<std::string>>& data) {
    std::ofstream file(filename, std::ios::app); // Open file in append mode
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open daily transaction file " << filename << " for writing." << std::endl;
        return false; // Return false if unable to open file
    }

    for (const auto& transaction : data) {
        file << transaction.get_data() << std::endl; // Write each transaction to file
    }
    return true;
}

/**
 * @brief Checks if the file is valid e.g. if it exists or matches the valid format or both
 * 
 * @return true 
 * @return false 
 */
bool DailyTransactionFileManager::isValid() const {
    return valid;
}

/**
 * @brief DailyTransactionFileManager destructor.
 */
DailyTransactionFileManager::~DailyTransactionFileManager() {}
