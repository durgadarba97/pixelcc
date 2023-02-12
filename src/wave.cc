#include <iostream>
#include <cmath>
#include <random>
#include "wave.h"
#include "state.h"

class Wave : public State {
    public:


    float randFloat(float min, float max) {
        return min + (rand() * (max-min) / RAND_MAX);
    }

    // Copies the grid and returns a pointer to the copy 2d array
    float** copyGrid(float grid[64][64]) {
        float** copy = new float*[64];
        for(int i = 0; i < 64; i++) {
            copy[i] = new float[64];
            for(int j = 0; j < 64; j++) {
                copy[i][j] = grid[i][j];
            }
        }
        return copy;
    }

    void wave(float grid[64][64]) {
        float** lastGrid = copyGrid(grid);

        for(int i = 0; i < 64; i++) {
            for(int j = 0; j < 64; j++) {
                float lastValue = lastGrid[i][j];

                // grid[i][j] = lastValue * (0.96 + 0.02 * (float)rand() / (float)RAND_MAX);
                grid[i][j] = lastValue * (0.96 + 0.02 * (float)rand() / (float)RAND_MAX);
                if(lastValue <= (0.18 + 0.04 * (float)rand() / (float)RAND_MAX)) {
                    int n = 0;

                    for(int u = -1; u < 2; u++) {
                        for(int v = -1; v < 2; v++) {
                            if(u == 0 && v == 0) {
                                continue;
                            }

                            int nj = abs((j + u) % 64);
                            int ni = abs((i + v) % 64);

                            float nLastValue = lastGrid[ni][nj];

                            if(nLastValue >= (0.5 + 0.04 * (float)rand() / (float)RAND_MAX)) {
                                n += 1;
                                grid[i][j] += nLastValue * (0.8 + 0.4 * (float)rand() / (float)RAND_MAX);
                            }
                        }
                    }

                    if(n > 0) {
                        grid[i][j] *= (float)(1.0 / n);
                    }

                    grid[i][j] = fmin(grid[i][j], float(1.0));
                }
            }
        }


        for(int i = 0; i < 64; i++) {
            delete[] lastGrid[i];
        }

        delete[] lastGrid;
    };

    void generateFrames(float grid[64][64]) {
        wave(grid);
    }

};
