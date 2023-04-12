#ifndef LORENZ_H
#define LORENZ_H

#include <vector>

class Lorenz {
    private:
        float x;
        float y;
        float z;

        float sigma;
        float rho;
        float beta;

    public:
        Lorenz();
        void lorenz();
        void generateFrames(std::vector<std::vector<float> > &grid);
        float getX();
        float getY();
        float getZ();
};
#endif