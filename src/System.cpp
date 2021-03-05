#include "../include/control/System.h"

#include <iostream>
#include <string>

std::string System::info(std::string str) {
    return "[INFO]:\t " + str;
}

std::string System::error(std::string str) {
    return "[ERROR]:\t " + str;
}

std::string System::debug(std::string str) {
    return "[DEBUG]:\t " + str;
}

void System::auth() {
    std::string email;
    std::cout << info("Login/Email") << std::endl;
    std::cin >> email;
    std::string pass;
    std::cout << info("Login/Email") << std::endl;
    std::cin >> email;
}