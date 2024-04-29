#include "../../include/collection/collection.h"

/**
 * @brief Default constructor for the Collection class.
 */
Collection::Collection() {}

/**
 * @brief Constructor for the Collection class with parameters.
 * @param gameName The name of the game.
 * @param owner The owner of the game.
 */
Collection::Collection(std::string gameName, std::string owner)
    : gameName(gameName), owner(owner) {}

/**
 * @brief Getter method for retrieving the game name.
 * @return The game name.
 */
std::string Collection::get_game_name() const {
    return gameName;
}

/**
 * @brief Getter method for retrieving the owner.
 * @return The owner.
 */
std::string Collection::get_owner() const {
    return owner;
}

/**
 * @brief Setter method for setting the game name.
 * @param gameName The new game name.
 */
void Collection::set_game_name(const std::string& gameName) {
    this->gameName = gameName;
}

/**
 * @brief Setter method for setting the owner.
 * @param owner The new owner.
 */
void Collection::set_owner(const std::string& owner) {
    this->owner = owner;
}