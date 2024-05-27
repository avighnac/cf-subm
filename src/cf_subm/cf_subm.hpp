#include "../global/global.hpp"

namespace cf_subm {
    class cf_subm {
        public:
            cf_subm();

            void fetch(const std::string &username);
            void stalk(const std::string &username, int num_problems);
            void savetojson(const std::string &username, const std::string &filename);
            void code(const std::string &problemname, const std::string &username, const std::string &filename);
            void list();
        private:
            std::string file_path;
            Global global_vars;
    };
};