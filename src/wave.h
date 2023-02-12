// header file for wave.cc

#ifndef WAVE_H
#define WAVE_H
#include "state.h"

// inherits from State
class Wave : public State {
    public:
        Wave();
        void wave(float grid[64][64]);
        void generateFrames(float grid[64][64]);
};


#endif // WAVE_H