#include <iostream>

#include "state.h"


State::State() {
    std::cout << "Base Class" << std::endl;
};

void State::generateFrames(float grid[64][64]) {
    std::cout << "Base Class" << std::endl;
};
