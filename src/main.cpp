#include "include.hpp"

int main(int argc, char **argv) {
  if (argc == 1) {
    std::cout << "Usage: cf-subm:\n";
    std::cout << "  list\n";
    std::cout << "  fetch [username]\n";
    std::cout << "  stalk [username] [num_problems]\n";
    std::cout << "  savetojson [username] [filename]\n";
    std::cout << "  code [problemname] [username] [filename]\n";
    return 0;
  }
  if (argc >= 2 && std::string(argv[1]) == "fetch") {
    std::string username;
    if (argc == 2) {
      std::cout << "Enter a username: ";
      std::cin >> username;
    } else {
      username = std::string(argv[2]);
    }
    return fetch(username);
  }
  if (argc >= 2 && std::string(argv[1]) == "stalk") {
    std::string username;
    if (argc == 2) {
      std::cout << "Enter a username: ";
      std::cin >> username;
    } else {
      username = std::string(argv[2]);
    }
    int num_problems = 10;
    if (argc >= 4) {
      try {
        num_problems = std::stoi(std::string(argv[3]));
      } catch (std::exception e) {
      }
    }
    return stalk(username, num_problems);
  }
  if (argc >= 2 && std::string(argv[1]) == "savetojson") {
    std::string username;
    if (argc == 2) {
      std::cout << "Enter a username: ";
      std::cin >> username;
    } else {
      username = std::string(argv[2]);
    }
    std::string filename = "output.json";
    if (argc >= 4) {
      filename = std::string(argv[3]);
    }
    return savetojson(username, filename);
  }
  if (argc >= 2 && std::string(argv[1]) == "list") {
    auto submissions = readSubmissionsFromFile("submissions/submissions.dat");
    for (auto &i : submissions) {
      std::cout << i.first << ": " << i.second.size() << " submissions\n";
    }
  }
  if (argc >= 2 && std::string(argv[1]) == "code") {
    std::string problemname;
    if (argc < 3) {
      std::cout << "Enter a problem\'s name: ";
      std::getline(std::cin, problemname);
    } else {
      problemname = std::string(argv[2]);
    }
    std::string username;
    if (argc < 4) {
      std::cout << "Enter a username: ";
      std::cin >> username;
    } else {
      username = std::string(argv[3]);
    }
    std::string filename;
    if (argc >= 5) {
      filename = std::string(argv[4]);
    }
    return code(problemname, username, filename);
  }
}