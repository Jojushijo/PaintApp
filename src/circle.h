#ifndef CIRCLE_H
#define CIRCLE_H

#include "tool.h"
#include "canvas.h"

class Circle : public Tool {
public:
    Circle(Canvas& canvas);

    void set_start(int x, int y, std::array<Uint8, 3>& color) override;
    void hold(int x, int y, std::array<Uint8, 3>& color) override;
};

#endif
