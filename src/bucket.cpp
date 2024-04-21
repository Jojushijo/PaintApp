#include "tool.h"
#include "canvas.h"

class Bucket : public Tool {
public:
    Bucket(Canvas& canvas) : Tool(canvas) {};

    void set_start(int x, int y, std::array<float, 3>& color) override {
        std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
    }

    void flood_fill() {

    }
};