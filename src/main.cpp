#include "include.hpp"
#include "input/input.hpp"
#include "commandline/commandline.hpp"
#include "cf_subm/cf_subm.hpp"

int main(int argc, char **argv) {
  commandline::commandline cli(argc, argv);
  cf_subm::cf_subm cf_subm;
  
  if (cli.n_arguments() == 1) {
    cli.print_usage();
    return 0;
  }

  const std::string function = cli.get_argument("function", 1);
  if (function == "fetch") {
    std::string username = cli.get_argument("username", 2);
    cf_subm.fetch(username);
  }
  else if (function == "stalk") {
    std::string username = cli.get_argument("username", 2);
    int num_problems = cli.get_optional_int_argument(3, 10);
    cf_subm.stalk(username, num_problems);
  } else if (function == "savetojson") {
    std::string username = cli.get_argument("username", 2);
    std::string filename = cli.get_optional_argument(3, "output.json");
    cf_subm.savetojson(username, filename);
  } else if (function == "list") {
    cf_subm.list();
  } else if (function == "code") {
    std::string username = cli.get_argument("username", 2);
    std::string problemname = cli.get_argument("problem\'s name", 3);
    std::string filename = cli.get_optional_argument(4, "");
    cf_subm.code(problemname, username, filename);
  }
}