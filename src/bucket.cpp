#include "tool.h"
#include "canvas.h"

class Bucket : public Tool {
public:
    Bucket(Canvas& canvas, std::array<int, 3> color, int x = 0, int y = 0) : Tool(canvas, color, x, y) {};

    void set_start(int x, int y, std::array<int, 3> color) override {
        return;
    }

    void flood_fill() {

    }
};