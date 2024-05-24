#include "include.hpp"
#include <fstream>

int savetojson(const std::string &username, const std::string &filename) {
  auto submissions = readSubmissionsFromFile("submissions/submissions.dat");
  if (submissions[username].empty()) {
    std::cout << "Error: no submissions found! Did you run \'cf-subm fetch "
              << username << "\'?\n";
    return 1;
  }
  std::ofstream f(filename);
  f << "{\"problems\": {\n";
  for (size_t idx = 0; idx < submissions[username].size(); ++idx) {
    Submission &i = submissions[username][idx];
    f << "\t\"" << i.contest_id << i.problem_letter << "\": {\n";
    f << "\t\t\"name\": \"" << i.problem_name << "\",\n";
    f << "\t\t\"letter\": \"" << i.problem_letter << "\",\n";
    f << "\t\t\"submission_id\": \"" << i.submission_id << "\",\n";
    f << "\t\t\"contest_id\": \"" << i.contest_id << "\",\n";
    f << "\t\t\"time\": {\n";
    f << "\t\t\t\"month\": " << i.time.month << ",\n";
    f << "\t\t\t\"date\": " << i.time.date << ",\n";
    f << "\t\t\t\"year\": " << i.time.year << ",\n";
    f << "\t\t\t\"hours\": " << i.time.hours << ",\n";
    f << "\t\t\t\"minutes\": " << i.time.minutes << "\n";
    f << "\t\t}\n";
    if (idx == submissions[username].size() - 1) {
      f << "\t}\n";
    } else {
      f << "\t},\n";
    }
  }
  f << "}}";
  f.close();
  std::cout << "Data written to " << filename << "\n";
  return 0;
}