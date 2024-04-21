// brush.h
#ifndef BRUSH_H
#define BRUSH_H

#include "tool.h"
#include "canvas.h"

class Brush : public Tool {
public:
    Brush(Canvas& canvas, std::array<int, 3> color, int x = 0, int y = 0) : Tool(canvas, color, x, y) {};

    void hold(int mouse_x, int mouse_y) override {
        // Implement brush functionality here
        // For example, drawing on the canvas
    }
};

#endif // BRUSH_H
