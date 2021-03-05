#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>

#include "../Asset.h"

class System {
   public:
    System();
    System(Asset);
    System(Asset*);
    void run();
    void auth();
    void create();
    std::string info(std::string);
    std::string error(std::string);
    std::string debug(std::string);

    Asset system_user;

    int class_room[4] = {100, 102, 104, 106};
    int labs[4] = {10, 12, 14, 16};
    int lecture_room[2] = {107, 108};
    int profesor_cabinet[3] = {501, 502, 503};
    int director_cabinet[1] = {1000};

    void red_button();
    void change_of_government();
    void shadowing(Asset);
    void shadowing(Asset*);
    void drop(std::string);
    void move_out(Asset);
    void move_out(Asset*);
    void drop(Asset);
    void drop(Asset*);
    void create_exam();
    void new_lessen();
    void open(int);

    bool access_check(Asset);
    bool access_check(Asset*);
};

#endif