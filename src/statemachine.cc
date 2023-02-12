#include <string>
#include <iostream>
#include <random>
#include <cmath>
#include <queue>
#include <vector>

#include "color.h"
#include "statemachine.h"
#include "wave.h"
#include "state.h"

using namespace color;

StateMachine::StateMachine() { 
    float grid[64][64];
    Wave wave;

    vector <State*> possibleStates = {&wave};
    

    initializeWeightedGrid();
    
}

void StateMachine::initializeWeightedGrid() {
    srand(unsigned(time(0)));

    for(int y = 0; y < 64; y++) {
        for(int x = 0; x < 64; x++) {
            grid[y][x] = (float)rand() / ((float)RAND_MAX+1.0);
        }
    }
}

void printarray(float array[64][64]) {
    for(int y = 0; y < 64; y++) {
        for(int x = 0; x < 64; x++) {
            std::cout << array[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void StateMachine::generateFrames() {
    for(int i = 0; i < 1000; i++) {
        // printarray(grid);
        std::cout << "Hello" << std::endl;
        // print();
    }
}


void StateMachine::print(int t) {

    // clear the screen
    std::cout << "\033[0;0H" << std::endl;

    // print the grid
    for(int y = 0; y < 64; y++) {
        for(int x = 0; x < 64; x++) {
            float v = grid[y][x]; 

            // hsv huesatvalue;
            // huesatvalue.h = powf(v, 2) * 0.2 + 0.2;
            // huesatvalue.s = 0.5 + powf(v, 2) * 0.5;
            // huesatvalue.v = powf(v, 3);

            // huesatvalue.h = (powf(v, 1.0));
            // huesatvalue.s = 0.1;
            // huesatvalue.v = ((v + t * 0.1)*360);

            // rgb redgreenblue = hsv_to_rgb(huesatvalue);

                //             r = 255 * pow(self.grid[i, j], 4 + (self.grid[i, j] * 0.5)) * math.cos(self.grid[i, j])
                // g = 255 * pow(self.grid[i, j], 3 + (self.grid[i, j] * 0.5)) * math.sin(self.grid[i, j])
                // b = 255 * pow(self.grid[i, j], 2 + (self.grid[i, j] * 0.5))
            rgb redgreenblue = {
                .r = 255 * powf(v, 4 + (v * 0.5)) * cosf(v),
                .g = 255 * powf(v, 3 + (v * 0.5)) * sinf(v),
                .b = 255 * powf(v, 2 + (v * 0.5))
            };

            std::cout << rgb_to_ansi(redgreenblue) + "██";
        }
        
    }
}

// int main() {
//     StateMachine s;
//     // hsv h = {240, 1, 1};
//     // std::cout << rgb_to_ansi(hsv_to_rgb(h)) << "██" << std::endl;
//     s.generateFrames();
//     // s.print();
// }