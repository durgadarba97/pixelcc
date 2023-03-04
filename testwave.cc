

// This is the test file for the wave class. It tests the wave class
// and the wave state class.
#include <iostream>
#include <vector>
#include "src/wave.h"
#include "led-matrix.h"

using namespace std;
using namespace rgb_matrix;

int wave( Canvas *canvas) {
    Wave wave = Wave();

    initializeCanvas();
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
        vector<vector<float> > frame = wave.getNextFrame();

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
                canvas->SetPixel(x, y, 255, 255, 255);
            }
        }
        usleep(1000000);
    }
    cout << "wave created" << endl;
}

int main() {
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
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    wave(canvas);    // Using the canvas.
    return 0;

}
