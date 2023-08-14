#include <iostream>
#include <unistd.h>
#include <random>
#include <chrono>
#include <vector>
#include "led-matrix.h"
#include "../src/state.h"

using namespace rgb_matrix;
using namespace std;

int boid(Canvas *canvas) {
    Flock flock = Flock();
    vector<vector<float>> grid(64, vector<float>(64));

    while(true) {
        
        flock.generateFrames(grid);
        for(int x = 0; x < 64; x ++) {
            for(int y = 0; y < 64; y++) {
                // get the grid value and convert it to a color simialr to the state machine
                float value = grid[x][y];
                // cout << value << endl; 
                
                float r = 255 * value;
                float g = 255 * value;
                float b = 255 * value;
                
                canvas->SetPixel(x, y, r, g, b);
            }
        }

        usleep(33333);
    }
}

int main(int argc, char *argv[]){
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm";  // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;

    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL)
    return 1;

    boid(canvas);    // Using the canvas.
    return 0;
}
