#include "commandline.hpp"

namespace commandline {
    commandline::commandline(int argc, char **argv) : argc(argc) {
        args.resize(argc);
        for (size_t i = 0; i < argc; ++i) {
            args[i] = std::string(argv[i]);
        }
    }

    size_t commandline::n_arguments() {
        return argc;
    }

    void commandline::print_usage() {
        std::cout << "Usage: cf-subm:\n";
        std::cout << "  list\n";
        std::cout << "  fetch [username]\n";
        std::cout << "  stalk [username] [num_problems]\n";
        std::cout << "  savetojson [username] [filename]\n";
        std::cout << "  code [problemname] [username] [filename]\n";
    }

    std::string commandline::get_argument(const std::string &message, size_t idx) {
        if (args.size() >= idx + 1) {
            return args[idx];
        }
        if (message == "problem\'s name") {
            return input::line("Enter " + message + ": ");
        }
        return input::str("Enter " + message + ": ");
    }

    int commandline::get_int_argument(const std::string &message, size_t idx) {
        bool successful = true;
        if (args.size() >= idx + 1) {
            int x;
            try {
                x = std::stoi(args[idx]);
            } catch (std::exception e) {
                successful = false;
            }
            if (successful) {
                return x;
            }
        }
        return input::integer("Enter " + message + ": ");
    }

    std::string commandline::get_optional_argument(size_t idx, const std::string &default_) {
        if (args.size() >= idx + 1) {
            return args[idx];
        }
        return default_;
    }

    int commandline::get_optional_int_argument(size_t idx, const int &default_) {
        bool successful = true;
        if (args.size() >= idx + 1) {
            int x;
            try {
                x = std::stoi(args[idx]);
            } catch (std::exception e) {
                successful = false;
            }
            if (successful) {
                return x;
            }
        }
        return default_;
    }
}