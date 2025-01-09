#include "main.h"
#include <iostream>
#include <fstream> // For file operations
#include <string>
#include <curl/curl.h>

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
            //std::ofstream outFile("../data/response.json");
            std::ofstream outFile("response.json");
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
