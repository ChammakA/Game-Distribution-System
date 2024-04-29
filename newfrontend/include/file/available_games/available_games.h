#ifndef AVAILABLE_GAMES_FILE_MANAGER_H
#define AVAILABLE_GAMES_FILE_MANAGER_H

#include <string>
#include <vector>
#include "../file_manager.h"
#include "../../game/game.h"

#define AVAILABLE_GAMES_FILE_PATH "./storage/available_games.txt"

/**
 * @brief Class that represents a file manager for available games.
 * 
 * This class inherits from the FileManager class and provides methods for reading and writing available games data.
 */
class AvailableGamesFileManager : public FileManager<Game> {
public:
    /**
     * @brief Constructor for AvailableGamesFileManager.
     * 
     * @param filename The name of the file.
     */
    AvailableGamesFileManager(const std::string& filename);

    /**
     * @brief Read method for reading available games data.
     * 
     * @return A vector of Data objects representing the available games.
     */
    std::vector<Data<Game>> read() override;

    /**
     * @brief Write method for writing available games data.
     * 
     * @param data A vector of Data objects representing the available games.
     * @return True if the write operation is successful, false otherwise.
     */
    bool write(const std::vector<Data<Game>>& data) override;

    /**
     * @brief Checks if the file is valid e.g. if it exists or matches the valid format or both
     * 
     * @return true If the file is valid
     * @return false If it is not valid
     */
    bool isValid() const override;

    /**
     * @brief Destructor for AvailableGamesFileManager.
     */
    virtual ~AvailableGamesFileManager() override;
};

#endif // AVAILABLE_GAMES_FILE_MANAGER_H
