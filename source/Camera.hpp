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
#include "types.hpp"

class InputManager;

class Camera
{
	static constexpr float maxFov = toRad(70.f);
	static constexpr float friction = 0.3f;
	static constexpr float mouseSpeed = 0.3f;
	static constexpr float moveSpeed = 200.f;
	static constexpr float turnSpeed = pi;

public:
	Camera(const Vec2i &size);
	void recalcFov(cint sx, cint sy);
	void update(cfloat dt, const InputManager &inputManager);
	cVec2f &getFov() const;
	cVec3f &getPos() const;
	Vec2f projectPoint(cVec3f &p, cVec2f &canvasSize) const;

private:
	void resize(cint sx, cint sy);
	void updateControls(const InputManager &inputManager);

	struct
	{
		Vec2f pos, vel, acc;
	} rot; // Rotation

	Vec2f fov;
	Vec3f pos, vel, acc;

	bool mouseMode = false;
};
