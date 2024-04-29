#include <iostream>
#include "Login.h"
#include "inputProcessor.h"
#include "List.h"
#include "Buy.h"
#include "Refund.h"
#include "AddCredit.h"
#include "Profiles.h"
#include "Create.h"
#include "Delete.h"
#include "Sell.h"
#include <string>

using namespace std;

string userAccountsFilePath;
string gameCollectionFilePath;
string availableGamesFilePath;
string dailyTransactionFilePath;

int main(int argc, char* argv[]){
    if (argc != 5) {
        cout << "Invalid number of arguments" << endl;
        return 1;
    }
    userAccountsFilePath = "../Test Files/AvailableAccounts/" + string(argv[1]);
    availableGamesFilePath = "../Test Files/AvailableGames/" + string(argv[2]);
    gameCollectionFilePath = "../Test Files/GameCollection/" + string(argv[3]);
    dailyTransactionFilePath = "../Test Files/DailyTransaction/" + string(argv[4]);

    Login login;
    List list;
    inputProcessor ip;
    
    Buy buy(login);
    Refund refund(login);
    AddCredit addCredit(login);
    Profiles profiles(login);
    Create create;
    Delete deleting(login);
    Sell sell(login);
    string input;

    cout << "Welcome to GameFlow!" << endl; // Welcome message

    do { //Login loop, meant to ensure that the user logs in before proceeding
        cout << "Please enter Login Command:" << endl;
        getline(cin, input);
        if (ip.ignoreCase(input, "exit")){
            exit(0);
        }
    }  while (!login.isLogin(input));

    while (!login.isLoggedIn()){ // Username loop, ensure user enters a valid username before proceeding
        cout << "Please enter a valid username:" << endl;
        getline(cin, input);
        if (ip.ignoreCase(input, "exit")){
            exit(0);
        }
        login.loginUser(input);
        
    }
    
    cout << "Welcome, " << login.getUserLevel() << " User: " << login.getCurrentUser() << endl; // Once logged in, appropriate welcome message is displayed
    cout << "Your current credit balance is: " << login.getUserCredit() << endl;
    while (login.isLoggedIn()) { // Command loop, will continue to prompt user for commands until they logout
        
        do {    
            cout << "Please enter a valid command. (Options: " << ip.getCommands(login.getUserLevel()) << ")"<< endl;
            getline(cin, input);
            
        } while (!ip.isValidInput(input, login.getUserLevel()));
        
        if (ip.ignoreCase(input, "logout")){
            login.logoutUser();
        }
        else if (ip.ignoreCase(input, "list")){
            list.displayList();
        }
        else if (ip.ignoreCase(input, "create")){
            create.createUser();
        }
        else if (ip.ignoreCase(input, "delete")){
            deleting.deleteUser();
        }
        else if (ip.ignoreCase(input, "buy")){
            buy.buyGame();
        }
        else if(ip.ignoreCase(input, "sell")){
            sell.sellGame();
        }
        else if (ip.ignoreCase(input, "refund")){
            refund.refundTransaction();
        }
        else if (ip.ignoreCase(input, "AddCredit")){
            addCredit.addCreditCommand();
        }
        else if (ip.ignoreCase(input, "Profiles")) {
            cout << "List of Current Users: " << endl << "-------------------" << endl;
            profiles.listProfiles();
        }

    }
    return 0;
}