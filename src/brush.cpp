#include "brush.h"
#include <cmath>

// Constructor
Brush::Brush(Canvas& canvas) : Tool(canvas) {}

// Implementation of set_start function
void Brush::set_start(int x, int y, std::array<Uint8, 3>& color) {
    this->x = x;
    this->y = y;

    draw_brush(x, y, color, 5);
}


// An implementation of Bresenham's line algorithm https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void Brush::hold(int x, int y, std::array<Uint8, 3>& color) {
    draw_line(x, y, this->x, this->y, color, 5);

    this->x = x;
    this->y = y;
}