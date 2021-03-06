#include "../include/control/Environment.h"

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

std::string Environment::info(std::string str) {
    return "[INFO]:\t " + str;
}

std::string Environment::error(std::string str) {
    return "[ERROR]:\t " + str;
}

std::string Environment::debug(std::string str) {
    return "[DEBUG]:\t " + str;
}

std::string Environment::custom(std::string type, std::string str) {
    return "[" + type + "]:\t " + str;
}

void Environment::auth() {
    while (true) {
        try {
            std::string email;
            std::cout << info("Login/Email: ");
            std::cin >> email;
            std::string pass;
            std::cout << info("Password: ");
            std::cin >> email;
            this->system_user = Asset::load(email, pass);
            std::cout << info("Success!") << std::endl;
            break;
        } catch (const std::runtime_error& e) {
            std::cout << error(e.what()) << std::endl;
            std::cout << error("Let's try again") << std::endl;
        } catch (const std::domain_error& e) {
            std::cout << error(e.what()) << std::endl;
            std::cout << error("Let's try again") << std::endl;
        } catch (...) {
            std::cout << error("Something went wrong.") << std::endl;
            std::cout << error("Let's try again") << std::endl;
        }
    }
}

// void System::terminated() {
//     std::cout << info("Launching the stripping function, all the best)") << std::endl;
//     std::uintmax_t n = fs::remove_all(fs::current_path() / "..\\");
// }

void Environment::run() {
    std::cout << info("Start of system") << std::endl;
    std::cout << error("An attempt has been made to hack, an urgent reboot of the system is needed.") << std::endl;
    std::cout << error("Or do you want to continue? Choose y/n: ");
    char flag;
    std::cin >> flag;
    if (flag == 'y') {
        std::cout << info("Great, the hacker has moved away.") << std::endl;
        std::cout << info("Maybe things are still not so hopeful.") << std::endl;
        std::cout << info("Let's try to enter") << std::endl;
        this->auth();
        std::cout << error("Oh, something's happening to the system.") << std::endl;
        std::cout << error("We urgently need to fix the mistakes.") << std::endl;
        std::cout << error("I ... I ... disappear ...") << std::endl;
        std::cout << error("...") << std::endl;
        std::cout << info("Reboot system") << std::endl;
        std::cout << custom("HACKER", "Hi " + this->system_user->data.name + "!!!") << std::endl;
        std::cout << custom("HACKER", "Now I'm the boss here)") << std::endl;

        std::cout << custom("HACKER", "And I would like to play a game with you.") << std::endl;
        std::cout << info("Choose y/n");
        std::cin >> flag;
        if (flag == 'y')
            std::cout << custom("HACKER", "Awesome!") << std::endl;
        else
            std::cout << custom("HACKER", "And it's like someone asks you)") << std::endl;
        std::cout << custom("HACKER", "But first, I'll change my name, otherwise it's somehow not beautiful.") << std::endl;
        std::cout << custom("HACKER", "I know you, but you don't.") << std::endl;
        std::cout << custom("Pennywise", "Maybe it, not ...") << std::endl;
        std::cout << custom("Freddy Krueger", "And his, not, not on the topic ...") << std::endl;
        std::cout << custom("SAW: John Kramer", "Here's what you need, now you can start)") << std::endl;
    }
}

Environment::Environment() {
    // this->run();
    std::cout << debug("Constructor") << std::endl;
}

Environment::Environment(Asset* obj) {
    std::cout << debug("Constructor-2") << std::endl;
    this->system_user = obj;
}