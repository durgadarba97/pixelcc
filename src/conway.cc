#include <iostream>
#include <random>
#include <chrono>
#include "conway.h"

// Grid dimensions
const int GRID_SIZE = 64;

using namespace std;

// Print grid to console
void printGrid(vector<vector<float> > &grid) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            std::cout << (grid[i][j] ? "X" : ".");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Get number of live neighbors for a cell
int getNumLiveNeighbors(vector<vector<float> > &grid, int x, int y) {
    int numLiveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int row = (x + i + 64) % 64;
            int col = (y + j + 64) % 64;
            numLiveNeighbors += grid[row][col];
        }
    }
    return numLiveNeighbors;
}

// Update grid based on Game of Life rules
void updateGrid(vector<vector<float> > &grid) {
    vector<vector<float> > newGrid(64, vector<float>(64));

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            int numLiveNeighbors = getNumLiveNeighbors(grid, i, j);
            if (grid[i][j]) {
                if (numLiveNeighbors < 2 || numLiveNeighbors > 3) {
                    newGrid[i][j] = 0;
                } else {
                    newGrid[i][j] = 1;
                }
            } else {
                if (numLiveNeighbors == 3) {
                    newGrid[i][j] = 1;
                } else {
                    newGrid[i][j] = 0;
                }
            }
        }
    }
    // Copy new grid over old grid
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

void Conway::generateFrames(vector<vector<float> > &grid) {
    updateGrid(grid);
}

