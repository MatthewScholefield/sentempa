#include "types.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2_gfxPrimitives.h>
#include "Renderer.hpp"
#include "SdlManager.hpp"

Renderer::Renderer(SDL_Renderer *sdlRenderer, const Vec2i &size) :
        sdlRenderer(sdlRenderer), size(size) {
    SdlManager::onResize([this](cint sx, cint sy) {
        resize(sx, sy);
    });
}

void Renderer::setColor(cuint8 r, cuint8 g, cuint8 b, cuint8 a) {
    SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);
}

void Renderer::clear(cuint8 r, cuint8 g, cuint8 b, cuint8 a) {
    setColor(r, g, b, a);
    SDL_RenderClear(sdlRenderer);
}

void Renderer::drawSingleLine(cint16 x1, cint16 y1, cint16 x2, cint16 y2, const colInt col) {
    lineColor(sdlRenderer, x1, y1, x2, y2, col);
}

void Renderer::drawSinglePoint(cint16 x, cint16 y, const colInt col) {
    pixelColor(sdlRenderer, x, y, col);
}

void Renderer::drawFillSquare(cint16 x, cint16 y, cint16 rad, const colInt col) {
    boxColor(sdlRenderer, x, y, cint16(x + rad - 1), cint16(y + rad - 1), col);
}

void Renderer::drawFillTri(const std::array<Vec2f, 3> &pts, const colInt col) {
    filledTrigonColor(sdlRenderer,
                      cint16(pts[0].x), cint16(pts[0].y),
                      cint16(pts[1].x), cint16(pts[1].y),
                      cint16(pts[2].x), cint16(pts[2].y), col);
}

void Renderer::beginPoints() {
    points.clear();
}

void Renderer::addPoint(cint x, cint y) {
    points.push_back({x, y});
}

void Renderer::endPoints(Shape shape) {
    auto func = getShapesFunc(shape);
    func(sdlRenderer, points.data(), int(points.size()));
}

void Renderer::draw() {
    SDL_RenderPresent(sdlRenderer);
}

void Renderer::resize(cint sx, cint sy) {
    size = {sx, sy};
}

int Renderer::getSX() const {
    return size.x;
}

int Renderer::getSY() const {
    return size.y;
}

const Vec2i &Renderer::getSize() const {
    return size;
}

Renderer::RenderShapesFunc Renderer::getShapesFunc(Shape shape) const {
    switch (shape) {
        case Shape::LINES:
            return &SDL_RenderDrawLines;
        case Shape::POINTS:
            return &SDL_RenderDrawPoints;
        default:
            throw std::runtime_error("Invalid shape");
    }
}

