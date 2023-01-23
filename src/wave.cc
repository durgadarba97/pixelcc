#include <iostream>

// state will pass pointer to grid. the grid will be a 2d array of ints
//  translated from python code https://github.com/durgadarba97/pixel/blob/main/pixel/utils/wave.py
void wave(int* grid) {

    for(int i = 0; i < 64; i++) {
        for(int j = 0; j < 64; j++) {
            std::cout << grid[i*64 + j];
        }
        std::cout << std::endl;
    }

};