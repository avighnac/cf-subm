#include <string>
#include <unordered_map>
#include <stdexcept>

// In russian time
class Time {
public:
  int month;
  int date;
  int year;

  int hours;
  int minutes;

  Time();
  Time(const std::string &s);
  std::string formatDateTime() const;
};