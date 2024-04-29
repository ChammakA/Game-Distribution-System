/**
 * @file file_manager.h
 * @brief This file contains the definition of the FileManager class and the Data class template.
 * 
 * The FileManager class is an abstract base class for file management. It provides pure virtual functions for reading from and writing to a file.
 * The Data class template is a generic class for representing user accounts or available games.
 */
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <string>

/**
 * @brief A generic class for representing data types in the file.
 * 
 * The Data class template is a generic class for representing data types in the file. It is used to store data read from a file or to write data to a file.
 * 
*/
template<typename T>
/**
 * @brief The Data class represents a container for storing data of type T.
 */
class Data {
public:
    /**
     * @brief Default constructor for the Data class.
     */
    Data() {}

    /**
     * @brief Constructor for the Data class that initializes the data with the given value.
     * @param data The value to initialize the data with.
     */
    Data(const T& data) : data(data) {}

    /**
     * @brief Retrieves the stored data.
     * @return The stored data of type T.
     */
    T get_data() const { return data; }

private:
    T data; // Data of type T
};

// Abstract base class for file management
template<typename T>
class FileManager {
protected:
    std::string filename;
    bool valid;
public:
    virtual ~FileManager() {} // Make the base class destructor virtual

    /**
     * @brief Reads data from a file.
     * @return A vector of Data objects containing the read data.
     */
    virtual std::vector<Data<T>> read() = 0;

    /**
     * @brief Writes data to a file.
     * @param data The vector of Data objects to be written.
     * @return True if the write operation is successful, false otherwise.
     */
    virtual bool write(const std::vector<Data<T>>& data) = 0;
    
    /**
     * @brief Checks if the file is valid e.g. if it exists or matches the valid format or both
     * 
     * @return true If the file is valid
     * @return false If it is not valid
     */
    virtual bool isValid() const = 0;
};

#endif // FILE_MANAGER_H