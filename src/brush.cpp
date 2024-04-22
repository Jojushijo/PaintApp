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
        // Temp precision error amount, shifting amount is from original implementation and I believe is to avoid the need for floating point comparison
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