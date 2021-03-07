#include "../include/control/Environment.h"

#include <stdio.h>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "../include/control/Calendar.h"
namespace fs = std::filesystem;

std::string Environment::info(std::string str) {
    return "[INFO]:\t\t " + str;
}

std::string Environment::error(std::string str) {
    return "[ERROR]:\t " + str;
}

std::string Environment::debug(std::string str) {
    return "[DEBUG]:\t " + str;
}

std::string Environment::custom(std::string type, std::string str) {
    return "[" + type + "]:\t " + str;
}

bool Environment::access_check(int room) {
    if (this->system_user->level >= 2)
        return true;
    else if (this->system_user->level == 1) {
        if (10 <= room && room <= 108)
            return true;
        return false;
    } else if (100 <= room && room <= 106)
        return true;
    else
        return false;
}

void Environment::red_button() {
    std::uintmax_t n = fs::remove_all(fs::current_path() / "..\\data\\persons");
}

void Environment::create() {
    User user;
    Info::Post post;
    Info::Access_Level level;
    std::cout << info("Name: ");
    std::cin >> user.name;
    std::cout << info("Surname: ");
    std::cin >> user.surname;
    std::cout << info("Sex(Male/Female): ");
    std::cin >> user.sex;
    std::cout << info("Type('-'/Aching/Whispering): ");
    std::cin >> user.type;
    std::cout << info("Age: ");
    std::cin >> user.age;
    std::cout << info("Appartment number: ");
    std::cin >> user.appartment;
    std::string email;
    std::cout << info("Email: ");
    std::cin >> email;
    std::string pass;
    std::cout << info("Password: ");
    std::cin >> pass;
    std::cout << info("Who(Professor/Student/Lab-Employees/Director/Admin): ");
    std::string spost;
    std::cin >> spost;
    if (spost == "Professor") {
        post = Info::Post(1);
        level = Info::Access_Level(2);
    } else if (spost == "Lab-Employees") {
        post = Info::Post(2);
        level = Info::Access_Level(1);
    } else if (spost == "Director") {
        post = Info::Post(3);
        level = Info::Access_Level(2);
    } else if (spost == "Admin") {
        post = Info::Post(4);
        level = Info::Access_Level(3);
    } else {
        post = Info::Post(0);
        level = Info::Access_Level(0);
    }
    Asset* o = new Asset(user, post, level, email, pass);
    o->save();
    std::cout << info("Success") << std::endl;
}

void Environment::drop(std::string email) {
    std::string path = "..\\data\\persons\\" + email + ".json";
    std::uintmax_t n = fs::remove(fs::current_path() / path);
}

void Environment::move_out(std::string email) {
    std::ifstream in("../data/persons/" + email + ".json");
    json j;
    in >> j;
    in.close();
    j["User"]["Appartment"] = "";

    std::ofstream out("../data/persons/" + email + ".json");
    out << j.dump(4) << std::endl;
    out.close();
}

void Environment::print_users() {
    std::vector<std::string> files;
    json j;

    for (auto& p : fs::directory_iterator(fs::current_path() / "..\\data\\persons\\"))
        files.push_back(p.path().filename().string());
    printf("%15s\t%15s\t%15s\t%15s\t%15s\t%15s\t%30s\t%30s\t\n\n", "Name", "Surname", "Sex", "Age", "Type", "Appartment", "Post", "Email");
    for (auto file : files) {
        std::ifstream in("../data/persons/" + file);
        in >> j;
        std::string post;
        if (j["Access"]["Post"] == 0)
            post = "Student";
        if (j["Access"]["Post"] == 1)
            post = "Professor";
        if (j["Access"]["Post"] == 2)
            post = "Lab Employees";
        if (j["Access"]["Post"] == 3)
            post = "Director";
        if (j["Access"]["Post"] == 4)
            post = "Admin";
        printf(
            "%15s\t%15s\t%15s\t%15d\t%15s\t%15s\t%30s\t%30s\t\n",
            j["User"]["Name"].get<std::string>().c_str(),
            j["User"]["Surname"].get<std::string>().c_str(),
            j["User"]["Sex"].get<std::string>().c_str(),
            j["User"]["Age"].get<int>(),
            j["User"]["Type"].get<std::string>().c_str(),
            j["User"]["Appartment"].get<std::string>().c_str(),
            post.c_str(),
            j["Auth"]["Email"].get<std::string>().c_str());
    }
}

void Environment::print_rooms() {
    std::cout << std::endl
              << info("====================================") << std::endl;
    std::cout << info("Class rooms: ");
    for (int i = 0; i < 4; i++)
        std::cout << class_room[i] << " ";
    std::cout << std::endl;
    std::cout << info("Labs: ");
    for (int i = 0; i < 4; i++)
        std::cout << labs[i] << " ";
    std::cout << std::endl;
    std::cout << info("Lecture rooms: ");
    for (int i = 0; i < 2; i++)
        std::cout << lecture_room[i] << " ";
    std::cout << std::endl;
    std::cout << info("Professor cabinets: ");
    for (int i = 0; i < 3; i++)
        std::cout << profesor_cabinet[i] << " ";
    std::cout << std::endl;
    std::cout << info("Director cabinets: ");
    for (int i = 0; i < 1; i++)
        std::cout << director_cabinet[i] << " ";
    std::cout << std::endl
              << info("====================================") << std::endl;
}

void Environment::open() {
    print_rooms();
    int room;
    std::cout << info("Which room you need: ");
    std::cin >> room;
    if (access_check(room)) {
        std::cout << info("You got in, sweet brat " + this->system_user->data.name) << std::endl;
    } else {
        std::cout << error("You don't have permission or the room doesn't exist!") << std::endl;
    }
}

void Environment::terminal() {
    Calendar table("ios");
    while (true) {
        std::cout << info("Welcome to terminal.") << std::endl
                  << std::endl;
        if (this->system_user->level >= 0) {  // No level Access & Green level Access
            std::cout << info("0) Open audience") << std::endl;
            std::cout << info("1) Reserve an audience") << std::endl;
        }
        if (this->system_user->level >= 2) {  // Yellow level Access
            std::cout << info("2) Create exam") << std::endl;
            std::cout << info("3) Create new lessen") << std::endl;
            std::cout << info("4) Good bey student (DROP)") << std::endl;
            std::cout << info("5) Move out student") << std::endl;
        }
        if (this->system_user->level == 3) {  // Red level Access
            std::cout << info("6) Create user") << std::endl;
            std::cout << info("7) Red Button (Don't worry, Be happy?)") << std::endl;
            std::cout << info("8) SkyNet (Joker trap)") << std::endl;
        }
        std::cout << info("-2) Print all users") << std::endl;
        std::cout << info("To exit write: '-1'") << std::endl;
        std::cout << info("What do you want: ");
        int command;
        std::cin >> command;
        if (command == -1) {
            std::cout << info("Good bey") << std::endl;
            break;
        }
        if (command == -2) {
            std::system("cls");
            print_users();
            std::system("pause");
            std::system("cls");
            continue;
        }
        std::system("cls");
        // std::system("clear");
        std::string date, label, from, to;
        char l;
        bool ans;
        int room;
        switch (command) {
            case 0:
                open();
                break;
            case 1:
                print_rooms();
                std::cout << info("What's name of your party: ");
                std::cin >> label;
                std::cout << info("Date(dd/mm/yyyy): ");
                std::cin >> date;
                std::cout << info("From(HH:mm): ");
                std::cin >> from;
                std::cout << info("To(HH:mm): ");
                std::cin >> to;
                std::cout << info("Room: ");
                std::cin >> room;
                while (!access_check(room)) {
                    std::cout << error("You don't have permission or the room doesn't exist!") << std::endl;
                    std::cout << info("Choose another room: ");
                    std::cin >> room;
                }
                ans = table.reservation(label, room, date, from, to);
                if (ans)
                    std::cout << info("Success") << std::endl;
                else
                    std::cout << info("The room is busy");
                break;
            case 2:
                print_rooms();
                std::cout << info("What's name of your exam: ");
                std::cin >> label;
                std::cout << info("Date(dd/mm/yyyy): ");
                std::cin >> date;
                std::cout << info("From(HH:mm): ");
                std::cin >> from;
                std::cout << info("To(HH:mm): ");
                std::cin >> to;
                std::cout << info("Room: ");
                std::cin >> room;
                while (!access_check(room)) {
                    std::cout << error("You don't have permission or the room doesn't exist!") << std::endl;
                    std::cout << info("Choose another room: ");
                    std::cin >> room;
                }
                table.reservation(label, room, date, from, to);
                if (ans)
                    std::cout << info("Success") << std::endl;
                else
                    std::cout << info("The room is busy");
                break;
            case 3:
                print_rooms();
                std::cout << info("What's name of your lessen: ");
                std::cin >> label;
                std::cout << info("Date(dd/mm/yyyy): ");
                std::cin >> date;
                std::cout << info("From(HH:mm): ");
                std::cin >> from;
                std::cout << info("To(HH:mm): ");
                std::cin >> to;
                std::cout << info("Room: ");
                std::cin >> room;
                while (!access_check(room)) {
                    std::cout << error("You don't have permission or the room doesn't exist!") << std::endl;
                    std::cout << info("Choose another room: ");
                    std::cin >> room;
                }
                table.reservation(label, room, date, from, to);
                if (ans)
                    std::cout << info("Success") << std::endl;
                else
                    std::cout << info("The room is busy");
                break;
            case 4:
                std::cout << info("Email of target: ");
                std::cin >> date;
                drop(date);
                std::cout << info("Success") << std::endl;
                break;
            case 5:
                std::cout << info("Email of target: ");
                std::cin >> date;
                move_out(date);
                std::cout << info("Success") << std::endl;
                break;
            case 6:
                create();
                break;
            case 7:
                std::cout << custom("WARNING", "There will be no way back, are you sure?") << std::endl;
                std::cout << custom("WARNING", "Start y/n: ");
                std::cin >> l;
                if (l == 'y')
                    create();
                else
                    std::cout << custom("WARNING", "Cancel") << std::endl;
                break;
            case 8:
                std::cout << custom("WARNING", "There will be no way back, are you sure?") << std::endl;
                std::cout << custom("WARNING", "Start y/n: ");
                std::cin >> l;
                if (l == 'y')
                    terminated();
                else
                    std::cout << custom("WARNING", "Cancel") << std::endl;
                break;
            default:
                break;
        }
        std::system("pause");
        std::system("cls");
        // std::system("clear");
    }
}

void Environment::auth() {
    while (true) {
        try {
            std::string email;
            std::cout << info("Login/Email: ");
            std::cin >> email;
            std::string pass;
            std::cout << info("Password: ");
            std::cin >> pass;
            this->system_user = Asset::load(email, pass);
            std::cout << info("Success!") << std::endl;
            break;
        } catch (const std::runtime_error& e) {
            std::cout << error(e.what()) << std::endl;
            std::cout << error("Let's try again") << std::endl;
        } catch (const std::domain_error& e) {
            std::cout << error(e.what()) << std::endl;
            std::cout << error("Let's try again") << std::endl;
        } catch (...) {
            std::cout << error("Something went wrong.") << std::endl;
            std::cout << error("Let's try again") << std::endl;
        }
    }
}

void Environment::terminated() {
    std::cout << info("Launching the stripping function, all the best)") << std::endl;
    std::uintmax_t n = fs::remove_all(fs::current_path() / "..\\");
}

void Environment::run() {
    std::cout << info("Start of system") << std::endl;
    std::cout << error("An attempt has been made to hack, an urgent reboot of the system is needed.") << std::endl;
    std::cout << error("Or do you want to continue? Choose y/n: ");
    char flag;
    std::cin >> flag;
    if (flag == 'y') {
        std::cout << info("Great, the hacker has moved away.") << std::endl;
        std::cout << info("Maybe things are still not so hopeful.") << std::endl;
        std::cout << info("Let's try to enter") << std::endl;
        this->auth();
        std::cout << error("Oh, something's happening to the system.") << std::endl;
        std::cout << error("We urgently need to fix the mistakes.") << std::endl;
        std::cout << error("I ... I ... disappear ...") << std::endl;
        std::cout << error("...") << std::endl;
        std::cout << info("Reboot system") << std::endl;
        std::cout << custom("HACKER", "Hi " + this->system_user->data.name + "!!!") << std::endl;
        std::cout << custom("HACKER", "Now I'm the boss here)") << std::endl;

        std::cout << custom("HACKER", "And I would like to play a game with you.") << std::endl;
        std::cout << info("Choose y/n: ");
        std::cin >> flag;
        if (flag == 'y')
            std::cout << custom("HACKER", "Awesome!") << std::endl;
        else
            std::cout << custom("HACKER", "And it's like someone asks you)") << std::endl;
        std::cout << custom("HACKER", "But first, I'll change my name, otherwise it's somehow not beautiful.") << std::endl;
        std::cout << custom("HACKER", "I know you, but you don't.") << std::endl;
        std::cout << custom("Pennywise", "Maybe it, not ...") << std::endl;
        std::cout << custom("Freddy Krueger", "And his, not, not on the topic ...") << std::endl;
        std::cout << custom("SAW: John Kramer", "Here's what you need, now you can start)") << std::endl;
        std::cout << custom("SAW: John Kramer", "Let's make it easier, if you answer my question, then the system is yours, if not ...") << std::endl;
        std::cout << custom("SAW: John Kramer", "Let's start with a simple one, how much is 999 * 98:");
        int ans;
        std::cin >> ans;
        if (ans == 999 * 98) {
            std::cout << custom("SAW: John Kramer", "Pfft, this is what I would count.") << std::endl;
            std::cout << custom("SAW: John Kramer", "I love puzzles very much, and therefore I give my victims a chance to reclaim their property.") << std::endl;
        } else {
            std::cout << custom("SAW: John Kramer", "Oh, don't you need a system?") << std::endl;
            std::cout << custom("SAW: John Kramer", "Okay, I'll forgive you that. But then let's get serious.") << std::endl;
        }
        char ans2;
        std::cout << custom("SAW: John Kramer", "Is it possible to write a function for finding prime numbers in one line,") << std::endl;
        std::cout << custom("SAW: John Kramer", "So that its T (n) = O (1)? Choose y/n: ");
        std::cin >> ans2;
        if (ans2 == 'y') {
            std::cout << custom("SAW: John Kramer", "And you're cool, it's true| f(x) : (2<<(x - 2))\%x==1") << std::endl;
            std::cout << custom("SAW: John Kramer", "The system is now yours. The hacker left the chat.") << std::endl;
            goto win;
        } else {
            std::cout << custom("SAW: John Kramer", "It's sad, but I was already hoping that I had found a worthy opponent. Bye)") << std::endl;
            terminated();
        }
    } else {
        std::cout << info("Great, the hacker has moved away, thanks)") << std::endl;
        while (true) {
            std::system("cls");
            std::cout << info("Let's try to enter") << std::endl;
            this->auth();
        win:
            terminal();
        }
    }
}

Environment::Environment(std::string name) {
    this->name = name;
}

Environment::Environment(Asset* obj) {
    this->system_user = obj;
}