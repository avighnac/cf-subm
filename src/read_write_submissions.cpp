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

    for (const auto &submission : submissions) {
      size_t nameSize = submission.problem_name.size();
      outFile.write((char *)&nameSize, sizeof(nameSize));
      outFile.write(submission.problem_name.data(), nameSize);

      size_t letterSize = submission.problem_letter.size();
      outFile.write((char *)&letterSize, sizeof(letterSize));
      outFile.write(submission.problem_letter.data(), letterSize);

      outFile.write((char *)&submission.submission_id, sizeof(submission.submission_id));
      outFile.write((char *)&submission.contest_id, sizeof(submission.contest_id));

      outFile.write((char *)&submission.time.month, sizeof(submission.time.month));
      outFile.write((char *)&submission.time.date, sizeof(submission.time.date));
      outFile.write((char *)&submission.time.year, sizeof(submission.time.year));
      outFile.write((char *)&submission.time.hours, sizeof(submission.time.hours));
      outFile.write((char *)&submission.time.minutes, sizeof(submission.time.minutes));
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

    for (auto &submission : submissions) {
      size_t nameSize;
      inFile.read((char *)&nameSize, sizeof(nameSize));
      submission.problem_name.resize(nameSize);
      inFile.read(&submission.problem_name[0], nameSize);

      size_t letterSize;
      inFile.read((char *)&letterSize, sizeof(letterSize));
      submission.problem_letter.resize(letterSize);
      inFile.read(&submission.problem_letter[0], letterSize);

      inFile.read((char *)&submission.submission_id, sizeof(submission.submission_id));
      inFile.read((char *)&submission.contest_id, sizeof(submission.contest_id));

      inFile.read((char *)&submission.time.month, sizeof(submission.time.month));
      inFile.read((char *)&submission.time.date, sizeof(submission.time.date));
      inFile.read((char *)&submission.time.year, sizeof(submission.time.year));
      inFile.read((char *)&submission.time.hours, sizeof(submission.time.hours));
      inFile.read((char *)&submission.time.minutes, sizeof(submission.time.minutes));
    }

    userSubmissions[username] = std::move(submissions);
  }

  inFile.close();
  return userSubmissions;
}