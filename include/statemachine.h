// define header file for state.c
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <queue>
#include <vector>
#include "state.h"

class StateMachine {
    private :
        float grid[64][64];
        std::queue<float[64][64]> frames;
        std::vector <State> possibleStates;

    public :
        StateMachine();
        void print();
        void initializeWeightedGrid();
        void generateFrames();
        std::queue<float[64][64]> getFrames();

};

#endif // STATEMACHINE_H
