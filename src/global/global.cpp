#include "global.hpp"

#ifdef __APPLE__
#include <unistd.h>   // For POSIX API
#include <pwd.h>      // For macOS-specific APIs

std::string getApplicationSupportPath() {
  const char *homeDir;
  std::string appSupportPath;
  struct passwd *pw = getpwuid(getuid());
  homeDir = pw->pw_dir;
  appSupportPath = std::string(homeDir) + "/Library/Application Support";
  return appSupportPath;
}
#endif

Global::Global() {
  save_path = "/opt";
#ifdef _WIN32
  TCHAR tcharAppdata[MAX_PATH] = {0};
  SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, tcharAppdata);
  save_path = std::string(tcharAppdata);
#elif __APPLE__
  save_path = getApplicationSupportPath();
#endif
  std::replace(save_path.begin(), save_path.end(), '\\', '/');
}