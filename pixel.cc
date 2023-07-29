#include "led-matrix.h"
#include "./src/spotify.h"
#include "./src/state.h"
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <exception>
#include <Magick++.h>
#include <magick/image.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>


using ImageVector = std::vector<Magick::Image>;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using namespace std;

std::mutex canvas_mutex;
std::atomic<bool> spotify_playing(false);


volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

// From the example in the matrix library:
static ImageVector LoadImageAndScaleImage(const char *filename, int target_width, int target_height) {
  ImageVector result;

  ImageVector frames;
  try {
    readImages(&frames, filename);
  } catch (std::exception &e) {
    if (e.what())
      fprintf(stderr, "%s\n", e.what());
    return result;
  }

  if (frames.empty()) {
    fprintf(stderr, "No image found.");
    return result;
  }

  // Animated images have partial frames that need to be put together
  if (frames.size() > 1) {
    Magick::coalesceImages(&result, frames.begin(), frames.end());
  } else {
    result.push_back(frames[0]); // just a single still image.
  }

  for (Magick::Image &image : result) {
    image.scale(Magick::Geometry(target_width, target_height));
  }

  return result;
}
void CopyImageToCanvas(const Magick::Image &image, Canvas *canvas) {
  const int offset_x = 0, offset_y = 0;  // If you want to move the image.

  // Copy all the pixels to the canvas.
  for (size_t y = 0; y < 64; ++y) {
    for (size_t x = 0; x < 64; ++x) {
      const Magick::Color &c = image.pixelColor(x, y);
      if (c.alphaQuantum() < 256) {
        canvas->SetPixel(x + offset_x, y + offset_y, ScaleQuantumToChar(c.redQuantum()), ScaleQuantumToChar(c.greenQuantum()), ScaleQuantumToChar(c.blueQuantum()));
      }
    }
  }
}

int initLorenz(Lorenz &lorenz, vector<vector<float> > &grid) {
  int t = 0;
  while(t < 500) {
    lorenz.lorenz();
    t++;

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {

            int x1 = lorenz.getX() + 32;
            int y1 = lorenz.getY() + 32;
            int z1 = lorenz.getZ();
            
            if (x1 >= 0 && x1 < 64 && z1 >= 0 && z1 < 64) {
                grid[z1][x1] = 1.0f;
            }
        }
    }
  }
  return 1;
}

static void spotifyThread(Canvas *canvas) {
  Spotify spotify;

  canvas->Clear();
  bool updated = false;

  while(!interrupt_received) {

    try {
        updated = spotify.update();
        spotify_playing = spotify.isPlaying();
    } catch (const json::type_error& e){
      cerr << "Caught type_error: " << e.what() << endl;
      sleep(5);
    }

    
    if(spotify_playing) {
      std::lock_guard<std::mutex> guard(canvas_mutex);
      // load the image
      ImageVector image = LoadImageAndScaleImage("./tmp/spotify.png", 64, 64);    
      canvas->Clear();
      CopyImageToCanvas(image[0], canvas);
      sleep(4);
    }
    sleep(10);
  }
}

// main loop for drawing
int render(Canvas *canvas) {
  Lorenz lorenz;
  vector<vector<float> > grid(64, vector<float>(64));

  initLorenz(lorenz, grid);

  thread spotify_thread(spotifyThread, canvas);
  sleep(3);

  while(!interrupt_received) {

    if(spotify_playing) {
      usleep(10000);
      continue;
    }

    // draw the lorenz attractor
    lorenz.generateFrames(grid);

    for(int x = 0; x < 64; x++) {     
      for(int y = 0; y < 64; y++) {
        // get the grid value and convert it to a color simialr to the state machine
        float value = grid[x][y];

        float r = 255 * powf(value, 4 + (value * 0.5)) * cosf(value);
        float g = 255 * powf(value, 3 + (value * 0.5)) * sinf(value);
        float b = 255 * powf(value, 2 + (value * 0.5));
        
        canvas->SetPixel(x, y, r, g, b);
      }
    }
    usleep(33333);
  }
  canvas->Clear();
  spotify_thread.join();
  return 1;
}



int main(int argc, char *argv[]) {
  Magick::InitializeMagick(*argv);
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "adafruit-hat-pwm";  // or e.g. "adafruit-hat"
  defaults.rows = 64;
  defaults.cols = 64;
  defaults.brightness = 95;

  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;

  // It is always good to set up a signal handler to cleanly exit when we
  // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
  // for that.
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  render(canvas);    // Using the canvas.

  delete canvas;

  return 0;
}

