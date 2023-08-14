#include <vector>
#include <random>
#include <iostream>

#include "state.h"

// basing off this documentation: https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html

using namespace std;

const float visualRange = 4;
const float protectedRange = 2;
const float avoidfactor = 5;
const float maxspeed = 2;
const float minspeed = 1.5;

void Boid::applyForce(float a_x, float a_y) {
    this->ax += a_x;
    this->ay += a_y;
}


Flock::Flock() {

    // initialize flock
    for(int i = 0; i < 50; i++) {
        int x = int(ROWS / 2);
        int y = int(COLS / 2);
        
        float angle = 2*PI * (rand()/RAND_MAX);
        // non zero velocity
        float vx = (rand() / RAND_MAX);
        float vy = (rand() / RAND_MAX);
        Boid b = Boid(x, y, vx, vy, 0, 0);
        flock.push_back(b);
    }
    
}

void Flock::alignment(Boid& boid) {

}


void Flock::cohesion(Boid& boid) {

}

void Flock::separation(Boid& boid) {

}


void Flock::generateFrames(vector<vector<float>>& grid) {
    // update the position of each boid
    for(int i = 0; i < flock.size(); i++) {
        alignment(flock[i]);
        cohesion(flock[i]);
        separation(flock[i]);
    }

    // clear the grid. This is a bit different from how the other classes work.
    for(int i = 0; i < 64; i++) {
        for(int j = 0; j < 64; j++) {
            grid[i][j] = 0;
        }
    }

    // update the grid
    for(int i = 0; i < flock.size(); i++) {        
        Boid& boid = flock[i];
        // Update the boid's position based on its velocity
        boid.x += boid.vx;
        boid.y += boid.vy;

        // cout << boid.x << endl;
        // cout << boid.vx << endl;

        // Wrap around the grid if the boid goes out of bounds
        boid.x = (boid.x + 64) % 64;
        boid.y = (boid.y + 64) % 64;

        grid[boid.x][boid.y] = 1;
    }

}