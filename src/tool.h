
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
    virtual void set_start(int x, int y, std::array<float, 3>& color);
    virtual void hold(int mouse_x, int mouse_y);

protected:
    int x, y;
    Canvas& canvas;
};

#endif // TOOL_H