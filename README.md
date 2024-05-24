# cf-subm
A (hacky) tool to manage codeforces submissions.

# Usage
```
Usage: cf-subm:
  list
  fetch [username]
  stalk [username] [num_problems]
  savetojson [username] [filename]
  code [problemname] [username] [filename]
```

- `list` lists the number of submissions stored for each user.
- `fetch` fetches all (accepted) submissions made by the user. If run again (after making additional submissions), it keeps adding submissions until finding one that it has already encountered.
- `stalk` displays the most recently solved problems by a user.
- `savetojson` exports the `Submission` struct's data for each submission for a particular user to a json file.
- `code` downloads an accepted submission's code.

# Submission struct
```cpp
// In russian time
class Time {
public:
  int month;
  int date;
  int year;

  int hours;
  int minutes;
};

struct Submission {
  std::string problem_name;
  std::string problem_letter;
  int submission_id;
  int contest_id;
  Time time;
};
```
