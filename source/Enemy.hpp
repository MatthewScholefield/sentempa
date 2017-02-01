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

#include "types.hpp"
#include "Polygon.hpp"

class Renderer;
class Camera;

class Enemy
{
public:
	Enemy(cint r, cint g, cint b);
	void render(Renderer &renderer, const Camera &camera);
	void update(cfloat dt, const Camera &camera);

private:
	struct
	{
		Vec2f pos, vel, acc;
	} rot; // Rotation
	Vec3f pos;
	Polygon poly;
	static Polygon createShape(cint r, cint g, cint b);
};
