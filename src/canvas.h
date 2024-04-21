#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <array>
#include <SDL2/SDL.h>

class Canvas {
public:
    SDL_Renderer* renderer;
    int w, h, x, y;
    float zoom;
    bool drawing;
    SDL_Surface* surface;
    SDL_Surface* buffer;
    std::array<float, 3> bodycolor;

    // Constructor with default parameter values
    Canvas(SDL_Renderer* renderer, int cx = 0, int cy = 0, int w = 720, int h = 480, float zoom = 1.0, bool drawing = false, const std::array<float, 3> bodycolor = { 255, 255, 255 });

    // Member functions
    void pan(int x_off, int y_off);
    void draw_self();
    void flush();
};

#endif // CANVAS_H
