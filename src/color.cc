// using to difne color definitions
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
// #include "color.h"

namespace color {
    struct rgb
    {
        float r;
        float g;
        float b;
    };

    struct hsv
    {
        float h;
        float s;
        float v;
    };

    rgb hsv_to_rgb(hsv in) {
        float c = in.v * in.s;
        float x = c * (1 - abs(fmod(in.h / 60.0, 2) - 1));
        float m = in.v - c;

        float r = 0;
        float g = 0;
        float b = 0;

        if(in.h >= 0 && in.h < 60) {
            r = c;
            g = x;
            b = 0;
        } else if(in.h >= 60 && in.h < 120) {
            r = x;
            g = c;
            b = 0;
        } else if(in.h >= 120 && in.h < 180) {
            r = 0;
            g = c;
            b = x;
        } else if(in.h >= 180 && in.h < 240) {
            r = 0;
            g = x;
            b = c;
        } else if(in.h >= 240 && in.h < 300) {
            r = x;
            g = 0;
            b = c;
        } else if(in.h >= 300 && in.h < 360) {
            r = c;
            g = 0;
            b = x;
        }

        rgb out = {(r + m) * 255, (g + m) * 255, (b + m) * 255};

        return out;
    }

    hsv rgb_to_hsv(rgb in) {
        
        rgb normalized = {in.r / 255.0, in.g / 255.0, in.b / 255.0};
        float cmax = std::max(normalized.r, std::max(normalized.g, normalized.b));
        float cmin = std::min(normalized.r, std::min(normalized.g, normalized.b));
        float diff = cmax - cmin;

        hsv out = {float(-1.0), float(-1.0)};

        if(!diff) {
            out.h = 0;
        } else if(cmax == normalized.r) {
            out.h = fmod((60 * ((normalized.g - normalized.b) / diff) + 360), 360);
        } else if(cmax == normalized.g) {
            out.h = fmod((60 * ((normalized.b - normalized.r) / diff) + 120), 360);
        } else if(cmax == normalized.b) {
            out.h = fmod((60 * ((normalized.r - normalized.g) / diff) + 240), 360);
        }

        if(cmax == 0) {
            out.s = 0;
        } else {
            out.s = (diff / cmax) * 100.0;
        }

        out.v = cmax * 100;

        return out;

    }

    //     r = int(r * 255)
    // g = int(g * 255)
    // b = int(b * 255)
    // return f"\033[38;2;{r};{g};{b}m"

    std::string rgb_to_ansi(rgb in) {
        int r = int(in.r);
        int g = int(in.g);
        int b = int(in.b);
        return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";}

}

// int main() {
//     color::rgb rgb;
//     rgb.r = 0;
//     rgb.g = 0;
//     rgb.b = 255;
//     color::hsv out = color::rgb_to_hsv(rgb);
//     std::cout << out.h << std::endl;
//     std::cout << out.s << std::endl;
//     std::cout << out.v << std::endl;
//     return 0;
// }