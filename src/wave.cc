#include <iostream>
#include <cmath>
#include <random>
#include "state.h"

float randFloat(float min, float max) {
    return min + (rand() * (max-min) / RAND_MAX);
}

void Wave::wave(std::vector<std::vector<float> > &grid) {
    vector<vector<float>> lastGrid = copyGrid(grid);

    for(int i = 0; i < 64; i++) {
        for(int j = 0; j < 64; j++) {
            float lastValue = lastGrid[i][j];

            // grid[i][j] = lastValue * (0.96 + 0.02 * (float)rand() / (float)RAND_MAX);
            grid[i][j] = lastValue * (0.96 + 0.02 * (float)rand() / (float)RAND_MAX);

            // if(lastValue <= (0.18 + 0.04 * (float)rand() / (float)RAND_MAX))
            if(lastValue <= (0.15 + 0.04 * (float)rand() / (float)RAND_MAX)) {
                int n = 0;

                // in a moving window of 3x3,
                for(int u = -1; u < 2; u++) {
                    for(int v = -1; v < 2; v++) {
                        if(u == 0 && v == 0) {
                            continue;
                        }

                        //  get the value of the cell at the current position
                        int nj = abs((j + u) % 64);
                        int ni = abs((i + v) % 64);

                        float nLastValue = lastGrid[ni][nj];

                        // if the value is greater than 0.5, add it to the current cell
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

}

void Wave::generateFrames(std::vector<std::vector<float> > & grid) {
    wave(grid);
}