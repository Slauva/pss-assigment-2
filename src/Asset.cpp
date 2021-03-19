#include "Asset.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "../lib/nlohmann/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

void checker() {
    bool is_exist = fs::exists(fs::current_path() / "..\\data\\persons");
    if (!is_exist)
        fs::create_directory(fs::current_path() / "..\\data\\persons");
}

//* Constructors
Asset::Asset(User data, Info::Post post, Info::Access_Level level, std::string email, std::string password) {
    this->data = data;
    this->post = post;
    this->level = level;
    this->email = email;
    this->password = std::hash<std::string>{}(password);
    int h = std::hash<std::string>{}(email) / 2;
    this->id = abs(this->password + h);
}

Asset::Asset(Info::Post post, Info::Access_Level level) {
    this->data = User();
    this->post = post;
    this->level = level;
    this->email = "guest@innopolis.university";
    this->password = std::hash<std::string>{}("12345");
    this->id = 0;
}

//* Save data to json file
void Asset::save() {
    json data;

    data["User"] = {
        {"Name", this->data.name},
        {"Surname", this->data.surname},
        {"Sex", this->data.sex},
        {"Age", this->data.age},
        {"Appartment", this->data.appartment},
        {"Type", this->data.type},
    };
    data["Access"] = {
        {"Post", this->post},
        {"Access Level", this->level}};
    data["Auth"] = {
        {"Email", this->email},
        {"Password", this->password},
        {"Id", this->id}};
    checker();
    std::ofstream output("../data/persons/" + this->email + ".json");
    output << data << std::endl;
}

//* Load data from json file
Asset *Asset::load(std::string email, std::string password) {
    checker();
    std::ifstream input("../data/persons/" + email + ".json");

    if (input.fail())
        throw std::runtime_error("User does not exist");

    json import;
    input >> import;

    int pass = std::hash<std::string>{}(password);
    if (import["Auth"]["Password"] != pass)
        throw std::domain_error("Wrong password");

    User user{
        import["User"]["Name"],
        import["User"]["Surname"],
        import["User"]["Sex"],
        import["User"]["Appartment"],
        import["User"]["Type"],
        import["User"]["Age"]};

    return new Asset(user, Info::Post(import["Access"]["Post"]), Info::Access_Level(import["Access"]["Access Level"]), email, password);
}