#include "tool.h"
#include "canvas.h"

Tool::Tool(Canvas& canvas, int x, int y) : canvas(canvas), x(x), y(y) {};

void Tool::set_start(int x, int y, std::array<float, 3>& color) {
    this->x = x;
    this->y = y;
}

void Tool::draw_brush(int x, int y, std::array<float, 3>& color, int radius) {
    int u = (x - canvas.zoom_x) / canvas.zoom;
    int v = (y - canvas.zoom_y) / canvas.zoom;

    // Ensure the coordinates are within the canvas bounds
    if (u >= 0 && u < canvas.buffer->w && v >= 0 && v < canvas.buffer->h) {
        // Lock the surface to directly access its pixels
        if (SDL_LockSurface(canvas.buffer) == 0) {
            // Get the color components
            Uint8 r = static_cast<Uint8>(color[0] * 255);
            Uint8 g = static_cast<Uint8>(color[1] * 255);
            Uint8 b = static_cast<Uint8>(color[2] * 255);

            // Draw a square (for example, a 10x10 square)
            for (int i = u - radius; i <= u + radius; ++i) {
                for (int j = v - radius; j <= v + radius; ++j) {
                    // Ensure the pixel coordinates are within the surface bounds
                    if (i >= 0 && i < canvas.buffer->w && j >= 0 && j < canvas.buffer->h) {
                        // Get the radial distance so we can smoothly set the pixels 
                        float dist = sqrt(pow(u - i, 2) + pow(v - j, 2));
                        float lerp_am = std::min(dist / radius, 1.0f);

                        // Calculate the pixel offset
                        int index = j * canvas.buffer->pitch + i * canvas.buffer->format->BytesPerPixel;

                        // Get a pointer to the pixel
                        Uint8* pixel = reinterpret_cast<Uint8*>(canvas.buffer->pixels) + index;

                        // Determine the appropriate color format and set the pixel color
                        pixel[0] = r;
                        pixel[1] = g;
                        pixel[2] = b;
                        pixel[3] = (1 - lerp_am) * 255 + lerp_am * pixel[3];
                    }
                }
            }

            // Unlock the surface
            SDL_UnlockSurface(canvas.buffer);
        }
    }
}

// An implementation of Bresenham's line algorithm https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void Tool::draw_line(int x1, int y1, int x2, int y2, std::array<float, 3>& color, int radius) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;

    // Difference between actual line and ideal line
    int err = dx - dy;
    int x = x1;
    int y = y1;

    while (x != x2 || y != y2) {
        // Draw a brush at each point along the line
        draw_brush(x, y, color, radius);

        // Temp precision error amount, shifting amount is from original implementation and I believe is to avoid the need for floating point comparison
        int e2 = err << 1;

        // Making sure we're not going too far below the ideal line
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }

        // Making sure we're not going too far to the right of the ideal line
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}


void Tool::hold(int x, int y, std::array<float, 3>& color) {};