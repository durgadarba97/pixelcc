# pixelcc

## Description ::
A (not so) simple C++ library for controlling the 64 x 64 RGB LED matrix from Adafruit.
https://www.adafruit.com/product/3649

## Examples::
I got the Spotify integration to work! When I play a song, on my phone, laptop etc. it automatically gets the album cover, 
downsamples the color to a 64x64 grid and displays it:

![thumbnail](https://user-images.githubusercontent.com/11541314/219512338-f2eae18e-fae3-4bb1-a6c4-9d0ebdda4a40.MOV)

https://user-images.githubusercontent.com/11541314/219512382-110da059-07dc-4b6e-910b-92dd8b418d76.MOV

https://user-images.githubusercontent.com/11541314/219512364-230d8d39-c421-43f3-a7f9-d17bfe2dbbf7.MOV

https://user-images.githubusercontent.com/11541314/219514155-16f2710b-5e49-4ed7-a33e-ef58dd4e6e57.mov

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

