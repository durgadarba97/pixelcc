#include <iostream>
#include <unistd.h>
#include <random>
#include <chrono>
#include "led-matrix.h"


#include "../src/conway.h"

using namespace rgb_matrix;
using namespace std;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> dist(0, 1);

Conway::Conway() {}

void initGrid(vector<vector<float> > &grid) {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            grid[i][j] = dist(rng);
        }
    }
}

int conway(Canvas *canvas) {
    Conway conway;

    vector<vector<float> > grid(64, vector<float>(64));

    initGrid(grid);
    
    
    while(true) {
        conway.generateFrames(grid);

        // print the grid
        for(int y = 0; y < 64; y++) {
            for(int x = 0; x < 64; x++) {
                // get the grid value and convert it to a color simialr to the state machine
                float value = grid[y][x];

                // q : will !value be faster than value == 0 ?
                
                float r = 255 * value;
                float g = 255 * value;
                float b = 255 * value;
                
                canvas->SetPixel(x, y, r, g, b);
            }
        }

        // 30 frames per second
        usleep(33333);
    }
}

int main(int argc, char *argv[]) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm";  // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.brightness = 75;

    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL)
    return 1;

    conway(canvas);    // Using the canvas.
    return 0;

}