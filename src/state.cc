#include <string>
#include <iostream>
#include <random>
#include "color.h"
#include "state.h"
#include <cmath>

// std::string rgb_to_ansi(rgb in);
// hsv rgb_to_hsv(rgb in);

State::State() { 
    std::string s = "Hello from State";
    float grid[64][64];
    // int* gridpointer = &grid[0][0];

    initializeWeightedGrid();
    
}

void State::initializeWeightedGrid() {
    srand(unsigned(time(0)));

    for(int y = 0; y < 64; y++) {
        for(int x = 0; x < 64; x++) {
            grid[y][x] = (float)rand() / ((float)RAND_MAX+1.0);
        }
    }
}
/**
 * def print_map(grid: Grid):
    print("\033[0;0H", end="")

    for y in range(HEIGHT):
        for x in range(WIDTH):
            v = grid[y][x]

            h = v**2 * 0.2 + 0.2
            s = 0.5 + v**2 * 0.5
            v = v**3

            r, g, b = colorsys.hsv_to_rgb(h, s, v)

            print(rgb_to_ansi(r, g, b) + "██", end="")

        print()
*/

// string rgb_to_ansi(float r, float g, float b) {
//     int r = int(r * 255);
//     int g = int(g * 255);
//     int b = int(b * 255);

//     return "\033[38;2;" + r + ";" + g + ";" + b + "m";
// }



void State::print() {
    while(true) {
    // clear the screen
    std::cout << "\033[0;0H" << std::endl;

    // print the grid
    for(int y = 0; y < 64; y++) {
        for(int x = 0; x < 64; x++) {
            float v = grid[y][x];

            hsv huesatvalue;
            huesatvalue.h = powf(v, 2) * 0.2 + 0.2;
            huesatvalue.s = 0.5 + powf(v, 2) * 0.5;
            huesatvalue.v = powf(v, 3);

            rgb redgreenblue = hsv_to_rgb(huesatvalue);
            std::cout << rgb_to_ansi(redgreenblue) + "██";
        }
        
    }
    }
}

int main() {
    State s;
    s.print();
}