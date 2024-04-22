#ifndef LINE_H
#define LINE_H

#include "tool.h"
#include "canvas.h"

class Line : public Tool {
public:
    Line(Canvas& canvas);

    void set_start(int x, int y, std::array<Uint8, 3>& color) override;
    void hold(int x, int y, std::array<Uint8, 3>& color) override;
};

#endif

