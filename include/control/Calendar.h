#ifndef CALENDAR_H
#define CALENDAR_H
#include <string>
#include <vector>

#include "../Asset.h"
#include "../lib/nlohmann/json.hpp"
using json = nlohmann::json;

class Calendar {
   public:
    Calendar(std::string);
    bool reservation(std::string, int, std::string, std::string, std::string);
    bool remove(std::string, int, std::string);
    void print();
    void save();
    void load();
    ~Calendar();

    struct Event {
        std::string date;  // 'dd/mm/yyyy'
        int room;
        std::string label;
        std::string from;  // hh:mm
        std::string to;    // hh:mm
        int compareTo(Event& o);
    };

    std::vector<Event> e;
    std::string name;
};

#endif