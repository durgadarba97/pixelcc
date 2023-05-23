// #ifndef STATE_H
// #define STATE_H

// #include <vector>
// #include <random>
// #include <chrono>

// class State {
//     public:
//         State();
//         ~State();
//         void generateFrames(vector<vector<float> > &frames);

// };

// #endif // STATE_H

#ifndef STATE_H
#define STATE_H

#include <vector>
#include <random>
#include <chrono>

using namespace std;

class State {
    public:
        virtual ~State() {}
        virtual void generateFrames(vector<vector<float>>& grid) = 0;

    protected:
        const int ROWS = 64;
        const int COLS = 64;

        mt19937_64 rng;
        uniform_int_distribution<int> dist;

        // don't really understand initialization list vs assignment syntax, but this works
        State() : rng(chrono::steady_clock::now().time_since_epoch().count()), dist(0, 1) {}

        float** copyGrid(const vector<vector<float>>& grid) {
            float** copiedGrid = new float*[grid.size()];
            for (int i = 0; i < grid.size(); i++) {
                copiedGrid[i] = new float[grid[i].size()];
                for (int j = 0; j < grid[i].size(); j++) {
                    copiedGrid[i][j] = grid[i][j];
                }
            }
            return copiedGrid;
        }

        void deleteGrid(float** grid) {
            for (int i = 0; i < ROWS; i++) {
                delete[] grid[i];
            }
            delete[] grid;
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
        void lorenz();
        void generateFrames(vector<vector<float>>& grid) override;
        void filter(vector<vector<float>>& grid);
        float getX();
        float getY();
        float getZ();
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
