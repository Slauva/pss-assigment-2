#ifndef ASSET_H
#define ASSET_H

#include "Post.h"
#include "Room.h"
#include "User.h"

class Asset {
   public:
    User data;
    Post post;
    Access_Level level;
    std::string email;

    Asset(User data, Post post, Access_Level level, std::string email, std::string password);

    int getId() { return this->id; };
    void save();
    Asset* load(std::string email, std::string password);

   private:
    int password;
    int id;
};

#endif