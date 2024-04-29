#include "List.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


// Function to display the list of available games
void List::displayList(){

    inputProcessor ip;
    vector<gamesAvailableInfo> gameList = ip.readAvailableGames(); // Read the user accounts file
    cout << "GameFlow Catalogue: " << endl; // Title of the list
    cout << "-------------------" << endl << "-------------------" << endl;
    for (auto game : gameList) {
        cout << "Title: " << game.gameName << endl << "Price: " << game.price << endl << "Seller: " << game.seller << endl; // Display the game, seller, and price
        cout << "-------------------" << endl;
    }
}
