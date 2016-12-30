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

#include "Utility.hpp"
#include "Vec.hpp"

class Camera
{
public:
	Camera(const Vec2i &size);
	void resize(int sx, int sy);
	void recalcFov(int sx, int sy);
	void update(float dt);
	const Vec2f &getFov();
	
	static constexpr float maxFov = toRad(100.f);
	Vec3f pos = {0.f, 0.f, 0.f};
	Vec3f vel = {0.f, 0.f, 0.f};
	
private:
	Vec2f fov;
};
