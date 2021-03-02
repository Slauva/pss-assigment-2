#ifndef ADMIN_H
#define ADMIN_H
#include <string>

#include "Asset.h"

class Admin : Asset {
   public:
    void red_button();
    void change_of_government();
    void shadowing(Asset);
    void shadowing(Asset*);
    void drop(std::string);
    void move_out(Asset);
    void move_out(Asset*);
};

#endif