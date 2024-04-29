#ifndef Profiles_h
#define Profiles_h

#include "Login.h"
#include "main.h"
#include <iostream>

class Profiles {
private:
    Login& login;

public:
    Profiles(Login& loginRef) : login(loginRef) {}
    void listProfiles();

};

#endif // Profiles_h
