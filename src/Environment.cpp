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

bool in(int target, int* arr, int n) {
    for (int i = 0; i < n; i++)
        if (target == arr[i])
            return true;
    return false;
}

bool Environment::access_check(int room, int mode) {
    if (mode == 1)
        return true;
    switch (this->system_user->level) {
        case Info::BLUE:
            if (in(room, class_room, 5))
                return true;
            if (in(room, lecture_room, 5))
                return true;
            return false;
            break;
        case Info::GREEN:
            if (in(room, class_room, 20))
                return true;
            if (in(room, lecture_room, 20))
                return true;
            if (in(room, conference_room, 20))
                return true;
            return false;
        case Info::YELLOW:
            if (room != director_cabinet)
                return true;
            else if (this->system_user->post == Info::Director)
                return true;
            return false;
        case Info::RED:
            return true;
        default:
            return false;
    }
}

void Environment::red_button() {
    fs::remove_all(fs::current_path() / "..\\data\\persons");
}

void Environment::create() {
    User user;
    Info::Post post;
    Info::Access_Level level;
    std::cout << info("Name: ");
    std::cin >> user.name;
    std::cout << info("Surname: ");
    std::cin >> user.surname;
    std::cout << info("Sex(Male/Female/Other): ");
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
    fs::remove(fs::current_path() / path);
}

void Environment::move_out(std::string email) {
    std::ifstream in("../data/persons/" + email + ".json");
    if (in.fail()) {
        std::cout << error("Incorrect email") << std::endl;
        return;
    }
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
    printf("%15s\t%15s\t%15s\t%15s\t%15s\t%15s\t%30s\t%30s\t\n\n",
           "Name", "Surname", "Sex", "Age", "Type", "Appartment", "Post", "Email");
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

void print_by_floor(const char* name, int* rooms, int n) {
    int prev = -1, cur = -1;
    for (int i = 0; i < n; i++) {
        cur = (int)i / 5;
        if (cur != prev)
            printf("\n%s(floor #%d): ", name, cur + 1);
        printf("%d ", rooms[i]);
        prev = cur;
    }
}

void Environment::print_rooms() {
    std::string line = "=============================================";
    std::cout << line;
    print_by_floor("Class rooms", class_room, 20);
    print_by_floor("Lecture rooms", lecture_room, 20);
    print_by_floor("Lab rooms", labs, 10);
    print_by_floor("Conference rooms", conference_room, 20);
    std::cout << "\nProfessor cabinets(floor #5): ";
    for (int i = 0; i < 4; i++) std::cout << profesor_cabinet[i] << " ";
    std::cout << "\nDirector cabinet(floor #5): " << director_cabinet << std::endl;
    std::cout << line << std::endl;
}

void Environment::open(int mode) {
    print_rooms();
    int room;
    std::cout << info("Which room you need: ");
    std::cin >> room;
    if (access_check(room, mode)) {
        std::cout << info("You got in, sweet brat " + this->system_user->data.name) << std::endl;
    } else {
        std::cout << error("You don't have permission or the room doesn't exist!") << std::endl;
    }
}

void Environment::auth(int mode) {
    if (mode == 1)
        this->system_user = new Asset(Info::Guest, Info::BLUE);
    else
        while (true) {
            try {
                std::string email, pass;
                std::cout << info("Login/Email: ");
                std::cin >> email;
                std::cout << info("Password: ");
                std::cin >> pass;
                this->system_user = Asset::load(email, pass);
                std::cout << info("Success!") << std::endl;
                break;
            } catch (const std::exception& e) {
                std::cout << error(e.what()) << std::endl;
                std::cout << error("Let's try again") << std::endl;
            }
        }
}

void Environment::terminated() {
    std::cout << info("Launching the stripping function, all the best)") << std::endl;
    fs::remove_all(fs::current_path() / "..\\");
}

Environment::Environment(std::string name) {
    this->name = name;
    class_room = new int(20);
    lecture_room = new int(20);
    conference_room = new int(20);
    labs = new int(10);
    profesor_cabinet = new int(4);
    director_cabinet = 510;

    for (int i = 0; i < 20; i++)
        class_room[i] = 100 * ((int)i / 5 + 1) + ((int)i % 5 + 1);
    for (int i = 0; i < 20; i++)
        lecture_room[i] = 100 * ((int)i / 5 + 1) + ((int)i % 5 + 1) + 10;
    for (int i = 0; i < 20; i++)
        conference_room[i] = 100 * ((int)i / 5 + 1) + ((int)i % 5 + 1) + 30;
    for (int i = 0; i < 10; i++)
        labs[i] = 100 * ((int)i / 5 + 1) + ((int)i % 5 + 1) + 20;
    for (int i = 0; i < 4; i++)
        profesor_cabinet[i] = 500 + i;
}