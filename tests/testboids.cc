#include <iostream>
#include <unistd.h>
#include <random>
#include <chrono>
#include <vector>

#include "../src/state.h"

using namespace std;

int main(int argc, char *argv[]){
    Flock flock = Flock();
    vector<vector<float>> grid(64, vector<float>(64));

    // while(true) {
        flock.generateFrames(grid);
        // for(int y = 0; y < 64; y++) {
        //     for(int x = 0; x < 64; x++) {
        //         // get the grid value and convert it to a color simialr to the state machine
        //         float value = grid[y][x];
                
        //         float r = 255 * value;
        //         float g = 255 * value;
        //         float b = 255 * value;
                
        //         // cout << r << " " << g << " " << b << endl;
        //     }
        // }
    // }
}

