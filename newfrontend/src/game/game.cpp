#include <string>
#include <list>
#include "../../include/game/game.h"

Game::Game() {
    this->name = "";
    this->seller = "";
    this->price = 0.0;
}

/**
 * @brief Constructs a new Game object.
 * 
 * @param name The name of the game.
 * @param seller The name of the seller.
 * @param price The price of the game.
 */
Game::Game(std::string name, std::string seller, float price) {
    this->name = name;
    this->seller = seller;
    this->price = price;
}

void Game::set_name(std::string name) {
    this->name = name;
}

void Game::set_seller(std::string seller) {
    this->seller = seller;
}

void Game::set_price(float price) {
    this->price = price;
}

std::string Game::get_name() {
    return this->name;
}

std::string Game::get_seller() {
    return this->seller;
}

float Game::get_price() {
    return this->price;
}
