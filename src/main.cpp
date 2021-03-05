#include <windows.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

// #include "../include/Asset.h"

int main() {
    // User user;
    // std::cin >> user.name;
    // std::cin >> user.surname;
    // std::cin >> user.sex;
    // std::cin >> user.type;
    // std::cin >> user.age;
    // std::cin >> user.appartment;
    // std::string email;
    // std::cin >> email;
    // std::string pass;
    // std::cin >> pass;

    // Asset prof(user, Info::Professors, Info::RED, email, pass);
    // prof.save();

    // Asset* loaded = Asset::load(email, pass);
    // std::cout << loaded->data.name << std::endl;
    // fs::path dir = "";
    std::uintmax_t n = fs::remove_all(fs::current_path() / "..\\data\\persons");
    std::cout << n;
    std::system("pause");
    return 0;
}