#include "bucket.h"
#include <iostream>
#include <array>
#include <stack>

Bucket::Bucket(Canvas& canvas) : Tool(canvas) {};

void Bucket::set_start(int x, int y, std::array<Uint8, 3>& color) {
    int u = (x - canvas.zoom_x) / canvas.zoom;
    int v = (y - canvas.zoom_y) / canvas.zoom;

    if (u >= 0 && u < canvas.surface->w && v >= 0 && v < canvas.surface->h) {

        if (SDL_LockSurface(canvas.buffer) == 0) {
            int index = v * canvas.surface->pitch + u * canvas.surface->format->BytesPerPixel;
            Uint8* pixel = reinterpret_cast<Uint8*>(canvas.surface->pixels) + index;

            std::array<Uint8, 3> pixel_color = {
                pixel[0],
                pixel[1],
                pixel[2]
            };

            flood_fill(u, v, pixel_color, color);
        }
        SDL_UnlockSurface(canvas.buffer);
    }
}

void Bucket::flood_fill(int x, int y, std::array<Uint8, 3>& replace_color, std::array<Uint8, 3>& new_color) {
    std::stack<std::pair<int, int>> pixels;
    pixels.push(std::make_pair(x, y));

    while (!pixels.empty()) {
        auto [u, v] = pixels.top();
        pixels.pop();

        if (u >= 0 && u < canvas.surface->w && v >= 0 && v < canvas.surface->h) {
            int index = v * canvas.surface->pitch + u * canvas.surface->format->BytesPerPixel;
            Uint8* pixel = reinterpret_cast<Uint8*>(canvas.surface->pixels) + index;

            if ((pixel[0] == replace_color[0]) && (pixel[1] == replace_color[1]) && (pixel[2] == replace_color[2])) {
                pixel[0] = new_color[0];
                pixel[1] = new_color[1];
                pixel[2] = new_color[2];

                // Add neighbors to the stack
                pixels.push(std::make_pair(u - 1, v)); // left
                pixels.push(std::make_pair(u + 1, v)); // right
                pixels.push(std::make_pair(u, v - 1)); // up
                pixels.push(std::make_pair(u, v + 1)); // down
            }
        }
    }
}

