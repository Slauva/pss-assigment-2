#include <iostream>
#include <string>

// #include "../include/Asset.h"
#include "../include/control/Environment.h"

int main() {
    // User user;
    // std::cin >> user.name;
    // std::cin >> user.surname;
    // std::cin >> user.sex;
    // std::cin >> user.type;
    // std::cin >> user.age;
    // std::cin >> user.appartment;
    // std::string email;
    // std::cin >> email;
    // std::string pass;
    // std::cin >> pass;

    // Asset prof(user, Info::Professors, Info::RED, email, pass);
    // prof.save();
    // Environment env();
    std::cout << Environment::debug("Test") << std::endl;
    std::system("pause");
    return 0;
}