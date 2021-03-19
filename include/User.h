#ifndef USER_H
#define USER_H
#include <string>

struct User {
    std::string name;
    std::string surname;
    std::string sex;
    std::string appartment;
    std::string type;
    int age;

    User() {
        name = "";
        surname = "";
        sex = "";
        appartment = "";
        type = "";
        sex = "";
        age = 0;
    }
    User(std::string name, std::string surname, std::string sex, std::string appartment, std::string type, int age) : name(name), surname(surname), sex(sex), appartment(appartment), type(type), age(age) {
    }
};

#endif