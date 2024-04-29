#ifndef Delete_h
#define Delete_h

#include "inputProcessor.h"
#include "main.h"
#include "login.h"
using namespace std;


class Delete {
    private:
        Login& login;
    public:
        Delete(Login& loginRef) : login(loginRef) {}

        void deleteUser();
        void writeToDaily(const string& user, const string& type, double price);
};
#endif // Delete_h