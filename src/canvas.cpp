#include <iostream>
#include <array>
#include "canvas.h"
#include <SDL2/SDL.h> // Include SDL headers if needed


Canvas::Canvas(SDL_Renderer* renderer, int cx, int cy, int w, int h, float zoom, bool drawing, std::array<float, 3> bodycolor)
    : renderer(renderer), x(cx - w / 2), y(cy - h / 2), w(w), h(h), zoom(zoom), drawing(drawing), bodycolor(bodycolor), surface(SDL_CreateRGBSurface(0, w, h, 24, 0xFF0000, 0x00FF00, 0x0000FF, 0)), buffer(SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32)) {
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, bodycolor[0], bodycolor[1], bodycolor[2]));
    SDL_FillRect(buffer, nullptr, SDL_MapRGBA(buffer->format, bodycolor[0], bodycolor[1], bodycolor[2], 0));
}

void Canvas::pan(int x_off, int y_off) {
    x += x_off;
    y += y_off;
}

void Canvas::draw_self() {
    // Calculate the zoomed width and height
    int zoom_w = static_cast<int>(w * zoom);
    int zoom_h = static_cast<int>(h * zoom);
    zoom_x = x + (w - zoom_w) / 2;
    zoom_y = y + (h - zoom_h) / 2;

    // Create texture from surface
    SDL_Texture* tex_canvas = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture* tex_buffer = SDL_CreateTextureFromSurface(renderer, buffer);

    // Set the destination rectangle to position the texture in the center of the screen
    SDL_Rect destRect = { zoom_x, zoom_y, zoom_w, zoom_h };

    // Render textures
    SDL_RenderCopy(renderer, tex_canvas, nullptr, &destRect);
    SDL_RenderCopy(renderer, tex_buffer, nullptr, &destRect);

    // Clean up
    SDL_DestroyTexture(tex_canvas);
    SDL_DestroyTexture(tex_buffer);
}

void Canvas::clear_buffer() {
    // buffer = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(buffer, nullptr, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
}

void Canvas::flush() {
    // Enable alpha blending on the renderer
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Set the alpha modulation of the buffer surface
    SDL_SetSurfaceAlphaMod(buffer, SDL_ALPHA_OPAQUE);

    // Blit the buffer surface onto the main surface with alpha blending
    SDL_BlitSurface(buffer, nullptr, surface, nullptr);

    // Clear the buffer surface
    clear_buffer();
}