#include "global.hpp"

Global::Global() {
  save_path = "/opt";
#ifdef _WIN32
  TCHAR tcharAppdata[MAX_PATH] = {0};
  SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, tcharAppdata);
  save_path = std::string(tcharAppdata);
#endif
  std::replace(save_path.begin(), save_path.end(), '\\', '/');
}