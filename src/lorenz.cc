#include <vector>
#include <random>
#include <chrono>
#include <iostream>

#include "lorenz.h"

using namespace std;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_real_distribution<float> dist(0, 1);

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


    cout << x << " " << y << " " << z << endl;

}

void Lorenz::generateFrames(std::vector<std::vector<float> > &grid) {
    // cout << x << " " << y << " " << z << endl;
    // calculate the next values
    float dx = sigma * (y - x);
    float dy = x * (rho - z) - y;
    float dz = x * y - beta * z;

    // cout << x << " " << y << " " << z << endl;

    // update the values
    this->x += dx * 0.01;
    this->y += dy * 0.01;
    this->z += dz * 0.01;

    // convert the values to a grid
    // int x1 = (int) (x * 10 + 32);
    // int y1 = (int) (y * 10 + 32);
    // int z1 = (int) (z * 10 + 32);

    // std::cout << x1 << " " << y1 << " " << z1 << std::endl;

    // set the grid value if indices are within bounds
    if (x >= 0 && x < 64 && y >= 0 && y < 64) {
        grid[x][y] = 1;
    }
}

int Lorenz::getX() {
    return x;
}

int Lorenz::getY() {
    return y;
}

int Lorenz::getZ() {
    return z;
}
