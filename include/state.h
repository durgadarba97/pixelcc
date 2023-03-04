#ifndef STATE_H
#define STATE_H

#include <vector>

class State {
    public:
        State();
        ~State();
        void generateFrames(std::vector<std::vector<float> > &frames);
};

#endif // STATE_H