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

# Build instructions

## Linux

Building on linux is simple enough. Make sure you have `libcurl-dev` installed. The steps for doing this vary in accordance with your Linux distribution. For example, for Ubuntu you would do:
```bash
sudo apt install libcurl4-openssl-dev
```

If this does not work for you, try googling 'how to install libcurl [your distribution]'.

CMake should work right off the bat. Simply do the following:
```bash
cmake -S . -B build
cd build
make
```

## Windows

This is the tricky part. You will first need to install [vcpkg](https://github.com/microsoft/vcpkg), which is a C++ library manager. To do this, first make sure you have `git` installed (considering the fact that you're using GitHub, I'm gonna assume that you do). Then run these commands (taken from [here](https://github.com/curl/curl/blob/master/docs/INSTALL.md#building-using-vcpkg)) in a suitable directory (perhaps C:/):
```cmd
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg integrate install
vcpkg install curl:x64-windows-static
```

Next, you will need to add an environment variable to your system. This variable will store the path of where you've installed vcpkg. For example, if your root folder is in the C:/ directory, your path would be 'C:/vcpkg'.

Press on the windows key and search for 'Edit the system environment variables'. Click on 'Environment Variables...', and below 'System variables', click 'New...'. Type in your variable name as `VCPKG_ROOT` and your path as your respective vcpkg directory's path. Make sure to use forward slashes and not backward ones.

Once you're done with all this, you can finally compile the code using CMake. Do note that you will **not** be able to use MinGW (since libcurl is built with MSVC and not with MinGW. If you're up for it and can successfully build libcurl using MinGW, feel free to do so) and will have to use a Visual Studio kit in CMake. Here's the commands you'll need to run:
```cmd
cmake -S. -Bbuild -G "Visual Studio 17 2022" -T host=x64 -A x64
cmake --build build --config Release --target ALL_BUILD -j 10 --
```