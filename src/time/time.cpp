#include "time.hpp"

Time::Time() {}

Time::Time(const std::string &s) {
  static const std::unordered_map<std::string, int> month_to_number = {
      {"Jan", 1}, {"Feb", 2},  {"Mar", 3},  {"Apr", 4},
      {"May", 5}, {"Jun", 6},  {"Jul", 7},  {"Aug", 8},
      {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};
  std::string month = s.substr(0, s.find('/'));
  std::string date, year;
  for (size_t i = s.find('/') + 1; i < s.length(); ++i) {
    if (s[i] == '/') {
      break;
    }
    date.push_back(s[i]);
  }
  for (size_t i = s.rfind('/') + 1; i < s.length(); ++i) {
    if (s[i] == ' ') {
      break;
    }
    year.push_back(s[i]);
  }
  this->month = month_to_number.find(month)->second;
  this->date = std::stoi(date);
  this->year = std::stoi(year);

  std::string hours, minutes;
  for (size_t i = s.find(' ') + 1; i < s.length(); ++i) {
    if (s[i] == ':') {
      break;
    }
    hours.push_back(s[i]);
  }
  for (size_t i = s.find(':') + 1; i < s.length(); ++i) {
    minutes.push_back(s[i]);
  }

  this->hours = std::stoi(hours);
  this->minutes = std::stoi(minutes);
}

std::string Time::formatDateTime() const {
  static const std::unordered_map<int, std::string> number_to_month = {
      {1, "January"},   {2, "February"}, {3, "March"},     {4, "April"},
      {5, "May"},       {6, "June"},     {7, "July"},      {8, "August"},
      {9, "September"}, {10, "October"}, {11, "November"}, {12, "December"}};

  static const std::unordered_map<int, std::string> suffixes = {
      {1, "st"},  {2, "nd"},  {3, "rd"}, {21, "st"},
      {22, "nd"}, {23, "rd"}, {31, "st"}};

  std::string suffix = "th";
  auto suffixIt = suffixes.find(date);
  if (suffixIt != suffixes.end()) {
    suffix = suffixIt->second;
  }

  auto monthIt = number_to_month.find(month);
  if (monthIt == number_to_month.end()) {
    throw std::invalid_argument("Invalid month number: " +
                                std::to_string(month));
  }

  char buffer[100];
  snprintf(buffer, sizeof(buffer), "%s %d%s, %d at %02d:%02d",
           monthIt->second.c_str(), date, suffix.c_str(), year, hours, minutes);
  return std::string(buffer);
}

bool operator>(const Time &a, const Time &b) {
  if (a.year != b.year) {
    return a.year > b.year;
  }
  if (a.month != b.month) {
    return a.month > b.month;
  }
  if (a.date != b.date) {
    return a.date > b.date;
  }
  if (a.hours != b.hours) {
    return a.hours > b.hours;
  }
  return a.minutes > b.minutes;
}