#include <vector>
#include <iostream>
#include <unistd.h>
#include <Magick++.h>

#include "../src/spotify.h"
#include <rgbmatrix/graphics.h>

using namespace std;
using namespace rgb_matrix;
using ImageVector = std::vector<Magick::Image>;

// Given the filename, load the image and scale it to the size of the matrix.
static ImageVector LoadImageAndScaleImage(const char *filename, int target_width, int target_height) {
    ImageVector result;

    ImageVector frames;
    try {
        Magick::readImages(&frames, filename);
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

void CopyImageToCanvas(const Magick::Image &image, FrameCanvas *canvas) {
    const int offset_x = 0, offset_y = 0; // If you want to move the image.
    // Copy all the pixels to the canvas.
    for (ssize_t y = 0; y < image.rows(); ++y) {
        for (ssize_t x = 0; x < image.columns(); ++x) {
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

int main(int argc, char *argv[]) {
    Spotify spotify = Spotify();

    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm"; // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;

    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == nullptr) {
        fprintf(stderr, "Failed to create RGBMatrix canvas.\n");
        return 1;
    }

    FrameCanvas *frame_canvas = dynamic_cast<FrameCanvas *>(canvas);
    if (frame_canvas == nullptr) {
        fprintf(stderr, "Failed to get FrameCanvas.\n");
        return 1;
    }

    while (true) {
        int updated = spotify.update();

        if (spotify.isPlaying()) {
            if (updated) {
                // Load the image
                ImageVector images = LoadImageAndScaleImage("./tmp/spotify.png", 64, 64);
                if (!images.empty()) {
                    CopyImageToCanvas(images[0], frame_canvas);
                    frame_canvas->Update();
                }
            }
            sleep(4);
            continue;
        }
    }

    delete canvas;
    return 0;
}
