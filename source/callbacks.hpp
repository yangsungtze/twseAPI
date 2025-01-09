#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
size_t HeaderCallback(char* buffer, size_t size, size_t nitems, std::string* headerData);
