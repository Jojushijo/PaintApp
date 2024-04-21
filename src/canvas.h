#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <array>
#include <SDL2/SDL.h> // Include SDL headers if needed

class Canvas {
public:
    SDL_Renderer* renderer;
    int w, h, x, y;
    float zoom;
    bool drawing;
    std::string tool = "brush";
    SDL_Surface* surface;
    SDL_Surface* buffer;
    std::array<int, 3> bodycolor;

    Canvas(SDL_Renderer* renderer, int cx = 0, int cy = 0, int w = 720, int h = 480, float zoom = 1.0, bool drawing = false, std::array<int, 3> bodycolor = { 255, 255, 255 })
        : renderer(renderer), x(cx - w / 2), y(cy - h / 2), w(w), h(h), zoom(zoom), drawing(drawing), bodycolor(bodycolor), surface(SDL_CreateRGBSurface(0, w, h, 24, 0, 0, 0, 0)), buffer(SDL_CreateRGBSurface(0, w, h, 24, 0, 0, 0, 0)) {
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, bodycolor[0], bodycolor[1], bodycolor[2]));
        SDL_FillRect(buffer, NULL, SDL_MapRGBA(surface->format, bodycolor[0], bodycolor[1], bodycolor[2], 0)); // Set the alpha value to 0 for transparency
    }

    void move(int x_off, int y_off) {
        x += x_off;
        y += y_off;
    }

    void draw_self() {
        // Create texture from surface
        SDL_Texture* tex_canvas = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Texture* tex_buffer = SDL_CreateTextureFromSurface(renderer, buffer);


        if (tex_canvas == nullptr) {
            // Handle error
            return;
        }

        // Set the destination rectangle to position the texture in the center of the screen
        SDL_Rect destRect = { x, y, w, h };

        // Render textures
        SDL_RenderCopy(renderer, tex_canvas, nullptr, &destRect);
        SDL_RenderCopy(renderer, tex_buffer, nullptr, &destRect);

        // Clean up
        SDL_DestroyTexture(tex_canvas);
    }
};

#endif // CANVAS_H
