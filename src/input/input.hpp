#include <iostream>

namespace input {
    std::string str();
    std::string str(const std::string &message);
    std::string line();
    std::string line(const std::string &message);
    int integer();
    int integer(const std::string &message);
};