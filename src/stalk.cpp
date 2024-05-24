#include "include.hpp"
#include "network.hpp"
#include <iomanip>

int stalk(const std::string &username, int num_problems) {
  auto submissions = readSubmissionsFromFile("submissions/submissions.dat");
  if (submissions[username].empty()) {
    std::cout << "Error: no submissions found! Did you run 'cf-subm fetch "
              << username << "'?\n";
    return 1;
  }
  std::cout << "Recently solved problems by " << username << ":\n";

  // Determine the maximum width for problem names
  size_t max_problem_name_length = 0;
  for (size_t i = 0; i < num_problems && i < submissions[username].size(); ++i) {
    if (submissions[username][i].problem_name.length() > max_problem_name_length) {
      max_problem_name_length = submissions[username][i].problem_name.length();
    }
  }

  for (size_t i = 0; i < num_problems && i < submissions[username].size(); ++i) {
    const auto& submission = submissions[username][i];
    std::cout << std::left << std::setw(max_problem_name_length + 2)
              << submission.problem_name 
              << " (" << submission.time.formatDateTime() << ")\n";
  }

  return 0;
}