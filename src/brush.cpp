#include "brush.h"

Brush::Brush(Canvas& canvas, std::array<int, 3> color, int x, int y) : Tool(canvas, color, x, y) {}

void Brush::set_start(int x, int y, std::array<int, 3> color) {
    Tool::set_start(x, y, color);
}

void Brush::hold(int mouse_x, int mouse_y) {
}
