#include <curl/curl.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include "spotify.h"


using namespace std;
using json = nlohmann::json;

typedef unsigned char uchar;
static const string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static string base64_encode(const string &in) {
    string out;

    int val=0, valb=-6;
    for (uchar c : in) {
        val = (val<<8) + c;
        valb += 8;
        while (valb>=0) {
            out.push_back(b[(val>>valb)&0x3F]);
            valb-=6;
        }
    }
    if (valb>-6) out.push_back(b[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
}

// callback function for curl
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// parse the response from the server to a json object
json jsonify(string response) {
    json j = json::parse(response);
    return j;
}

json defaultRes() {
    return jsonify("{\"is_playing\" : false, \"item\" : { \"id\" : 0}}");
}

Spotify::Spotify() {
    // read these from .config
    json tojson;
    ifstream f(".config");

    f >> tojson;
    f.close();
    client_id = tojson["client_id"];
    client_secret = tojson["client_secret"];
    redirect_url = tojson["redirect_url"];
    refresh_token = tojson["refresh_token"];;
    current_state = defaultRes();
    

    authorize();
}

int Spotify::authorize() {
    CURL* curl;
    string readBuffer = "";
    string url = "https://accounts.spotify.com/api/token";
    string refresh = "refresh_token=" + refresh_token;

    // Initialize curl
    curl = curl_easy_init();
    if (curl) {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the headers
        string authorization_header = "Authorization: Basic " + base64_encode(client_id + ":" + client_secret);
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        headers = curl_slist_append(headers, authorization_header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the form data
        string form_data = "grant_type=refresh_token&" + refresh;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, form_data.c_str());

        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        curl_easy_perform(curl);

        // Cleanup
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    json response = jsonify(readBuffer);
    setCache(response);

    return 1;
}

// this method does wayy too much break it down bub
json Spotify::getCurrentlyPlaying() {
    CURL* curl;
    CURLcode code;
    string readBuffer = "";
    string url = "https://api.spotify.com/v1/me/player/currently-playing";

    // Initialize curl
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the headers
        string authorization_header = "Authorization: Bearer " + access_token;
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, authorization_header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the WriteCallback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        code = curl_easy_perform(curl);

        // Cleanup
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    if(readBuffer == "") {
        return defaultRes();
    }

    return jsonify(readBuffer);
}

int Spotify::saveImage() {
    string url = current_state["item"]["album"]["images"][0]["url"];
    string tempFile = "./tmp/spotify_tmp.png";
    string finalFile = "./tmp/spotify.png";

    // Download the image file to a temporary location
    string command = "wget -q -O " + tempFile + " " + url;
    system(command.c_str());

    // Move the temporary file to the final destination
    command = "mv " + tempFile + " " + finalFile;
    system(command.c_str());

    return 1;
}

// read the .cache file and return the json object
json Spotify::getCache() {
    ifstream file;
    file.open(".cache");
    string line;
    string cache;
    while (getline(file, line)) {
        cache += line;
    }
    file.close();
    json tojson = jsonify(cache);
    load(tojson);
    return tojson;
}

int Spotify::setCache(json tocache) {
    ofstream file;
    file.open(".cache");
    file << tocache;
    file.close();
    load(tocache);
    return 1;
}

// syncs the cache with instance variables.
// they all need to be loaded at the same time, a universal load function makes sense to me
int Spotify::load(json cache) {
    cout << cache << endl;
    expires_at = time(nullptr) + cache["expires_in"].get<time_t>();
    access_token = cache["access_token"];

    return 1;
}

bool Spotify::isPlaying() {
    return current_state["is_playing"];
}

bool Spotify::update() {

    if(time(nullptr) > expires_at) {
        cout << "Token expired, refreshing..." << endl;
        authorize();
    }

    json current = getCurrentlyPlaying();
    if(current["item"]["id"] != current_state["item"]["id"]) {
        current_state = current;
        saveImage();
        return true;
    }
    current_state = current;
    return false;
}