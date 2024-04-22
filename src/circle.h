#ifndef CIRCLE_H
#define CIRCLE_H

#include "tool.h"

#include "tool.h"
#include "canvas.h"

class Brush : public Tool {
public:
    Brush(Canvas& canvas);

    void set_start(int x, int y, std::array<float, 3>& color) override;
    void hold(int x, int y, std::array<float, 3>& color) override;
    void draw_brush(int x, int y, std::array<float, 3>& color, int radius);
    void draw_circle(int x1, int y1, int x2, int y2, std::array<float, 3>& color, int radius);
};

#endif
