#ifndef GAME_COLLECTION_FILE_MANAGER_H
#define GAME_COLLECTION_FILE_MANAGER_H

#include <string>
#include <vector>
#include "../file_manager.h"
#include "../../collection/collection.h"

#define GAME_COLLECTION_FILE_PATH "./storage/game_collection.txt"

const int LINE_LENGTH = 42;

/**
 * @brief Class for managing game collection file.
 */
class GameCollectionFileManager : public FileManager<Collection> {
public:
    /**
     * @brief Constructor for GameCollectionFileManager.
     * @param filename The name of the file to manage.
     */
    GameCollectionFileManager(const std::string& filename);
    
    /**
     * @brief Read data from the file.
     * @return A vector of Data<Collection> objects read from the file.
     */
    std::vector<Data<Collection>> read() override;
    
    /**
     * @brief Write data to the file.
     * @param data The vector of Data<Collection> objects to write.
     * @return True if the write operation is successful, false otherwise.
     */
    bool write(const std::vector<Data<Collection>>& data) override;

    /**
     * @brief Checks if the file is valid e.g. if it exists or matches the valid format or both
     * 
     * @return true If the file is valid
     * @return false If it is not valid
     */
    bool isValid() const override;

    /**
     * @brief Destructs the GameCollectionFileManager object.
     * 
     * This destructor cleans up any resources used by the GameCollectionFileManager object.
     */
    virtual ~GameCollectionFileManager() override;
};


#endif // GAME_COLLECTION_FILE_MANAGER_H