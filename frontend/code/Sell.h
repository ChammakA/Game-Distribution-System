#ifndef Sell_h
#define Sell_h

#include <string>
#include "inputProcessor.h"
#include "main.h"

using namespace std;

class Sell {
    private:
        Login& login;

    public:
        Sell(Login& login): login(login) {}

        void sellGame();
        bool alreadyAvailable(const string& gameName);
        void writeToDaily(const string& gameName, const string& seller, double price);

};
#endif // Sell_h