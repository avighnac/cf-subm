#include "include.hpp"
#include "network.hpp"
#include <algorithm>
// #include <csignal>
#include <curl/curl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int get_num_submission_pages(const std::string &username) {
  std::string url =
      "https://codeforces.com/submissions/" + username + "/page/1000000000";
  std::string html = fetchHTML(url);
  if (html.find("data-submission-id") == std::string::npos) {
    throw std::runtime_error("No submissions found");
  }
  size_t idx = html.rfind("/page/");
  if (idx == std::string::npos) {
    return 1;
  }
  std::string num;
  for (size_t i = idx + 6; i < html.length(); ++i) {
    if (!std::isdigit(html[i])) {
      break;
    }
    num.push_back(html[i]);
  }
  return std::stoi(num);
}

std::vector<std::string> get_html_contents(const std::string &url,
                                           bool omit_newlines = true) {
  std::vector<std::string> contents;
  std::string html = fetchHTML(url);
  std::string cur_line;
  for (size_t i = 0; i < html.length(); ++i) {
    if (html[i] != '\n') {
      cur_line.push_back(html[i]);
    } else {
      if (!cur_line.empty()) {
        contents.push_back(cur_line);
        cur_line.clear();
      } else if (!omit_newlines) {
        contents.push_back(cur_line);
      }
    }
  }
  return contents;
}

std::string trim(std::string s) {
  std::string ans;
  while (!s.empty() && (s.back() == ' ' || s.back() == '\r')) {
    s.pop_back();
  }
  std::reverse(s.begin(), s.end());
  while (!s.empty() && (s.back() == ' ' || s.back() == '\r')) {
    s.pop_back();
  }
  std::reverse(s.begin(), s.end());
  return s;
}

void replace_all(std::string &str, const std::string &from,
                 const std::string &to) {
  if (from.empty())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

std::vector<Submission>
get_accepted_submissions(const std::string &submission_page_url, std::set<std::string> &st) {
  std::vector<std::string> contents = get_html_contents(submission_page_url);
  std::vector<Submission> problems;
  std::string time_str;
  for (size_t i = 1; i < contents.size(); ++i) {
    if (contents[i].find("format-time") != std::string::npos) {
      bool enabled = false;
      time_str.clear();
      for (size_t j = contents[i].find("format-time"); j < contents[i].length(); ++ j) {
        if (contents[i][j] == '>') {
          enabled = true;
          continue;
        }
        if (contents[i][j] == '<') {
          enabled = false;
        }
        if (enabled) {
          time_str.push_back(contents[i][j]);
        }
      }
    }
    if (contents[i].find(" - ") != std::string::npos &&
        contents[i - 1].find("/contest/") != std::string::npos) {
      std::string problem = trim(contents[i]);
      bool is_solution_accepted = false;
      std::string submission_id;
      std::string contest_id;
      for (size_t idx = contents[i - 1].find("/contest/") + 9;
           idx < contents[i - 1].length(); ++idx) {
        if (contents[i - 1][idx] == '/') {
          break;
        }
        contest_id.push_back(contents[i - 1][idx]);
      }
      for (; i < contents.size(); ++i) {
        if (contents[i].find("</tr>") != std::string::npos) {
          break;
        }
        if (contents[i].find("submissionVerdict=\"OK\"") != std::string::npos &&
            contents[i].find("class='verdict-accepted'") != std::string::npos) {
          is_solution_accepted = true;
        }
        if (submission_id.empty() &&
            contents[i].find("submissionId=\"") != std::string::npos) {
          for (size_t idx = contents[i].find("submissionId=\"") + 14;
               idx < contents[i].length(); ++idx) {
            if (contents[i][idx] == '\"') {
              break;
            }
            submission_id.push_back(contents[i][idx]);
          }
        }
      }
      if (!is_solution_accepted) {
        continue;
      }
      if (!st.count(problem)) {
        st.insert(problem);
        replace_all(problem, "?", "");
        std::string letter = trim(problem.substr(0, problem.find('-')));
        for (auto &i : letter) {
          i = std::tolower(i);
        }
        problems.push_back(
            {problem, letter, std::stoi(submission_id), std::stoi(contest_id), Time(time_str)});
      }
    }
  }
  return problems;
}

std::string decodeHTMLEntities(const std::string &str) {
  static const std::unordered_map<std::string, std::string> htmlEntities = {
      {"&quot;", "\""}, {"&#39;", "\'"}, {"&amp;", "&"},
      {"&lt;", "<"},    {"&gt;", ">"},   {"&nbsp;", " "}};
  std::string ans = str;
  for (auto &i : htmlEntities) {
    replace_all(ans, i.first, i.second);
  }
  return ans;
}

std::vector<std::string> get_submission_code(const Submission &submission) {
  std::string url = "https://codeforces.com/contest/" +
                    std::to_string(submission.contest_id) + "/submission/" +
                    std::to_string(submission.submission_id);
  auto contents = get_html_contents(url, false);
  bool submission_started = false;
  std::vector<std::string> ans;
  for (size_t i = 0; i < contents.size(); ++i) {
    if (!submission_started && !contents[i].empty() &&
        contents[i].find(" program-source") != std::string::npos) {
      submission_started = true;
      std::string first_line;
      for (size_t j = contents[i].length() - 1; j >= 0; --j) {
        if (contents[i][j] == '>') {
          break;
        }
        first_line.push_back(contents[i][j]);
      }
      std::reverse(first_line.begin(), first_line.end());
      ans.push_back(first_line);
    } else if (submission_started) {
      if (!contents[i].empty() &&
          contents[i].find("</pre>") != std::string::npos) {
        std::string last_line;
        for (size_t j = 0; j < contents[i].length(); ++j) {
          if (contents[i][j] == '<') {
            break;
          }
          last_line.push_back(contents[i][j]);
        }
        ans.push_back(last_line);
        break;
      } else {
        ans.push_back(contents[i]);
      }
    }
  }

  for (auto &i : ans) {
    while (!i.empty() && i.back() == '\r') {
      i.pop_back();
    }
    i = decodeHTMLEntities(i);
  }

  if (ans.empty()) {
    throw std::runtime_error(
        "Error: the submission is empty! (probably 403 forbidden)");
  }

  return ans;
}

std::string get_submission_filename(const Submission &submission) {
  std::string ans = trim(
      submission.problem_name.substr(submission.problem_name.find('-') + 1));
  replace_all(ans, " ", "_");
  for (auto &i : ans) {
    i = std::tolower(i);
  }
  ans += ".cpp";
  return ans;
}

std::map<std::string, std::vector<Submission>> submissions;

// void signalHandler(int signum) {
//   std::cout << "\nInterrupt signal (" << signum << ") received. Saving
//   data..."
//             << std::endl;

//   try {
//     writeSubmissionsToFile(submissions, "submissions/submissions.dat");
//   } catch (const std::runtime_error &e) {
//     std::cerr << "Failed to save data: " << e.what() << std::endl;
//   }

//   std::exit(signum);
// }

bool file_exists(std::string filename) {
  std::ifstream f(filename);
  if (f.good()) {
    f.close();
    return true;
  }
  return false;
}

int fetch(const std::string &username) {
  // std::signal(SIGINT, signalHandler);
  const int num_pages = get_num_submission_pages(username);
  std::cout << num_pages << " submission pages found.\n";

  std::set<int> existing_submissions;

  if (!std::filesystem::exists("submissions")) {
    std::filesystem::create_directory("submissions");
  } else if (file_exists("submissions/submissions.dat")) {
    submissions = readSubmissionsFromFile("submissions/submissions.dat");
    for (auto &i : submissions[username]) {
      existing_submissions.insert(i.submission_id);
    }
  }

  std::set<std::string> st;
  for (auto &i : submissions[username]) {
    st.insert(i.problem_name);
  }
  for (size_t i = 1; i <= num_pages; ++i) {
    std::cout << "On page " << i << "...\n";
    std::vector<Submission> subs;
    try {
      subs = get_accepted_submissions("https://codeforces.com/submissions/" +
                                      username + "/page/" + std::to_string(i), st);
    } catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
      writeSubmissionsToFile(submissions, "submissions/submissions.dat");
      return 0;
    }

    bool ran_into_existing = false;

    for (auto &sub : subs) {
      if (existing_submissions.count(sub.submission_id)) {
        ran_into_existing = true;
        break;
      }
      std::cout << "Processed submission for " << sub.problem_name << "\n";
      submissions[username].push_back(sub);
      existing_submissions.insert(sub.submission_id);
    }

    if (ran_into_existing) {
      break;
    }
  }

  writeSubmissionsToFile(submissions, "submissions/submissions.dat");
  std::cout << submissions[username].size() << " submissions found.\n";
  return 0;
}