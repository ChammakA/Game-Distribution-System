#ifndef Create_h
#define Create_h

#include "inputProcessor.h"
#include "main.h"
using namespace std;

class Create {
    public:
        void writeToDaily(const string& user, const string& type);
        bool isValidType(const string& type);
        void createUser();
};

#endif // Create_h