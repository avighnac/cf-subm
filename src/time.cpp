#include "include.hpp"

Time::Time() {}

Time::Time(const std::string &s) {
    static const std::unordered_map<std::string, int> month_to_number = {
        {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5},
        {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10},
        {"Nov", 11}, {"Dec", 12}
    };
    std::string month = s.substr(0, s.find('/'));
    std::string date, year;
    for (size_t i = s.find('/') + 1; i < s.length(); ++ i) {
        if (s[i] == '/') {
            break;
        }
        date.push_back(s[i]);
    }
    for (size_t i = s.rfind('/') + 1; i < s.length(); ++ i) {
        if (s[i] == ' ') {
            break;
        }
        year.push_back(s[i]);
    }
    this->month = month_to_number.find(month)->second;
    this->date = std::stoi(date);
    this->year = std::stoi(year);

    std::string hours, minutes;
    for (size_t i = s.find(' ') + 1; i < s.length(); ++ i) {
        if (s[i] == ':') {
            break;
        }
        hours.push_back(s[i]);
    }
    for (size_t i = s.find(':') + 1; i < s.length(); ++ i) {
        minutes.push_back(s[i]);
    }

    this->hours = std::stoi(hours);
    this->minutes = std::stoi(minutes);
}