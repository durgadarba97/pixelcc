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
        for(int y = 0; y < 64; y++) {
            for(int x = 0; x < 64; x++) {
                // print grid where x is the first index and y is the second index and if z is greater than 0 then print a 1
                float value = grid[y][x];
                
                float r = 255 * value;
                float g = 255 * value;
                float b = 255 * value;
                
                canvas->SetPixel(x, y, r, g, b);
            }
        }
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


// int main(int argc, char *argv[]) {
//     Lorenz lorenz;
//     // cout << lorenz.getX() << " " << lorenz.getY() << " " << lorenz.getZ() << endl;

//     vector<vector<float> > grid(64, vector<float>(64));

//     for (int i = 0; i < 64; i++) {
//         for (int j = 0; j < 64; j++) {
//             grid[i][j] = 0;
//         }
//     }

//     while(true) {
//         // cout << lorenz.getX() << " " << lorenz.getY() << " " << lorenz.getZ() << endl;
//         lorenz.generateFrames(grid);

//         // print the grid
//         for(int y = 0; y < 64; y++) {
//             for(int x = 0; x < 64; x++) {
//                 // print grid where x is the first index and y is the second index and if z is greater than 0 then print a 1
//                 float value = grid[y][x];
                
//                 float r = 255 * value;
//                 float g = 255 * value;
//                 float b = 255 * value;
                
//                 cout << r << " " << g << " " << b << endl;
//             }
//         }
//     }
//     return 0;
// }


int main(int argc, char *argv[]) {
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
        for(int y = 0; y < 64; y++) {
            for(int x = 0; x < 64; x++) {
                // print grid where x is the first index and y is the second index and if z is greater than 0 then print a 1
                float value = grid[y][x];
                
                float r = 255 * value;
                float g = 255 * value;
                float b = 255 * value;
                
                cout << r << " " << g << " " << b << endl;
            }
        }
    }
    return 0;
}