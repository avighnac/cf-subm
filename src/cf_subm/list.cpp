#include "cf_subm.hpp"
#include "../include.hpp"
#include <iostream>

namespace cf_subm {
void cf_subm::list() {
    auto submissions = readSubmissionsFromFile(file_path);
    for (auto &i : submissions) {
      std::cout << i.first << ": " << i.second.size() << " submissions\n";
    }
}
};