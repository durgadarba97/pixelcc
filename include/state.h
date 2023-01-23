// define header file for state.c
#ifndef STATE_H
#define STATE_H

class State {
    private :
        float grid[64][64];
        // int* gridpointer = &grid[0][0];

    public :
        State();
        void print();
        void initializeWeightedGrid();
};

#endif // STATE_H
