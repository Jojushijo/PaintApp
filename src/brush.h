#ifndef BRUSH_H
#define BRUSH_H

#include "tool.h"
#include "canvas.h"

class Brush : public Tool {
public:
    Brush(Canvas& canvas);

    void set_start(int x, int y, std::array<float, 3>& color) override;
    void hold(int x, int y, std::array<float, 3>& color) override;
    void draw_brush(int x, int y, std::array<float, 3>& color, int radius);
};

#endif // BRUSH_H
