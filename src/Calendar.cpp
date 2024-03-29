#include "../include/control/Calendar.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../lib/nlohmann/json.hpp"
using json = nlohmann::json;

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

void Calendar::save() {
    std::ofstream out("../data/calendar/calendar.json");
    json table;
    for (auto event : this->e) {
        json container = {event.label, {event.from, event.to}};
        table[event.date][std::to_string(event.room)].push_back(container);
    }
    out << table << std::endl;
}

void Calendar::load() {
    std::ifstream in("../data/calendar/calendar.json");
    json table;
    in >> table;
    if (table.is_null())
        return;
    for (auto& dv : table.items()) {  // data - {room - []}
        for (auto& rc : dv.value().items()) {
            auto mer = rc.value().array();          // room - []
            for (int i = 0; i < mer.size(); i++) {  // [[label:[from, to]]]
                Event event;
                event.date = dv.key();
                event.room = std::stoi(rc.key());
                event.label = mer[i][0];
                event.from = mer[i][1][0];
                event.to = mer[i][1][1];
                this->e.push_back(event);
            }
        }
    }
    // print();
    // std::system("pause");
}

Calendar::Calendar(std::string name) {
    this->name = name;
    load();
}
Calendar::~Calendar() {
    save();
}

int Calendar::Event::compareTo(Event& o) {
    std::vector<std::string> _f = split(this->from, ":");
    std::vector<std::string> _t = split(this->to, ":");
    std::vector<std::string> n_f = split(o.from, ":");
    std::vector<std::string> n_t = split(o.to, ":");

    int from = std::stoi(_f[0]) * 60 + std::stoi(_f[1]);
    int to = std::stoi(_t[0]) * 60 + std::stoi(_t[1]);
    int _from = std::stoi(n_f[0]) * 60 + std::stoi(n_f[1]);
    int _to = std::stoi(n_t[0]) * 60 + std::stoi(n_t[1]);

    if (from <= _from && _from <= to)
        return -1;
    if (from <= _to && _to <= to)
        return -1;
    if (_from <= from && to <= _to)
        return -1;
    return 1;
}

bool Calendar::reservation(std::string label, int room, std::string date, std::string from, std::string to) {
    Event new_event;
    new_event.date = date;
    new_event.room = room;
    new_event.label = label;
    new_event.from = from;
    new_event.to = to;
    bool flag = false;

    for (auto event : this->e) {
        if (event.date == date && event.room == room) {
            if (event.compareTo(new_event) == 1) {
                this->e.push_back(new_event);
                return true;
            }
            flag = true;
        }
    }

    if (!flag) {
        this->e.push_back(new_event);
        return true;
    }
    return false;
}

bool Calendar::remove(std::string label, int room, std::string date) {
    int index = -1;
    for (int i = 0; i < this->e.size(); i++)
        if (this->e[i].date == date && this->e[i].room == room && this->e[i].label == label)
            index = i;
    if (index == -1)
        return false;
    else {
        this->e.erase(this->e.begin() + index);
        return true;
    }
}

void Calendar::print() {
    json table;
    for (auto event : this->e) {
        json container = {event.label, {event.from, event.to}};
        table[event.date][event.room].push_back(container);
    }
    std::cout << table.dump(4) << std::endl;
}