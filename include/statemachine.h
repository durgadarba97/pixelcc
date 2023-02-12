// define header file for state.c
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

class StateMachine {
    private :
        float grid[64][64];

    public :
        StateMachine();
        void print(int t);
        void initializeWeightedGrid();
        void generateFrames();
};

#endif // STATEMACHINE_H
