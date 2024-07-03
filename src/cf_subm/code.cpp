#include "cf_subm.hpp"
#include "../include.hpp"

std::string lowercase(std::string s) {
  for (auto &i : s) {
    i = std::tolower(i);
  }
  return s;
}

namespace cf_subm {
void cf_subm::code(const std::string &problemname, const std::string &username,
         const std::string &filename) {
  auto submissions = readSubmissionsFromFile(file_path);
  std::vector<Submission> matching;
  for (auto &i : submissions[username]) {
    if (lowercase(i.problem_name).find(lowercase(problemname)) != std::string::npos) {
      matching.push_back(i);
    }
  }
  if (matching.empty()) {
    std::cout << "Error: no matching submissions found\n";
    return;
  }
  if (matching.size() != 1) {
    std::cout << "More than one matching submission found:\n";
    for (auto &i : matching) {
      std::cout << "  " << i.problem_name << " from contest " << i.contest_id
                << "\n";
    }
    return;
  }

  auto code = get_submission_code(matching[0]);
  if (filename.empty()) {
    for (auto &i : code) {
      std::cout << i << "\n";
    }
    return;
  } else {
    std::ofstream f(filename);
    for (auto &i : code) {
      f << i << "\n";
    }
    f.close();
    std::cout << "Code saved to " << filename << "\n";
    return;
  }
}
};