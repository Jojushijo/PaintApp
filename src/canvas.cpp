#include <iostream>
#include <array>
#include "canvas.h"
#include <SDL2/SDL.h> // Include SDL headers if needed


Canvas::Canvas(SDL_Renderer* renderer, int cx, int cy, int w, int h, float zoom, bool drawing, std::array<float, 3> bodycolor)
    : renderer(renderer), x(cx - w / 2), y(cy - h / 2), w(w), h(h), zoom(zoom), drawing(drawing), bodycolor(bodycolor), surface(SDL_CreateRGBSurface(0, w, h, 24, 0xFF0000, 0x00FF00, 0x0000FF, 0)), buffer(SDL_CreateRGBSurface(0, w, h, 24, 0, 0, 0, 0)) {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, bodycolor[0], bodycolor[1], bodycolor[2]));
    SDL_FillRect(buffer, NULL, SDL_MapRGBA(surface->format, bodycolor[0], bodycolor[1], bodycolor[2], 0)); // Set the alpha value to 0 for transparency
}

void Canvas::pan(int x_off, int y_off) {
    x += x_off;
    y += y_off;
}

void Canvas::draw_self() {
    // Create texture from surface
    SDL_Texture* tex_canvas = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture* tex_buffer = SDL_CreateTextureFromSurface(renderer, buffer);

    // Set the destination rectangle to position the texture in the center of the screen
    SDL_Rect destRect = { x, y, w, h };

    // Render textures
    SDL_RenderCopy(renderer, tex_canvas, nullptr, &destRect);
    // SDL_RenderCopy(renderer, tex_buffer, nullptr, &destRect);

    // Clean up
    SDL_DestroyTexture(tex_canvas);
    SDL_DestroyTexture(tex_buffer);
}

void Canvas::flush() {

}