#ifndef inputProcessor_h
#define inputProcessor_h
using namespace std;

#include "Login.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>


struct userAccountsInfo{
    string username;
    string userType;
    double credits;
};

struct gameCollectionInfo{
    string gameName;
    string owner;
};

struct gamesAvailableInfo{
    string gameName;
    string seller;
    double price;
};

// inputProcessor class (meant for processing input)
class inputProcessor{ 

    private: // private variables
        static set<string> deletedUsers;
        vector<string> adminCommands;   
        vector<string> fullCommands;
        vector<string> buyCommands;
        vector<string> sellCommands;
    
    public:
        inputProcessor() { // constructor for the commands
            adminCommands = {"Logout", "Create", "Delete", "Buy", "Sell", "AddCredit", "Refund", "List", "Profiles"};
            buyCommands = {"Logout", "Buy", "AddCredit","List"};
            sellCommands = {"Logout", "Sell", "AddCredit", "List"};
            fullCommands = {"Logout", "Buy", "Sell", "AddCredit", "List"};
}
        string getCommands(const string& userLevel){ // function to get output based on user level
            return (userLevel == "Admin") ? "Logout, Create, Delete, Buy, Sell, AddCredit, Refund, List, Profiles" :
                   (userLevel == "Buy Standard") ? "Logout, Buy, AddCredit, List" :
                   (userLevel == "Sell Standard") ? "Logout, Sell, AddCredit, List" :
                   "Logout, Buy, Sell, AddCredit, List";
        };
  
        vector<userAccountsInfo> readUserAccounts(); // function to read and store user accounts
        vector<gameCollectionInfo> readGameCollection(); // function to read and store game collection
        vector<gamesAvailableInfo> readAvailableGames(); // function to read and store available games

        static void addDeletedUser(const string& user){
            deletedUsers.insert(user);
        } // function to add deleted user to the vector

        static bool isDeletedUser(const string& user){ // function to check if user is deleted
            return deletedUsers.find(user) != deletedUsers.end();
        }


        bool isCommand(const string& input);
        bool ignoreCase(string s1, string s2); // function to ignore case when comparing strings
        bool nonASCII(const string& input); // function to check if input contains non-ASCII characters
        bool isValidInput(const string& input, const string& userLevel);  // function to check if input is valid command based on user type
        string typeUser(const string& abbreviation); // function to convert user type from 2 letter code to string value

       
};

#endif // inputProcessor_h