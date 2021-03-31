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

void reserve(Environment& os, Calendar& table, int mode) {
    std::string date, label, from, to;
    int room;
    std::cout << os.info("What's name of your party: ");
    std::cin >> label;
    std::cout << os.info("Date(dd/mm/yyyy): ");
    std::cin >> date;
    std::cout << os.info("From(HH:mm): ");
    std::cin >> from;
    std::cout << os.info("To(HH:mm): ");
    std::cin >> to;
    std::cout << os.info("Room: ");
    std::cin >> room;

    if (os.access_check(room, mode)) {
        bool ans = table.reservation(label, room, date, from, to);
        std::cout << os.info(ans ? "Success" : "The room is busy") << std::endl;
    } else {
        std::cout << os.error("You don't have permission or the room doesn't exist!") << std::endl;
    }
}

void terminal(Environment& os, int mode) {
    Calendar table("ios");
    int command;
    char cmd;
    std::string date;
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
                os.open(mode);
                break;
            case 1:  // Same like 3
            case 2:  // Same like 3
            case 3:
                os.print_rooms();
                reserve(os, table, mode);
                break;
            case 4:
                std::cout << os.info("Email of target: ");
                std::cin >> date;
                os.drop(date);
                std::cout << os.info("Success") << std::endl;
                break;
            case 5:
                std::cout << os.info("Email of target: ");
                std::cin >> date;
                os.move_out(date);
                std::cout << os.info("Success") << std::endl;
                break;
            case 6:
                os.print_users();
                break;
            case 7:
                os.create();
                break;
            case 8:
            case 9:
                std::cout << os.custom("WARNING", "There will be no way back, are you sure?") << std::endl;
                std::cout << os.custom("WARNING", "Start y/n: ");
                std::cin >> cmd;
                if (cmd == 'y')
                    if (command == 8)
                        os.red_button();
                    else
                        os.terminated();
                else
                    std::cout << os.custom("WARNING", "Cancel") << std::endl;
                break;
            default:
                break;
        }
        std::system("pause");
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
        std::cout << env.custom("WARNING", "A fire alarm went off at the university.") << std::endl;
        std::cout << env.custom("WARNING", "Activate an emergency? y/n: ");
        std::cin >> cmd;
        std::cout << env.custom("WARNING", cmd == 'y' ? "All rooms were opened" : "Fortunately, the guard checked and found out that they were smoking students. Training alarm.");
        std::system("pause");
        terminal(env, cmd == 'y' ? 1 : 0);
    }
    std::system("pause");
    return 0;
}