#include "include.hpp"
#include "network.hpp"

int stalk(const std::string &username, int num_problems) {
  auto submissions = readSubmissionsFromFile("submissions/submissions.dat");
  if (submissions[username].empty()) {
    std::cout << "Error: no submissions found! Did you run \'cf-subm fetch "
              << username << "\'?\n";
    return 1;
  }
  std::cout << "Recently solved problems by " << username << ":\n";
  for (size_t i = 0; i < num_problems; ++i) {
    std::cout << submissions[username][i].problem_name << "\n";
  }
  return 0;
}