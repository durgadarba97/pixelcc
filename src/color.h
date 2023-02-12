// header file for color.cc
#ifndef COLOR_H
#define COLOR_H
#include <string>

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

    rgb hsv_to_rgb(hsv in);

    hsv rgb_to_hsv(rgb in);

    std::string rgb_to_ansi(rgb in);
}
#endif // COLOR_H