#ifndef BUCKET_H
#define BUCKET_H

#include "tool.h"
#include "canvas.h"

class Bucket : public Tool {
public:
    Bucket(Canvas& canvas);
    void set_start(int x, int y, std::array<Uint8, 3>& color) override;
    void flood_fill(int x, int y, std::array<Uint8, 3>& replace_color, std::array<Uint8, 3>& new_color);
};

#endif // BUCKET_H
