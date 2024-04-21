#include "brush.h"
#include <SDL2/SDL2_gfxPrimitives.h>

// Constructor
Brush::Brush(Canvas& canvas) : Tool(canvas) {}

// Implementation of set_start function
void Brush::set_start(int x, int y, std::array<float, 3>& color) {
    int radius = 5;
    int u = x - canvas.x;
    int v = y - canvas.y;

    // Ensure the coordinates are within the canvas bounds
    if (u >= 0 && u < canvas.surface->w && v >= 0 && v < canvas.surface->h) {
        // Lock the surface to directly access its pixels
        if (SDL_LockSurface(canvas.surface) == 0) {
            // Get the color components
            Uint8 r = static_cast<Uint8>(color[0] * 255);
            Uint8 g = static_cast<Uint8>(color[1] * 255);
            Uint8 b = static_cast<Uint8>(color[2] * 255);

            // Draw a square (for example, a 10x10 square)
            for (int i = u - radius; i <= u + radius; ++i) {
                for (int j = v - radius; j <= v + radius; ++j) {
                    // Ensure the pixel coordinates are within the surface bounds
                    if (i >= 0 && i < canvas.surface->w && j >= 0 && j < canvas.surface->h) {
                        // Calculate the pixel offset
// Calculate the pixel offset
                        int index = j * canvas.surface->pitch + i * canvas.surface->format->BytesPerPixel;

                        // Get a pointer to the pixel
                        Uint8* pixel = reinterpret_cast<Uint8*>(canvas.surface->pixels) + index;

                        // Determine the appropriate color format and set the pixel color
                            // 24-bit color (RGB)
                        pixel[0] = b;
                        pixel[1] = g;
                        pixel[2] = r;
                    }
                }
            }

            // Unlock the surface
            SDL_UnlockSurface(canvas.surface);
        }
    }
}

void Brush::draw_brush() {

}

// Implementation of hold function
void Brush::hold(int mouse_x, int mouse_y) {
}
