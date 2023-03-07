# pixelcc

## Description ::
A (not so) simple C++ library for controlling the 64 x 64 RGB LED matrix from Adafruit.
https://www.adafruit.com/product/3649

## Dependencies ::
RPI RGB Matrix Library : https://github.com/hzeller/rpi-rgb-led-matrix
Spotify JSON LIBRARY : https://github.com/spotify/spotify-json
    - still to be determined. not very out of the box friendly.

## Notes ::
The library was originally hacked together in Python (https://github.com/durgadarba97/pixel)
but the performace with the Python library is not good, so I'm rewriting it in C++ so that it can be used in a more real-time environment. It also allows for more control over the LED matrix and animations in the future.

## TO DO ::
    - Queue
        - Sigfault error when trying to add to queue

    - Spotify 
        - learning how to use the spotify-json library
        - writing the CMakelists.txt file for the library
    
    - Animations
        - Conways Game of Life
        - Snake
        - Maze Generators
        - Transitioning between animations
        
