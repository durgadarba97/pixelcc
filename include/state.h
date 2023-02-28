#ifndef STATE_H
#define STATE_H

// struct Display {
//     float grid[64][64];
// };

class State {
    public:
        State();
        void generateFrames(float grid[64][64]);
};

#endif // STATE_H