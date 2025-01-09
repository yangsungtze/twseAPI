#include "main.h"
#include <iostream>
#include <fstream> // For file operations
#include <string>
#include <curl/curl.h>

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

int main() {
    CURL* curl;
    CURLcode res;

    std::string responseBody;
    std::string responseHeaders; // To store the headers

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://openapi.twse.com.tw/v1/exchangeReport/STOCK_DAY_ALL");

        // Set up the callback for the response body
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBody);

        // Set up the callback for the headers
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &responseHeaders);

        // Perform the request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Print the response headers and body
            std::cout << "Headers:\n" << responseHeaders << std::endl;
            std::cout << "Body:\n" << responseBody << std::endl;

            // Save the response body to a file
            std::ofstream outFile("../data/response.json");
            if (outFile.is_open()) {
                outFile << responseBody;
                outFile.close();
                std::cout << "Response saved to 'response.json'" << std::endl;
            } else {
                std::cerr << "Failed to open file for writing." << std::endl;
            }
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    return 0;
}
