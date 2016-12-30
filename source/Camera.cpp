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

#include "Camera.hpp"

Camera::Camera(const Vec2i &size)
{
	recalcFov(size.x, size.y);
}

void Camera::resize(int sx, int sy)
{
	recalcFov(sx, sy);
}

void Camera::recalcFov(int sx, int sy)
{
	if (sx > sy)
	{
		fov.x = maxFov;
		fov.y = fov.x * sy / sx;
	}
	else
	{
		fov.y = maxFov;
		fov.x = fov.y * sx / sy;
	}
}

void Camera::update(float dt)
{
	v *= friction;
	v += a * dt;
	p += v * dt;
}

const Vec2f& Camera::getFov()
{
	return fov;
}
