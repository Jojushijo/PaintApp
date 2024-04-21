#ifndef BRUSH_H
#define BRUSH_H

#include "tool.h"
#include "canvas.h"

class Brush : public Tool {
public:
    Brush(Canvas& canvas, std::array<int, 3> color, int x = 0, int y = 0);

    void set_start(int x, int y, std::array<int, 3> color) override;
    void hold(int mouse_x, int mouse_y) override;
};

#endif // BRUSH_H
