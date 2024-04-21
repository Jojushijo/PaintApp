#include "tool.h"
#include "canvas.h"

Tool::Tool(Canvas& canvas, std::array<int, 3> color, int x, int y) : canvas(canvas), color(color), x(x), y(y) {};

void Tool::set_start(int x, int y, std::array<int, 3> color) {
    this->x = x;
    this->y = y;
    this->color = color;
}

void Tool::hold(int mouse_x, int mouse_y) {};