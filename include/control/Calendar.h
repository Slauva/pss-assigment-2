#ifndef CALENDAR_H
#define CALENDAR_H
#include <string>

#include "../Asset.h"

class Calendar {
   public:
    Calendar();
    auto create_exam(std::string, std::string, std::string, Asset, std::string);
    auto reservation(std::string, std::string, std::string, Asset, std::string);
    auto remove(std::string, std::string);
    void save();
    void load();
    ~Calendar();
};

#endif