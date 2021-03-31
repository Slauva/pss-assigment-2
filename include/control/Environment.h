#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <string>

#include "../Asset.h"

class Environment {
   public:
    Environment(std::string);
    void auth(int);
    void create();
    static std::string info(std::string);
    static std::string error(std::string);
    static std::string debug(std::string);
    static std::string custom(std::string, std::string);

    Asset* system_user;
    std::string name;

    int* class_room;
    int* labs;
    int* lecture_room;
    int* conference_room;
    int* profesor_cabinet;
    int director_cabinet;

    void print_rooms();
    void print_users();
    void red_button();
    void terminated();
    void move_out(std::string);
    void drop(std::string);
    void create_exam();
    void new_lessen();
    void open(int);

    bool access_check(int, int);
};

#endif