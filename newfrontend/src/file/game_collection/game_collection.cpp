#include "../../../include/file/game_collection/game_collection.h"
#include "../../../include/game/game.h"
#include "../../../include/user/user.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

/**
 * @brief Constructor for GameCollectionFileManager class.
 * 
 * @param filename The name of the file to read from.
 */
GameCollectionFileManager::GameCollectionFileManager(const std::string& filename) {
    this->filename = filename;
    this->valid = true;
}

/**
 * @brief Read data from the file.
 * 
 * @return A vector of Data<Collection> objects containing the game collection data.
 */
std::vector<Data<Collection>> GameCollectionFileManager::read() {
    std::vector<Data<Collection>> gameCollection;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open game collection file " << filename << std::endl;
        valid = false;
        return gameCollection;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "END") {
            break;
        }

        if (line.length() != LINE_LENGTH) {
            // Print the line length
            std::cout << "Line length: " << line.length() << std::endl;
            std::cerr << "Error: Invalid line length in game collection file " << filename << std::endl;
            valid = false;
            continue;
        }

        try {
            std::string game_name = line.substr(0, GAME_NAME_FIELD_LENGTH);
            game_name.erase(std::remove(game_name.begin(), game_name.end(), '_'), game_name.end());

            std::string owner_username = line.substr(GAME_NAME_FIELD_LENGTH, USERNAME_FIELD_LENGTH);
            owner_username.erase(std::remove(owner_username.begin(), owner_username.end(), '_'), owner_username.end());


            // Print game name and owner name to console.
            // std::cout << "Game name: " << game_name << std::endl;
            // std::cout << "Owner username: " << owner_username << std::endl;

            // Ensure that a constructor exists in the Game class that takes two std::string arguments
            Collection collection(game_name, owner_username);
            gameCollection.push_back(collection);
        } catch (std::exception &e) {
            std::cerr << "Error: Unexpected error while reading Game Collection file! It might be corrupted!" << std::endl;
            valid = false;
        }
    }

    return gameCollection;
}

/**
 * @brief Restricted write function.
 * 
 * @param data The data to write to the file.
 * @return False, as writing to the game collection file is not allowed.
 */
bool GameCollectionFileManager::write(const std::vector<Data<Collection>>& data) {
    // Since writing to the game collection file is restricted, return false
    std::cerr << "Error: Writing to the game collection file is not allowed." << std::endl;
    return false;
}

bool GameCollectionFileManager::isValid() const {
    return valid;
}

/**
 * @brief Destructor for the AvailableGamesFileManager class.
 */
GameCollectionFileManager::~GameCollectionFileManager() {}
