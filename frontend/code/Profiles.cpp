#include "Profiles.h"
#include "inputProcessor.h"

#include <iostream>
#include <fstream>
#include <string>

// Function to Handle Profiles Command
void Profiles::listProfiles() {
    inputProcessor ip; // Assuming login is a member of the Profiles class
    vector<userAccountsInfo> profileList = ip.readUserAccounts(); // Read the user accounts file

    for (auto user : profileList) {
        cout << "User: " << user.username << endl; // Display the user, type, and credits
        cout << "Type: " << ip.typeUser(user.userType) << endl;
        cout << "Credits: " << user.credits << endl;
        cout << endl;
    }
}
