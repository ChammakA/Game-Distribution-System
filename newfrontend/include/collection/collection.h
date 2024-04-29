#include <string>
#include <list>
#include <vector>

#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include <vector>

/**
 * @brief Class that represents a collection of games.
 */
class Collection {
private:
    std::string gameName;                                   // Name of the game
    std::string owner;                                      // Owner of the collection

public:
    /**
     * @brief Default constructor.
     */
    Collection();

    /**
     * @brief Constructor.
     * @param gameName The name of the game.
     * @param owner The owner of the collection.
     */
    Collection(std::string gameName, std::string owner);

    /**
     * @brief Get the name of the game.
     * @return The name of the game.
     */
    std::string get_game_name() const;

    /**
     * @brief Get the owner of the collection.
     * @return The owner of the collection.
     */
    std::string get_owner() const;

    /**
     * @brief Set the name of the game.
     * @param gameName The name of the game.
     */
    void set_game_name(const std::string& gameName);

    /**
     * @brief Set the owner of the collection.
     * @param owner The owner of the collection.
     */
    void set_owner(const std::string& owner);
};

#endif // COLLECTION_H