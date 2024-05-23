#include "network.hpp"

size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     std::string *userp) {
  size_t totalSize = size * nmemb;
  userp->append((char *)contents, totalSize);
  return totalSize;
}

std::string fetchHTML(const std::string &url) {
  CURL *curl;
  CURLcode res;
  std::string htmlContent;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      throw std::runtime_error("curl_easy_perform() failed: ");
    }
    curl_easy_cleanup(curl);
  }

  return htmlContent;
}