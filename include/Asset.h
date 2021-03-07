#ifndef ASSET_H
#define ASSET_H

#include "Info.h"
#include "User.h"

class Asset {
   public:
    User data;
    Info::Post post;
    Info::Access_Level level;
    std::string email;
    Asset(User data, Info::Post post, Info::Access_Level level, std::string email, std::string password);
    ~Asset() { save(); };

    int getId() { return this->id; };
    void save();
    static Asset* load(std::string email, std::string password);

   private:
    int password;
    int id;
};

#endif