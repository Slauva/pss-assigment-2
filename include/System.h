#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>

#include "Asset.h"

class System {
   public:
    System(Asset);
    System(Asset*);
    void run();
    void auth();
    void create();
    std::string info(std::string);
    std::string error(std::string);
    std::string debug(std::string);
};

#endif