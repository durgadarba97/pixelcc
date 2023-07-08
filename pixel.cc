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


// include everything in utils directory

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

using ImageVector = std::vector<Magick::Image>;

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
  for (size_t y = 0; y < image.rows(); ++y) {
    for (size_t x = 0; x < image.columns(); ++x) {
      const Magick::Color &c = image.pixelColor(x, y);
      if (c.alphaQuantum() < 256) {
        canvas->SetPixel(x + offset_x, y + offset_y,
                         ScaleQuantumToChar(c.redQuantum()),
                         ScaleQuantumToChar(c.greenQuantum()),
                         ScaleQuantumToChar(c.blueQuantum()));
      }
    }
  }
}

int initLorenz(Lorenz *lorenz, vector<vector<float> > *grid) {
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
                grid[z1][x1] = 1;
            }
        }
    }
  }
  return 1;
}

// main loop for drawing
int render() {
  Spotify spotify;
  Lorenz lorenz;
  vector<vector<float> > grid(64, vector<float>(64));

  initLorenz(&lorenz, &grid);

  while(!interrupt_received) {
    int updated = spotify.update();
    
  if(spotify.isPlaying() && updated) {
    // load the image
    ImageVector image = LoadImageAndScaleImage("./tmp/spotify.png", 64, 64);
    CopyImageToCanvas(image[0], canvas);

    sleep(4);
    continue;
  }

  // draw the lorenz attractor
  lorenz.lorenz();
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      int x1 = lorenz.getX() + 32;
      intå y1 = lorenz.getY() + 32;
      int z1 = lorenz.getZ();
      
      if (x1 >= 0 && x1 < 64 && z1 >= 0 && z1 < 64) {
          grid[z1][x1] = 1;
      }

      canvas->SetPixel(x, y, r, g, b);
    }
  }

  usleep(40000);
  }
}


int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "adafruit-hat-pwm";  // or e.g. "adafruit-hat"
  defaults.rows = 64;
  defaults.cols = 64;
  defaults.brightness = 80;

  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;

  // It is always good to set up a signal handler to cleanly exit when we
  // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
  // for that.
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  DrawOnCanvas(canvas);    // Using the canvas.

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;

  return 0;
}

