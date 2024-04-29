#ifndef Refund_h
#define Refund_h

using namespace std;
#include <iostream>
#include <string>
#include "Login.h"
#include "main.h"


//Refund class 
class Refund{

    private: // private variables
        Login& login;
        string BuyerName;
        string SellerName;
        double credit;
        
    public:
        // Refund() : LoggedIn(false) {} // constructor for the login
        Refund(Login& loginRef) : login(loginRef){};
        void writeToDaily(const string& buyer, const string& seller, double credit); // write to daily transaction file
        void refundTransaction(); // refund transaction
};
#endif // Refund_h