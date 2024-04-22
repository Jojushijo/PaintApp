
#ifndef TOOL_H
#define TOOL_H

#include "canvas.h" // Include Canvas header file

// Bucket tool
// Line tool
// Circle tool
// Dot tool
class Tool {
public:
    Tool(Canvas& canvas, int x = 0, int y = 0);
    virtual void set_start(int x, int y, std::array<Uint8, 3>& color);
    virtual void hold(int x, int y, std::array<Uint8, 3>& color);
    void draw_brush(int x, int y, std::array<Uint8, 3>& color, int radius);
    void draw_line(int x1, int y1, int x2, int y2, std::array<Uint8, 3>& color, int radius);

protected:
    int x, y;
    Canvas& canvas;
};

#endif // TOOL_H