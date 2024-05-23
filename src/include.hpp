#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Submission {
  std::string problem_name;
  std::string problem_letter;
  int submission_id;
  int contest_id;
};

std::vector<std::string> get_submission_code(const Submission &submission);
void writeSubmissionsToFile(
    const std::map<std::string, std::vector<Submission>> &userSubmissions,
    const std::string &filename);
std::map<std::string, std::vector<Submission>>
readSubmissionsFromFile(const std::string &filename);

int fetch(const std::string &username);
int stalk(const std::string &username, int num_problems);
int savetojson(const std::string &username, const std::string &filename);
int code(const std::string &problemname, const std::string &username,
         const std::string &filename);