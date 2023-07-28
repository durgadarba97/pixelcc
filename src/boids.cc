#include <vector>
#include <random>
#include <iostream>

#include "state.h"

// basing off this documentation: https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html

using namespace std;

const float turnfactor = 0.2;
const float visualRange = 2;
const float protectedRange = 8;
const float centeringfactor = 0.0005;
const float avoidfactor = 0.05;
const float matchingfactor = 0.05;
const float maxspeed = 6;
const float minspeed = 3;
const float maxbias = 0.01;
const float bias_increment = 0.00004;
const float biasval = 0.001;


Boid::Boid(int x, int y, float vx, float vy) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
}

// int Boid::x() {
//     return this->x;
// }
// int Boid::y() {
//     return this->y;
// }
// int Boid::vx() {
//     return this->vx;
// }
// int Boid::vy() {
//     return this->vy;
// }

Flock::Flock() {
    vector<Boid> flock;

    // initialize flock
    for(int i = 0; i < 100; i++) {
        int x = rand() % 64;
        int y = rand() % 64;
        float vx = rand() % 10;
        float vy = rand() % 10;

        Boid b = Boid(x, y, vx, vy);
        flock.push_back(b);
    }
}

void Flock::generateFrames(vector<vector<float>>& grid) {
    // update the position of each boid

    // update the grid
    for (int i = 0; i < flock.size(); i++) {
        Boid b = flock[i];
        grid[b.x][b.y] = 1;
    }
}