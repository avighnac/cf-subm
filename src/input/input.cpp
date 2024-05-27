#include "input.hpp"

std::string input::str() {
    std::string str;
    std::cin >> str;
    return str;
}

std::string input::str(const std::string &message) {
    std::cout << message;
    return input::str();
}

std::string input::line() {
    std::string str;
    std::getline(std::cin, str);
    return str;
}

std::string input::line(const std::string &message) {
    std::cout << message;
    return input::line();
}

int input::integer() {
    int x;
    std::cin >> x;
    return x;
}

int input::integer(const std::string &message) {
    std::cout << message;
    return input::integer();
}