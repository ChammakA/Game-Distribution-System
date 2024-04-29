#ifndef AddCredit_h
#define AddCredit_h

#include "Login.h"
#include "inputProcessor.h"
#include "main.h"
#include <iostream>

class AddCredit {
private:
    Login& login;

public:
    AddCredit(Login& loginRef) : login(loginRef) {}

    void addCreditCommand();
    void writeToDaily(const string& username, const string& type, double price);
};

#endif // AddCredit_h
