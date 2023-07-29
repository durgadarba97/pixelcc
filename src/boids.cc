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



Boid::Boid(int x, int y, float vx, float vy, float ax, float ay) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->ax = ax;
    this->ay = ay;
}


Flock::Flock() {

    // initialize flock
    for(int i = 0; i < 50; i++) {
        int x = rand() % 64;
        int y = rand() % 64;
        // non zero velocity
        float vx = (rand() % 2)+1;
        float vy = (rand() % 2)+1;
        Boid b = Boid(x, y, vx, vy, 0, 0);
        flock.push_back(b);
    }
    
}

void Flock::alignment(Boid& boid) {
    float sum_vx = 0.0;
    float sum_vy = 0.0;
    int count = 0;

    for (int i = 0; i < flock.size(); i++) {
        Boid& other = flock[i];

        if (&other == &boid) {
            continue;  // Skip the current boid itself
        }

        float dist = distance(boid.x, boid.y, other.x, other.y);

        if (dist <= visualRange) {
            sum_vx += other.vx;
            sum_vy += other.vy;

            count++;
        }
    }

    if (count > 0) {
        // Calculate the average velocity of neighboring boids
        float avg_vx = sum_vx / count;
        float avg_vy = sum_vy / count;

        // Calculate the desired change in velocity
        float desired_vx = avg_vx - boid.vx;
        float desired_vy = avg_vy - boid.vy;

        // Calculate the acceleration based on desired change in velocity and time (let's assume time is 1)
        boid.ax = desired_vx;
        boid.ay = desired_vy;

        // Update the boid's velocity based on acceleration
        boid.vx += boid.ax;
        boid.vy += boid.ay;

        // Limit the velocity to maxspeed
        float speed = sqrt(boid.vx * boid.vx + boid.vy * boid.vy);
        if (speed > maxspeed) {
            boid.vx = (boid.vx / speed) * maxspeed;
            boid.vy = (boid.vy / speed) * maxspeed;
        }
    }
}


void Flock::cohesion(Boid& boid) {
    float sum_x = 0.0;
    float sum_y = 0.0;
    int count = 0;

    for (int i = 0; i < flock.size(); i++) {
        Boid& other = flock[i];

        if (&other == &boid) {
            continue;  // Skip the current boid itself
        }

        float dist = distance(boid.x, boid.y, other.x, other.y);

        if (dist <= visualRange) {
            sum_x += other.x;
            sum_y += other.y;
            count += 1;
        }
    }

    if (count > 0) {
        // Calculate the average position of neighboring boids
        float avg_x = sum_x / count;
        float avg_y = sum_y / count;

        // Calculate the desired change in velocity
        float desired_vx = avg_x - boid.x;
        float desired_vy = avg_y - boid.y;

        // Calculate the acceleration based on desired change in velocity and time (let's assume time is 1)
        boid.ax = desired_vx;
        boid.ay = desired_vy;

        // Update the boid's velocity based on acceleration
        boid.vx += boid.ax;
        boid.vy += boid.ay;

        // Limit the velocity to maxspeed
        float speed = sqrt(boid.vx * boid.vx + boid.vy * boid.vy);
        if (speed > maxspeed) {
            boid.vx = (boid.vx / speed) * maxspeed;
            boid.vy = (boid.vy / speed) * maxspeed;
        }
    }
}

void Flock::separation(Boid& boid) {
    float avoid_vx = 0.0;
    float avoid_vy = 0.0;

    for (int i = 0; i < flock.size(); i++) {
        Boid& other = flock[i];

        if (&other == &boid) {
            continue;  // Skip the current boid itself
        }

        float dist = distance(boid.x, boid.y, other.x, other.y);

        if (dist <= protectedRange) {
            float diff_x = boid.x - other.x;
            float diff_y = boid.y - other.y;

            // Normalize the separation vector
            float len = sqrt(diff_x * diff_x + diff_y * diff_y);
            if (len > 0.0) {
                diff_x /= len;
                diff_y /= len;
            }

            // Accumulate the separation force
            avoid_vx += diff_x;
            avoid_vy += diff_y;
        }
    }

    // Calculate the desired change in velocity
    float desired_vx = avoid_vx * avoidfactor;
    float desired_vy = avoid_vy * avoidfactor;

    // Calculate the acceleration based on desired change in velocity and time (let's assume time is 1)
    boid.ax = desired_vx;
    boid.ay = desired_vy;

    // Update the boid's velocity based on acceleration
    boid.vx += boid.ax;
    boid.vy += boid.ay;

    // Limit the velocity to maxspeed
    float speed = sqrt(boid.vx * boid.vx + boid.vy * boid.vy);
    if (speed > maxspeed) {
        boid.vx = (boid.vx / speed) * maxspeed;
        boid.vy = (boid.vy / speed) * maxspeed;
    }
}


void Flock::generateFrames(vector<vector<float>>& grid) {
    // update the position of each boid
    for(int i = 0; i < flock.size(); i++) {
        alignment(flock[i]);
        cohesion(flock[i]);
        separation(flock[i]);
        // speedLimit(flock[i]);
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