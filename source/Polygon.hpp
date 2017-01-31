/*
 * Copyright (C) 2017 Matthew D. Scholefield
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <memory>
#include <vector>
#include "Vec.hpp"
#include "Renderer.hpp"

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
	void addFace(const Triangle &tri);

private:
	std::vector<Vec3f> pts;
	std::vector<Triangle> triangles;
};
