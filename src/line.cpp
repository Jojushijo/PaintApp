#include "line.h"
#include <cmath>

// Constructor
Line::Line(Canvas& canvas) : Tool(canvas) {}

// Implementation of set_start function
void Line::set_start(int x, int y, std::array<Uint8, 3>& color) {
    this->x = x;
    this->y = y;
}

void Line::hold(int x, int y, std::array<Uint8, 3>& color) {
    canvas.clear_buffer();

    draw_line(this->x, this->y, x, y, color, 5);
}