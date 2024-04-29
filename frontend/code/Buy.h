#ifndef Buy_h
#define Buy_h

#include <string>
#include "Login.h"
#include "main.h"
#include "inputProcessor.h"
#include <vector>

using namespace std;


class Buy {
    private:
        Login& login;
    
    public:
        // Constructor for the Buy class
        Buy(Login& login): login(login) {}

        bool alreadyOwns(const string& game); // Function to check if user already owns the game
        void buyGame(); // Function to buy a game
        void writeToDaily(const string& game, const string& seller, double price, const string& buyer); // Function to write to daily transaction file

};
#endif // Buy_h