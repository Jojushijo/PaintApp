#include "tool.h"
#include "canvas.h"

Tool::Tool(Canvas& canvas, int x, int y) : canvas(canvas), x(x), y(y) {};

void Tool::set_start(int x, int y, std::array<float, 3>& color) {
    this->x = x;
    this->y = y;
}

void Tool::hold(int mouse_x, int mouse_y) {};