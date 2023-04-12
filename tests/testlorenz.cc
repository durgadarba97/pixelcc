#include <iostream>
#include <cmath>
#include <signal.h>

#include "unistd.h"
#include "led-matrix.h"
#include "../src/lorenz.h"

using namespace rgb_matrix;
using namespace std;

int lorenz(Canvas *canvas) {
    Lorenz lorenz;
    // cout << lorenz.getX() << " " << lorenz.getY() << " " << lorenz.getZ() << endl;

    vector<vector<float> > grid(64, vector<float>(64));

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            grid[i][j] = 0;
        }
    }

    while(true) {
        // cout << lorenz.getX() << " " << lorenz.getY() << " " << lorenz.getZ() << endl;
        lorenz.generateFrames(grid);

        // print the grid
        for(int x = 0; x < 64; x++) {
            for(int y = 0; y < 64; y++) {
                // get the grid value and convert it to a color simialr to the state machine
                float value = grid[x][y];

                float r = 255 * powf(value, 4 + (value * 0.5)) * cosf(value);
                float g = 255 * powf(value, 3 + (value * 0.5)) * sinf(value);
                float b = 255 * powf(value, 2 + (value * 0.5));
                
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

    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL)
    return 1;

    lorenz(canvas);    // Using the canvas.
    return 0;

}


