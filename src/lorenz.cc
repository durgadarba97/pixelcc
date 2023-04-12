#include <vector>
#include <random>
#include <chrono>
#include <iostream>

#include "lorenz.h"

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<float> dist(0, 1);

// a program to generate a Lorenz attractor
Lorenz::Lorenz() {
    // set the initial values
    x = 1.0;
    y = 1.0;
    z = 0.0;  

    // set the constants
    sigma = 10.0;
    rho = 28.0;
    beta = 8.0 / 3.0;

    vector<vector<float> > weight_grid(64, vector<float>(64));



    // cout << x << " " << y << " " << z << endl;
}

void Lorenz::lorenz() {
    // cout << x << " " << y << " " << z << endl;
    // calculate the next values
    float dx = sigma * (y - x);
    float dy = x * (rho - z) - y;
    float dz = x * y - beta * z;

    // cout << x << " " << y << " " << z << endl;

    // update the values
    this->x += dx * 0.015;
    this->y += dy * 0.015;
    this->z += dz * 0.015;

    // center this around the middle of the grid
    // int x1 = x + 32;
    // int y1 = y + 32;
    // int z1 = z + 32;

    // cout << x1 << " " << y1 << " " << z1 << endl;

    // set the grid value if indices are within bounds
    // if (x1 >= 0 && x1 < 64 && y1 >= 0 && y1 < 64) {
    //     grid[x1][z1] = 1;
    // }
}

// Copies the grid and returns a pointer to the copy 2d array
float** copy(vector<vector<float> > &grid) {
    float** copy = new float*[64];
    for(int i = 0; i < 64; i++) {
        copy[i] = new float[64];
        for(int j = 0; j < 64; j++) {
            copy[i][j] = grid[i][j];
        }
    }
    return copy;
}

void filter(vector<vector<float> > &grid) {
    float** lastGrid = copy(grid);

    for(int i = 0; i < 64; i++) {
        for(int j = 0; j < 64; j++) {
            float lastValue = lastGrid[i][j];

            // grid[i][j] = lastValue * (0.96 + 0.02 * (float)rand() / (float)RAND_MAX);
            grid[i][j] = lastValue * (0.96 + 0.02 * (float)rand() / (float)RAND_MAX);
            if(lastValue <= (0.18 + 0.04 * (float)rand() / (float)RAND_MAX)) {
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

    for(int i = 0; i < 64; i++) {
        delete[] lastGrid[i];
    }

}

void Lorenz::generateFrames(vector<vector<float> > &grid) {

    lorenz();

    // cout << x << " " << y << " " << z << endl;

    // center this around the middle of the grid
    int x1 = x + 32;
    int y1 = y + 32;
    int z1 = z;

    // cout << x1 << " " << y1 << " " << z1 << endl;

    // set the grid value if indices are within bounds
    if (x1 >= 0 && x1 < 64 && z1 >= 0 && z1 < 64) {
        grid[z1][x1] = 1;
    }

    // cout << x << " " << y << " " << z << endl;

    // filter the grid
    filter(grid);

}
