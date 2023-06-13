#include <vector>
#include <iostream>
#include <unistd.h>
#include <Magick++.h>
#include <led-matrix.h>

#include "../src/spotify.h"

using namespace std;
using rgb_matrix::Canvas;
using rgb_matrix::RGBMatrix;
using rgb_matrix::FrameCanvas;
using ImageVector = std::vector<Magick::Image>;

// Given the filename, load the image and scale it to the size of the matrix.
static ImageVector LoadImageAndScaleImage(const char *filename, int target_width, int target_height) {
    ImageVector result;
    ImageVector frames;

    try {
        Magick::readImages(&frames, filename);
    } catch (Magick::Exception &e) {
        std::cerr << "Error loading image: " << e.what() << std::endl;
        return result;
    }

    if (frames.empty()) {
        std::cerr << "No image found." << std::endl;
        return result;
    }

    // Animated images have partial frames that need to be put together
    if (frames.size() > 1) {
        Magick::coalesceImages(&result, frames.begin(), frames.end());
    } else {
        result.push_back(frames[0]); // just a single still image
    }

    for (Magick::Image &image : result) {
        image.scale(Magick::Geometry(target_width, target_height));
    }

    return result;
}

void CopyImageToCanvas(const Magick::Image &image, Canvas *canvas) {
    const int offset_x = 0, offset_y = 0; // If you want to move the image.
    // Copy all the pixels to the canvas.
    for (size_t y = 0; y < image.rows(); ++y) {
        for (size_t x = 0; x < image.columns(); ++x) {
            const Magick::Color &c = image.pixelColor(x, y);
            if (c.alphaQuantum() < 256) {
                canvas->SetPixel(x + offset_x, y + offset_y,
                                 c.redQuantum(), c.greenQuantum(), c.blueQuantum());
            }
        }
    }
}

int main(int argc, char *argv[]) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm"; // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;

    RGBMatrixRuntime matrix_runtime;
    if (!matrix_runtime.Init(argc, argv, defaults))
        return 1;

    SignalHandler signal_handler;
    signal_handler.SetupExitCallback([&]() { matrix_runtime.Stop(); });

    Canvas *canvas = matrix_runtime.matrix();
    if (canvas == nullptr)
        return 1;

    Spotify spotify;

    while (true) {
        int updated = spotify.update();

        if (spotify.isPlaying()) {
            if (updated) {
                // Load the image
                ImageVector image = LoadImageAndScaleImage("./tmp/spotify.png", 64, 64);
                CopyImageToCanvas(image[0], canvas);
            }
            sleep(5);
            continue;
        }

        sleep(10);
    }

    matrix_runtime.Stop();

    return 0;
}
