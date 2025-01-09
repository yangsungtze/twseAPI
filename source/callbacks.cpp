#include "callbacks.hpp"

// Callback function to write response body
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

// Callback function to process headers
size_t HeaderCallback(char* buffer, size_t size, size_t nitems, std::string* headerData) {
    size_t totalSize = size * nitems;
    headerData->append(buffer, totalSize);
    return totalSize;
}