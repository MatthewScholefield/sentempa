#pragma once

#include <memory>
#include <vector>
#include "Vec.hpp"
#include "Renderer.hpp"
#include "Utility.hpp"

class Renderer;
class Camera;

enum class RenderOrder
{
	before,
	after,
	either
};

class Triangle
{
public:
	Triangle(const Vec3<uint8_t> &color, const std::array<size_t, 3> &ids);
	void draw(Renderer &renderer, const Camera &camera, const std::vector<Vec3f> &pts) const;
	RenderOrder calcRenderOrder(const Triangle &other, const Camera &camera, const std::vector<Vec3f> &pts) const;

private:
	Vec3<uint8_t> color;
	std::array<size_t, 3> ids;
};

class Polygon
{
public:
	void render(Renderer &renderer, const Camera &camera) const;
	void definePoint(size_t id, const Vec3f &pt);
	void centerPoints();
	void addFace(const Triangle &tri);

	Vec3f pos;
	Vec2f rot;
private:
	std::vector<Vec3f> pts;
	std::vector<Triangle> triangles;
};
