#ifndef INFO_H
#define INFO_H

class Info {
   public:
    enum Post {
        Students,
        Professors,
        Lab_Employees,
        Director,
        Admins
    };

    enum Access_Level {
        GREEN = 1,
        YELLOW = 2,
        RED = 3,
        NO_LEVEL = 0
    };

    enum Rooms {
        Class_room = GREEN,
        Lecture_room = GREEN,
        Conference_room = GREEN,
        Cabinet = YELLOW,
        Director_cabinet = RED
    };
};

#endif