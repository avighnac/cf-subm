#include "include.hpp"
#include <fstream>
#include <map>
#include <string>
#include <vector>

void writeSubmissionsToFile(
    const std::map<std::string, std::vector<Submission>> &userSubmissions,
    const std::string &filename) {
  std::ofstream outFile(filename, std::ios::binary);
  if (!outFile) {
    throw std::runtime_error("Unable to open file for writing");
  }

  size_t userCount = userSubmissions.size();
  outFile.write((char *)&userCount, sizeof(userCount));

  for (const auto &[username, submissions] : userSubmissions) {
    size_t usernameSize = username.size();
    outFile.write((char *)&usernameSize, sizeof(usernameSize));
    outFile.write(username.data(), usernameSize);

    size_t size = submissions.size();
    outFile.write((char *)&size, sizeof(size));

    for (const auto &[problem_name, problem_letter, submission_id, contest_id] :
         submissions) {
      size_t nameSize = problem_name.size();
      outFile.write((char *)&nameSize, sizeof(nameSize));
      outFile.write(problem_name.data(), nameSize);

      size_t letterSize = problem_letter.size();
      outFile.write((char *)&letterSize, sizeof(letterSize));
      outFile.write(problem_letter.data(), letterSize);

      outFile.write((char *)&submission_id, sizeof(submission_id));
      outFile.write((char *)&contest_id, sizeof(contest_id));
    }
  }

  outFile.close();
}

std::map<std::string, std::vector<Submission>>
readSubmissionsFromFile(const std::string &filename) {
  std::ifstream inFile(filename, std::ios::binary);
  if (!inFile) {
    throw std::runtime_error("Unable to open file for reading");
  }

  std::map<std::string, std::vector<Submission>> userSubmissions;
  size_t userCount;
  inFile.read((char *)&userCount, sizeof(userCount));

  for (size_t i = 0; i < userCount; ++i) {
    size_t usernameSize;
    inFile.read((char *)&usernameSize, sizeof(usernameSize));
    std::string username(usernameSize, '\0');
    inFile.read(&username[0], usernameSize);

    size_t size;
    inFile.read((char *)&size, sizeof(size));
    std::vector<Submission> submissions(size);

    for (auto &[problem_name, problem_letter, submission_id, contest_id] :
         submissions) {
      size_t nameSize;
      inFile.read((char *)&nameSize, sizeof(nameSize));
      problem_name.resize(nameSize);
      inFile.read(&problem_name[0], nameSize);

      size_t letterSize;
      inFile.read((char *)&letterSize, sizeof(letterSize));
      problem_letter.resize(letterSize);
      inFile.read(&problem_letter[0], letterSize);

      inFile.read((char *)&submission_id, sizeof(submission_id));
      inFile.read((char *)&contest_id, sizeof(contest_id));
    }

    userSubmissions[username] = std::move(submissions);
  }

  inFile.close();
  return userSubmissions;
}