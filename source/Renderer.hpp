#pragma once

#include <memory>
#include <vector>
#include <SDL2/SDL_render.h>
#include "Vec.hpp"
#include "types.hpp"

enum class Shape {
    LINES, POINTS
};

using colInt = uint32_t;

// Used to concatenate 8 bit color values into a single 32 bit int

constexpr colInt makeCol(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    return (r << (0 * 8)) |
           (g << (1 * 8)) |
           (b << (2 * 8)) |
           (a << (3 * 8));
}

class Renderer {
public:
    Renderer(SDL_Renderer *sdlRenderer, const Vec2i &size);
    void setColor(cint r, cint g, cint b, cint a = 255);
    void clear(cint r = 0, cint g = 0, cint b = 0, cint a = 255);

    void drawSingleLine(cint x1, cint y1, cint x2, cint y2, const colInt col);
    void drawSinglePoint(cint x, cint y, const colInt col);
    void drawFillSquare(cint x, cint y, cint rad, const colInt col);
    void drawFillTri(const std::array<Vec2f, 3> &pts, const colInt col);

    void beginPoints();
    void addPoint(cint x, cint y);
    void endPoints(Shape shape);

    void draw();
    void resize(cint sx, cint sy);
    int getSX() const;
    int getSY() const;
    const Vec2i &getSize() const;

private:
    using RenderShapesFunc = int (*)(SDL_Renderer *, const SDL_Point *points, int count);

    RenderShapesFunc getShapesFunc(Shape shape) const;

    std::vector<SDL_Point> points;
    SDL_Renderer *sdlRenderer;
    Vec2i size;
};
