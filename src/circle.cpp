#include "circle.h"
#include <cmath>

// Constructor
Circle::Circle(Canvas& canvas) : Tool(canvas) {};

// Implementation of set_start function
void Circle::set_start(int x, int y, std::array<Uint8, 3>& color) {
    this->x = x;
    this->y = y;
}

// Basically just rotate two points around a circle by an equal distance
// And then connect them with a line
void Circle::hold(int center_x, int center_y, std::array<Uint8, 3>& color) {
    canvas.clear_buffer();

    float dist = sqrt(pow(center_x - this->x, 2) + pow(center_y - this->y, 2));
    int steps = dist;

    int x1 = center_x + dist;
    int y1 = center_y;
    int x2, y2;

    for (int i = 1; i <= steps; i++) {
        float angle = static_cast<float>(i) * ((2 * M_PI) / steps);
        x2 = center_x + static_cast<int>(cos(angle) * dist);
        y2 = center_y + static_cast<int>(sin(angle) * dist);

        draw_line(x1, y1, x2, y2, color, 5);
        x1 = x2;
        y1 = y2;
    }
}

