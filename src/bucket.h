#ifndef BUCKET_H
#define BUCKET_H

#include "tool.h"
#include "canvas.h"

class Bucket : public Tool {
public:
    Bucket(Canvas& canvas);

    void set_start(int x, int y, std::array<float, 3>& color) override {

    };
};

#endif // BUCKET_H
