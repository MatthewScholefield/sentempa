#pragma once

#include "types.hpp"
#include "Polygon.hpp"

class Renderer;

class Camera;

class Enemy {
public:
    Enemy(cint r, cint g, cint b, const Vec3f pos, cfloat rotSpeed, cfloat speed);
    void render(Renderer &renderer, const Camera &camera);
    void update(cfloat dt, const Camera &camera);

private:
    struct {
        Vec2f pos, vel, acc;
    } rot; // Rotation
    Vec3f pos;
    cfloat rotSpeed, speed;
    Polygon poly;
    static Polygon createShape(cint r, cint g, cint b);
};
