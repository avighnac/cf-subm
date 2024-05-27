#include <iostream>
#include <vector>
#include <string>
#include "../input/input.hpp"

namespace commandline {
    class commandline {
        public:
            commandline(int argc, char **argv);
            size_t n_arguments();
            void print_usage();
            std::string get_argument(const std::string &message, size_t idx);
            int get_int_argument(const std::string &message, size_t idx);
            std::string get_optional_argument(size_t idx, const std::string &default_);
            int get_optional_int_argument(size_t idx, const int &default_);
        private:
            int argc;
            std::vector<std::string> args;
    };
}