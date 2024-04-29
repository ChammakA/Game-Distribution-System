#include <string>
#include "../../../include/user/buystandard/buy_standard.h"

BuyStandard::BuyStandard() : User() {

}

BuyStandard::BuyStandard(std::string username, std::string userType, float availableCredit) : User(username, userType, availableCredit) {

}

void BuyStandard::buy_game() {
    
}