#ifndef BRUSH_H
#define BRUSH_H

#include "tool.h"
#include "canvas.h"

class Brush : public Tool {
public:
    Brush(Canvas& canvas);

    void set_start(int x, int y, std::array<float, 3>& color) override;
    void hold(int mouse_x, int mouse_y) override;
    void draw_brush();
};

#endif // BRUSH_H
