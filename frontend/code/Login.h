#ifndef Login_h
#define Login_h

using namespace std;

#include <string>
#include "inputProcessor.h"
#include "main.h"

//Login class, meant to handle user login and logout
class Login{

    private: // private variables
        bool LoggedIn;
        string currentUser;
        string level;
        double credit;

    public:
        Login() : LoggedIn(false) {} // constructor for the login

        bool isLoggedIn () const{ // getter function to check if user is logged in
            return LoggedIn;
        }

        string getCurrentUser() const{ // getter function to get the current user
            return currentUser;
        }

        double getUserCredit() const{ // getter function to get the user's credit
            return credit;
        }
        
        void setUserCredit(double credit){ // setter function to set the user's credit
            this->credit = credit;
        }

        string getUserLevel() const { // getter function to get the user's level
            return level;
        }

        bool isLogin(const string& input); // Function to check if input is login command
        bool loginUser(const string& username); // Function to check if user exists and log them in if they do

        void logoutUser(); // Function to log the user out


};
#endif // Login_h