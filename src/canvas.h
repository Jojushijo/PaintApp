#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <array>
#include <SDL2/SDL.h> // Include SDL headers if needed

class Canvas {
public:
    SDL_Renderer* renderer;
    int w, h, x1, y1, x2, y2;
    float zoom;
    bool drawing;
    std::string tool = "brush";
    SDL_Surface* surface;
    std::array<int, 3> bodycolor;

    Canvas(SDL_Renderer* renderer, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, float zoom = 1.0, bool drawing = false, std::array<int, 3> bodycolor = { 255, 255, 255 })
        : renderer(renderer), x1(x1), y1(y1), x2(x2), y2(y2), zoom(zoom), drawing(drawing), bodycolor(bodycolor), surface(SDL_CreateRGBSurface(0, w, h, 24, 0, 0, 0, 0)) {
    }

    void draw() {
        // Draw Shape
        SDL_Rect Canvas = { 0, 0, 200, 200 };
        SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(this->renderer, &Canvas);
        // SDL_RenderPresent(this->renderer);
    }
};

#endif // CANVAS_H
