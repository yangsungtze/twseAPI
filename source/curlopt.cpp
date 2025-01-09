#include <iostream>
#include <fstream>
#include <curl/curl.h>

// Callback function to write the response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;

    std::string responseBody;

    curl = curl_easy_init();
    if (curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://openapi.twse.com.tw/v1/exchangeReport/STOCK_DAY_ALL");

        // Set headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "accept: text/csv");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set up the callback to capture the response body
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBody);

        // Perform the request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Save the raw response to a file
            std::ofstream outFile("../data/response_raw.csv", std::ios::binary);
            if (outFile.is_open()) {
                outFile << responseBody;
                outFile.close();
                std::cout << "Raw response written to response_raw.csv" << std::endl;
            } else {
                std::cerr << "Failed to open response_raw.csv for writing." << std::endl;
            }
        }

        // Clean up
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    } else {
        std::cerr << "Failed to initialize curl" << std::endl;
    }

    return 0;
}
