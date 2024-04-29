#include "../../../include/file/file_manager.h"
#include "../../../include/game/game.h"
#include "../../../include/user/user.h"
#include "../../../include/file/available_games/available_games.h"
#include <fstream>
#include <iostream>
#include <vector>

/**
 * @brief Implementation of the AvailableGamesFileManager class.
 */
AvailableGamesFileManager::AvailableGamesFileManager(const std::string& filename) {
    this->filename = filename;
    this->valid = true;
}

/**
 * @brief Reads the available games from the file.
 * @return A vector of Data<Game> objects representing the available games.
 */
std::vector<Data<Game>> AvailableGamesFileManager::read() {

    std::vector<Data<Game>> games;

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open available games file " << filename << std::endl;
        valid = false;
        return games; // Return empty vector
    }

    // Iterate through each line in the file and extract game data.
    std::string line;

    while (std::getline(file, line)) {  // TODO: extra while loop or what? Investigate?
        if (line == "END") {
            break;
        }
        try {
            std::string name = line.substr(0, GAME_NAME_FIELD_LENGTH);
            std::string seller = line.substr(GAME_NAME_FIELD_LENGTH+1, USERNAME_FIELD_LENGTH+1);
            std::string price_str = line.substr(42, 6);

            // Remove trailing underscores from name
            size_t lastNonUnderscore = name.find_last_not_of('_');
            if (lastNonUnderscore != std::string::npos) {
                name = name.substr(0, lastNonUnderscore + 1);
            }

            // Remove trailing underscores from seller
            lastNonUnderscore = seller.find_last_not_of('_');
            if (lastNonUnderscore != std::string::npos) {
                seller = seller.substr(0, lastNonUnderscore + 1);
            }
            float price = std::stof(price_str);
            Game game(name, seller, price);
            games.emplace_back(game);
        } catch (std::exception &e) {
            std::cerr << "Error: Unexpeceted error occurred while reading available games file! It might be corrupted!" << std::endl;
            valid = false;
        }
    }
    return games;
}

/**
 * @brief Writes the available games to the file.
 * @param data A vector of Data<Game> objects representing the available games.
 * @return False, as write operation is not supported.
 */
bool AvailableGamesFileManager::write(const std::vector<Data<Game>>& data) {
    // Return false as write operation is not supported
    return false;
}

bool AvailableGamesFileManager::isValid() const {
    return valid;
}

/**
 * @brief Destructor for the AvailableGamesFileManager class.
 */
AvailableGamesFileManager::~AvailableGamesFileManager() {}