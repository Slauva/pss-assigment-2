#include <iostream>

#include "../include/Asset.h"

int main() {
    User user;
    std::cin >> user.name;
    std::cin >> user.surname;
    std::cin >> user.sex;
    std::cin >> user.description;
    std::cin >> user.age;
    std::cin >> user.appartment;
    std::string email;
    std::cin >> email;
    std::string pass;
    std::cin >> pass;

    Asset prof(user, Professors, RED, email, pass);
    prof.save();

    std::system("pause");
    return 0;
}