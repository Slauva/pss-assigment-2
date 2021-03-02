#ifndef DIRECTOR_H
#define DIRECTOR_H
#include <string>

#include "Asset.h"

class Director : Asset {
   public:
    void drop(Asset);
    void drop(Asset*);
    void create_exam();
    void newLessen();
};

#endif