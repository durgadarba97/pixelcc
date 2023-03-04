// header file for wave.cc

#ifndef WAVE_H
#define WAVE_H
#include "state.h"

// inherits from State
class Wave : public State {
    public:
        Wave();
        ~Wave();
        void wave(std::vector<std::vector<float> > &grid);
        void generateFrames(std::vector<std::vector<float> > &grid);
};


#endif // WAVE_H