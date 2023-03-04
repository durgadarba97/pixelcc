// define header file for state.c
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <queue>
#include <vector>
#include "state.h"

class StateMachine {
    private :
        std::vector<std::vector<float> > grid;
        std::queue<std::vector<std::vector<float> > > frameQueue;
        std::vector<State> possibleStates;

    public :
        StateMachine();
        ~StateMachine();
        void print(std::vector<std::vector<float> > * array);
        void initializeWeightedGrid();
        void generateFrames();

};

#endif // STATEMACHINE_H
