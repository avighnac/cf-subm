#ifdef _WIN32
#include <ShlObj.h>
#endif
#include <algorithm>
#include <string>

class Global {
public:
  std::string save_path;

  Global();
};