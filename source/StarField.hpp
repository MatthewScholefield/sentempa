/*
 * Copyright (C) 2016 Matthew D. Scholefield
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

#include <vector>

#include "Vec.hpp"
#include "types.hpp"

class Renderer;
class Camera;

class StarField
{
public:
	void refill(const Camera &camera);
	void update(cfloat dt, const Camera &camera);
	void render(Renderer &renderer, const Camera &camera) const;

private:
	static constexpr int maxStars = 20000, maxDepth = 1000;
	static constexpr float starSize = 800.f;

	class Star
	{
	public:
		void update(cfloat dt);
		bool shouldRemove(const Vec2i &size) const;
		Vec3f p;
	};
	std::vector<Star> stars;

	class Box
	{
	public:
		Vec3f pos;
		Vec3f size;
	};

	// Area containing all existing stars
	Box box;
};
