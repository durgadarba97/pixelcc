// #include <string>
// #include <iostream>
// #include <random>
// #include <cmath>
// #include <queue>
// #include <vector>
// #include <typeinfo>
// #include "color.h"
// #include "statemachine.h"
// #include "wave.h"
// #include "state.h"

// using namespace color;

// StateMachine::StateMachine() { 

//     // create a vector of possible states
//     std::vector <State> possibleStates;
//     Wave wave = Wave();
//     std::cout << "wave created" << std::endl;
//     possibleStates.push_back(wave);
    
//     std::cout << "wave pushed" << std::endl;
//     // create a queue of frames where each frame is a 2d array of 64x64 floats
//     std::vector<std::vector<float> > grid;

//     std::cout << "grid created" << std::endl;
//     std::queue<std::vector<std::vector<float> > > frameQueue = std::queue<std::vector<std::vector<float> > >();

//     std::cout << "frameQueue created" << std::endl;
//     // initializeWeightedGrid();
    
//     std::cout << "grid initialized" << std::endl;
// }


// StateMachine::~StateMachine() {
// }

// // There seems to be a segfault in this function. I'm not sure why.
// // I'm not sure if it's because of the way I'm passing the grid to the
// // wave class or if it's because of the way I'm initializing the grid.
// //  q: why am I getting a segfault in this function?
// //  a: I was passing the grid by reference, but I was also passing it to the
// void StateMachine::initializeWeightedGrid() {
//     // initialize the grid with random values
//     srand(unsigned(time(0)));

//     // 
//     for(int y = 0; y < 64; y++) {
//         for(int x = 0; x < 64; x++) {
//             this->grid[y][x] = (float)rand() / ((float)RAND_MAX+1.0);
//         }
//     }
// }

// void printarray(std::vector<std::vector<float> > & array) {
//     for(int y = 0; y < 64; y++) {
//         for(int x = 0; x < 64; x++) {
//             std::cout << array[y][x] << " ";
//         }
//         std::cout << std::endl;
//     }
// }

// void StateMachine::generateFrames() {
//     int t = 0;
//     while(t < 100)
//     {
//         if(frameQueue.size() >= 100) {
//             continue;
//         }  

//         // gebnerate a new frame from wave and append it to the queue
//         // possibleStates[0].generateFrames(grid);
//         frameQueue.push(grid);
//         t += 1;
//     }

//     for(int i = 0; i < 100; i++) {
//         std::cout << "frame " << i << std::endl;
        
//         // print the frame
//         print(&frameQueue.front());
//         frameQueue.pop();

//     }
    
// }

// void StateMachine::print(std::vector<std::vector<float> > * array) {

//     // clear the screen
//     std::cout << "\033[0;0H" << std::endl;

//     // print the grid
//     for(int y = 0; y < 64; y++) {
//         for(int x = 0; x < 64; x++) {
//             float v = (*array)[y][x];

//             // hsv huesatvalue;
//             // huesatvalue.h = powf(v, 2) * 0.2 + 0.2;
//             // huesatvalue.s = 0.5 + powf(v, 2) * 0.5;
//             // huesatvalue.v = powf(v, 3);

//             // huesatvalue.h = (powf(v, 1.0));
//             // huesatvalue.s = 0.1;
//             // huesatvalue.v = ((v + t * 0.1)*360);

//             // rgb redgreenblue = hsv_to_rgb(huesatvalue);

//                 //             r = 255 * pow(self.grid[i, j], 4 + (self.grid[i, j] * 0.5)) * math.cos(self.grid[i, j])
//                 // g = 255 * pow(self.grid[i, j], 3 + (self.grid[i, j] * 0.5)) * math.sin(self.grid[i, j])
//                 // b = 255 * pow(self.grid[i, j], 2 + (self.grid[i, j] * 0.5))
//             rgb redgreenblue = {
//                 .r = 255 * powf(v, 4 + (v * 0.5)) * cosf(v),
//                 .g = 255 * powf(v, 3 + (v * 0.5)) * sinf(v),
//                 .b = 255 * powf(v, 2 + (v * 0.5))
//             };

//             std::cout << rgb_to_ansi(redgreenblue) + "██";
//         }
        
//     }
// }


// // int main() {
// //         std::cout << "hello world" << std::endl;

// //     StateMachine s;
// //     // hsv h = {240, 1, 1};
// //     // std::cout << rgb_to_ansi(hsv_to_rgb(h)) << "██" << std::endl;
// //     s.generateFrames();
// //     // s.print();
// // }