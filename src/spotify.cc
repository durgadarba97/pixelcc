// using the libcurl and the json libraries to hit the spotify api. 
// I feel like this is going to suck ...
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "spotify.h"
#include <curl/curl.h>

using namespace std;

int main() {
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.spotify.com/v1/search?q=weezer&type=artist");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(readBuffer, root);
    if(!parsingSuccessful) {
        cout << "Failed to parse JSON" << endl;
        return 1;
    }

    const Json::Value artists = root["artists"];
    cout << artists << endl;
    return 0;
}
