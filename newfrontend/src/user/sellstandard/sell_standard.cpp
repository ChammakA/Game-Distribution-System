#include <string>
#include "../../../include/user/sellstandard/sell_standard.h"

SellStandard::SellStandard() : User() {

}

SellStandard::SellStandard(std::string username, std::string userType, float availableCredit) : User(username, userType, availableCredit) {

}

void SellStandard::sell_game() {
    
}
