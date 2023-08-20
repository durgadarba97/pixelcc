# pixelcc

## Description ::
A (not so) simple C++ library for controlling the 64 x 64 RGB LED matrix from Adafruit.
https://www.adafruit.com/product/3649

## Dependencies ::
RPI RGB Matrix Library : https://github.com/hzeller/rpi-rgb-led-matrix
JSON LIBRARY : https://github.com/nlohmann/json

## Notes ::
The library was originally hacked together in Python (https://github.com/durgadarba97/pixel)
but it had poor performnace. 

spotify.cc - usign the json library to get album covers of the currently playing song on spotify
lorenz.cc - the wave animation + "bug" (lorenz attractor) 
wave.cc - wave animation inspired by u/knifa 

Insipired by the rust project : https://www.reddit.com/r/raspberry_pi/comments/hxlk9c/been_working_on_this_led_matrix_display_project/

## TO DO ::
    - Queue 
        - Add a queue to string together animations.
    
    - Animations
        - Color class to transition along HSV : 
            https://www.masterclass.com/articles/how-to-use-hsv-color-model-in-photography
            https://web.cs.uni-paderborn.de/cgvb/colormaster/web/color-systems/hsv.html
        - Conways Game of Life
        - Snake
        - Maze Generators
        
    - Other
        - CLEAN UP MAKEFILE 
        - AND TEST FILE!
