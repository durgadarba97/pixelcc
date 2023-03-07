# add_subdirectory(spotify/vendor/spotify-json)
# target_link_libraries(spotify spotify-json)

# # Add the executable
# add_executable(testspotify testspotify.cpp)

# link the src library to the executable
# link the wave library to the executable

cmake_minimum_required(VERSION 3.10)

project(pixelcc)

add_executable(test test.cc)

