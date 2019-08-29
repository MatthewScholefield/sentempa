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
    void setColor(cuint8 r, cuint8 g, cuint8 b, cuint8 a = 255);
    void clear(cuint8 r = 0, cuint8 g = 0, cuint8 b = 0, cuint8 a = 255);

    void drawSingleLine(cint16 x1, cint16 y1, cint16 x2, cint16 y2, colInt col);
    void drawSinglePoint(cint16 x, cint16 y, colInt col);
    void drawFillSquare(cint16 x, cint16 y, cint16 rad, colInt col);
    void drawFillTri(const std::array<Vec2f, 3> &pts, colInt col);

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
