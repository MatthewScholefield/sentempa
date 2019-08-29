#include <memory>

#include "StarField.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

void StarField::refill(const Camera &camera) {
    auto shouldRemove = [&camera](const Star &star) {
        return (star.p - camera.getPos()).abs().max() > Camera::viewDist;
    };
    stars.erase(std::remove_if(stars.begin(), stars.end(), shouldRemove),
                stars.end());

    float starsToCreate = maxStars - (int) stars.size();

    if (starsToCreate == 0)
        return;

    Box newBox = {
            camera.getPos() - Camera::viewDist,
            {Camera::viewDist * 2, Camera::viewDist * 2, Camera::viewDist * 2}
    };

    // Delta
    Vec3f d = newBox.pos - box.pos;
    Vec3f da = d.abs();
    Vec3f &s = newBox.size;

    std::array<Box, 3> boxes;

    boxes[0].size = {da.x, s.y, s.z};
    boxes[1].size = {s.x - da.x, da.y, s.z};
    boxes[2].size = {s.x - da.x, s.y - da.y, da.z};

    boxes[0].pos = box.pos + (d.x > 0.f ? Vec3f(box.size.x, 0.f, 0.f) : Vec3f(d.x, d.y, d.z));
    boxes[1].pos = box.pos + (d.y > 0.f ? Vec3f(0.f, box.size.y, 0.f) : Vec3f(0.f, d.y, d.z));
    boxes[2].pos = box.pos + (d.z > 0.f ? Vec3f(0.f, 0.f, box.size.z) : Vec3f(0.f, 0.f, d.z));

    if (box.size.volume() == 0.f) {
        boxes[0] = newBox;
        boxes[1] = boxes[2] = Box();
    }

    float totalVolume = 0.f;
    std::array<float, boxes.size()> volumes{};
    for (int i = 0; i < volumes.size(); ++i) {
        totalVolume += (volumes[i] = boxes[i].size.volume());
    }

    for (int i = 0; i < boxes.size(); ++i) {
        cint numStars = int(std::round(starsToCreate * volumes[i] / totalVolume));
        const auto size = boxes[i].size.cast<int>();
        for (int j = 0; j < numStars; ++j)
            stars.push_back({boxes[i].pos + size.max(1).rand().cast<float>()});
    }
    box = newBox;
}

void StarField::update(cfloat dt, const Camera &camera) {
    for (Star &i : stars)
        i.update(dt);

    refill(camera);
}

void StarField::render(Renderer &renderer, const Camera &camera) const {
    const auto canvasSize = renderer.getSize().cast<float>();
    for (const Star &i : stars) {
        cauto proj = camera.projectPoint(i.p, canvasSize);
        if (!proj.onScreen)
            continue;
        cauto pt = proj.pt;

        cfloat dist = i.p.dist(camera.getPos());
        auto squareSize = cint16(dist == 0.f ? 0 : std::max(1.f, starSize / dist));

        if (pt.x + squareSize < 0.f || pt.x >= canvasSize.x ||
            pt.y + squareSize < 0.f || pt.y >= canvasSize.y)
            continue;

        float alpha = 255.f * (1.f - dist / Camera::viewDist);
        if (alpha <= 0.f)
            continue;

        uint8_t r = 255, g = 255, b = 255;
        cint twinkle = rand() % 301 - 150;
        if (twinkle > 0) {
            r -= twinkle;
            g -= twinkle;
        } else {
            g += twinkle / 2;
            b += twinkle;
        }

        renderer.drawFillSquare(cint16(pt.x), cint16(pt.y), squareSize, makeCol(r, g, b, uint8_t(alpha)));
    }
}

void StarField::Star::update(cfloat dt) {}
