#ifndef STATE_H
#define STATE_H

#include <vector>
#include <random>
#include <chrono>
#include <nlohmann/json.hpp>

// The UsE oF nAmEsPaCeS iS cOnSiDeReD bAd PrAcTiCe
using json = nlohmann::json;
using namespace std;

class State {
    public:
        virtual ~State() {}
        virtual void generateFrames(vector<vector<float>>& grid) = 0;

    protected:
        const int ROWS = 64;
        const int COLS = 64;
        const float PI = 3.14159265358979323846;


        mt19937_64 rng;
        uniform_int_distribution<int> dist;

        // don't really understand initialization list vs assignment syntax, but this works
        State() : rng(chrono::steady_clock::now().time_since_epoch().count()), dist(0, 1) {}

        vector<vector<float>> copyGrid(const vector<vector<float>>& grid) {
            vector<vector<float>> copyGrid(grid.size(), vector<float>(grid[0].size()));

            for (size_t i = 0; i < grid.size(); i++) {
                for (size_t j = 0; j < grid[i].size(); j++) {
                    copyGrid[i][j] = grid[i][j];
                }
            }
            return copyGrid;
        }

        // helper function for dthe manhattan distance
        int distance(int x1, int y1, int x2, int y2) {
            return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        }
};

class Lorenz : public State {
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
        void generateFrames(vector<vector<float>>& grid) override;
        void filter(vector<vector<float>>& grid);
        float getX();
        float getY();
        float getZ();
};

class Boid {
    public:
        int x;
        int y;
        float vx;
        float vy;
        float ax;
        float ay;

        Boid(int x, int y, float vx, float vy, float ax, float ay) {
            this->x = x;
            this->y = y;
            this->vx = vx;
            this->vy = vy;
            this->ax = ax;
            this->ay = ay;
        }
        void init();
        void applyForce(float a_x, float a_y);
};

class Flock : public State {
    public:
        vector<Boid> flock;
        Flock();
        void generateFrames(vector<vector<float>>& grid) override;
        void separation(Boid& boid);
        void alignment(Boid& boid);
        void cohesion(Boid& boid);
};

class Wave : public State {
    public:
        void wave(vector<vector<float>>& grid);
        void generateFrames(vector<vector<float>>& grid) override;

};

class Conway : public State {
    public:
        void conway(vector<vector<float>>& grid);
        void generateFrames(vector<vector<float>>& grid) override;
};

#endif // STATE_H
