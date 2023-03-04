

// This is the test file for the wave class. It tests the wave class
// and the wave state class.
#include <iostream>
#include <vector>
#include <unistd.h>
#include <cmath>
#include <signal.h>

#include "src/wave.h"
#include "led-matrix.h"


using namespace std;
using namespace rgb_matrix;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}


int wave( Canvas *canvas) {
    Wave wave = Wave();

    vector <vector<float> > grid;


    srand(unsigned(time(0)));
    for(int y = 0; y < 64; y++) {
        vector<float> row;
        for(int x = 0; x < 64; x++) {
            row.push_back((float)rand() / ((float)RAND_MAX+1.0));
        }
        grid.push_back(row);
    }
    
    wave.generateFrames(grid);

    // print the grid
    // for(int y = 0; y < 64; y++) {
    //     for(int x = 0; x < 64; x++) {
    //         cout << grid[y][x] << " ";
    //     }
    //     cout << endl;
    // }
    


    while(true) {

        // get the next frame
        wave.generateFrames(grid);

        // print the frame
        // for(int y = 0; y < 64; y++) {
        //     for(int x = 0; x < 64; x++) {
        //         cout << frame[y][x] << " ";
        //     }
        //     cout << endl;
        // }

        // draw the frame
        for(int y = 0; y < 64; y++) {
            for(int x = 0; x < 64; x++) {
                // get the grid value and convert it to a color simialr to the state machine
                float value = grid[y][x];
                float r = 255 * powf(value, 4 + (value * 0.5)) * cosf(value);
                float g = 255 * powf(value, 3 + (value * 0.5)) * sinf(value);
                float b = 255 * powf(value, 2 + (value * 0.5));
                
                canvas->SetPixel(x, y, r, g, b);
            }
        }
        usleep(1000000);
    }
    cout << "wave created" << endl;
}

int main(int argc, char *argv[]) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm";  // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;

    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL)
    return 1;

    // It is always good to set up a signal handler to cleanly exit when we
    // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
    // for that.
    // q: why cant the compiler find this function?
    // a: because it is a static function in the pixel.cc file
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    wave(canvas);    // Using the canvas.
    return 0;

}
