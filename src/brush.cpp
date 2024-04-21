#include "brush.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cmath>
// #include <algorithm>

// Constructor
Brush::Brush(Canvas& canvas) : Tool(canvas) {}

// Implementation of set_start function
void Brush::set_start(int x, int y, std::array<float, 3>& color) {
    this->x = x;
    this->y = y;

    draw_brush(x, y, color, 5);
}

void Brush::draw_brush(int x, int y, std::array<float, 3>& color, int radius) {
    int u = x - canvas.x;
    int v = y - canvas.y;

    // Ensure the coordinates are within the canvas bounds
    if (u >= 0 && u < canvas.buffer->w && v >= 0 && v < canvas.buffer->h) {
        // Lock the surface to directly access its pixels
        if (SDL_LockSurface(canvas.buffer) == 0) {
            // Get the color components
            Uint8 r = static_cast<Uint8>(color[0] * 255);
            Uint8 g = static_cast<Uint8>(color[1] * 255);
            Uint8 b = static_cast<Uint8>(color[2] * 255);

            // Draw a square (for example, a 10x10 square)
            for (int i = u - radius; i <= u + radius; ++i) {
                for (int j = v - radius; j <= v + radius; ++j) {
                    // Ensure the pixel coordinates are within the surface bounds
                    if (i >= 0 && i < canvas.buffer->w && j >= 0 && j < canvas.buffer->h) {
                        // Get the radial distance so we can smoothly set the pixels 
                        float dist = sqrt(pow(u - i, 2) + pow(v - j, 2));
                        float lerp_am = std::min(dist / radius, 1.0f);

                        // Calculate the pixel offset
                        int index = j * canvas.buffer->pitch + i * canvas.buffer->format->BytesPerPixel;

                        // Get a pointer to the pixel
                        Uint8* pixel = reinterpret_cast<Uint8*>(canvas.buffer->pixels) + index;

                        // Determine the appropriate color format and set the pixel color
                        pixel[0] = (1 - lerp_am) * b + lerp_am * pixel[0];
                        pixel[1] = (1 - lerp_am) * g + lerp_am * pixel[1];
                        pixel[2] = (1 - lerp_am) * r + lerp_am * pixel[2];
                    }
                }
            }

            // Unlock the surface
            SDL_UnlockSurface(canvas.buffer);
        }
    }
}

// Implementation of hold function
// void Brush::draw_line(int x1, int y1, int x2, int y2, std::array<float, 3>& color, int brush_radius) {
// 
//     }
// }

// An implementation of Bresenham's line algorithm https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void Brush::hold(int x, int y, std::array<float, 3>& color) {
    int dx = abs(this->x - x);
    int dy = abs(this->y - y);
    int sx = x < this->x ? 1 : -1;
    int sy = y < this->y ? 1 : -1;

    // Difference between actual line and ideal line
    int err = dx - dy;
    int new_x = x;
    int new_y = y;

    while (x != this->x || y != this->y) {
        int e2 = err << 1;

        // Making sure we're not going too far below the ideal line
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }

        // Not going too far right of the ideal line
        if (e2 < dx) {
            err += dx;
            y += sy;
        }

        draw_brush(x, y, color, 5);
    }

    this->x = new_x;
    this->y = new_y;
}