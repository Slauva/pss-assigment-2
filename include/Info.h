#ifndef INFO_H
#define INFO_H

class Info {
   public:
    enum Post {
        Guest = -1,
        Students,       //0
        Professors,     //2
        Lab_Employees,  //1
        Director,       //2
        Admins          //3
    };

    enum Access_Level {
        BLUE = -1,
        NO_LEVEL = 0,
        GREEN = 1,
        YELLOW = 2,
        RED = 3,
    };

    enum Rooms {
        Class_room = GREEN,
        Lecture_room = GREEN,
        Conference_room = GREEN,
        Cabinet = YELLOW,
        Director_cabinet = YELLOW,
        ALL = RED
    };
};

#endif