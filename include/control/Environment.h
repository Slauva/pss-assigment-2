#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <string>

#include "../Asset.h"

class Environment {
   public:
    Environment(std::string);
    Environment(Asset* obj);
    void run();
    void auth();
    void create();
    void terminal();
    static std::string info(std::string);
    static std::string error(std::string);
    static std::string debug(std::string);
    static std::string custom(std::string, std::string);

    Asset* system_user;
    std::string name;

    int class_room[4] = {100, 102, 104, 106};
    int labs[4] = {10, 12, 14, 16};
    int lecture_room[2] = {107, 108};
    int profesor_cabinet[3] = {501, 502, 503};
    int director_cabinet[1] = {1000};

    void print_rooms();
    void red_button();
    void terminated();
    void move_out(std::string);
    void drop(std::string);
    void create_exam();
    void new_lessen();
    void open();

    bool access_check(int);
};

#endif