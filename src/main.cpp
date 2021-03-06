#include "../include/control/Environment.h"

int main() {
    Environment env("win10");
    env.run();
    std::system("pause");
    return 0;
}