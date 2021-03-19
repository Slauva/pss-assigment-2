#include <iostream>

#include "../include/control/Calendar.h"
#include "../include/control/Environment.h"

void functional_list(Environment& os) {
    if (os.system_user->level >= -1) {  // No level Access & Green level Access
        std::cout << os.info("0) Open audience") << std::endl;
    }
    if (os.system_user->level >= 0)
        std::cout << os.info("1) Reserve an audience") << std::endl;
    if (os.system_user->level >= 2) {  // Yellow level Access
        std::cout << os.info("2) Create exam") << std::endl;
        std::cout << os.info("3) Create new lessen") << std::endl;
        std::cout << os.info("4) Good bey student (DROP)") << std::endl;
        std::cout << os.info("5) Move out student") << std::endl;
    }
    if (os.system_user->level == 3) {  // Red level Access
        std::cout << os.info("6) Print all users") << std::endl;
        std::cout << os.info("7) Create user") << std::endl;
        std::cout << os.info("8) Red Button (Don't worry, Be happy?)") << std::endl;
        std::cout << os.info("9) SkyNet (Joker trap)") << std::endl;
    }
    std::cout << os.info("-1) Exit") << std::endl;
}

void reserve(Environment& os, Calendar& table) {
}

void terminal(Environment& os) {
    Calendar table("ios");
    int command;
    while (true) {
        std::system("cls");
        std::cout << os.info("Welcome to terminal.\n") << std::endl;
        functional_list(os);
        std::cout << os.info("What do you want: ");
        std::cin >> command;
        std::system("cls");

        switch (command) {
            case -1:
                return;
            case 0:
                os.open();
                break;
            case 1:
                os.print_rooms();
                reserve(os, table);
                break;

            default:
                break;
        }
    }
}

int main() {
    Environment env("win10");

    std::cout << env.info("Start of system") << std::endl;
    while (true) {
        std::system("cls");
        std::cout << env.info("Let's try to enter") << std::endl;
        std::cout << env.info("Do you want to enter like guest? Guest y/n: ");
        char cmd;
        std::cin >> cmd;
        env.auth(cmd == 'y' ? 1 : 0);
        terminal(env);
    }
    std::system("pause");
    return 0;
}