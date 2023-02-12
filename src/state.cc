#include <iostream>

#include "state.h"

class State {
    public:
        State() {
            std::cout << "Base Class" << std::endl;
        };

        void generateFrames(float grid[64][64]) {
            std::cout << "Base Class" << std::endl;
        };
};