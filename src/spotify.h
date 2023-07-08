#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;


class Spotify {
    private:
        long expires_at;
        string access_token;
        string client_id;
        string client_secret;
        string redirect_url;
        string refresh_token;
        json current_state;

        int setCache(json tocache);
        json getCache();

        int load(json cache);
        int saveImage();
        int authorize();
        json getCurrentlyPlaying();

    public:
        Spotify();
        bool update();
        bool isPlaying();
};

#endif