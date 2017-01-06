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
	float screenSize = 4.f * tan(maxFov / 2.f);
	if (sx > sy)
	{
		fov.x = screenSize;
		fov.y = fov.x * sy / sx;
	}
	else
	{
		fov.y = screenSize;
		fov.x = fov.y * sx / sy;
	}
}

constexpr float epsilon = 0.00001f;

void Camera::update(float dt)
{
	Vec3f d = acc;
	if (d.mag() >= epsilon)
	{
		const float rotX = angularPos.y;
		const float rotY = angularPos.x;

		const float sx = sin(rotX), cx = cos(rotX);
		const float sy = sin(rotY), cy = cos(rotY);

		d = {
			d.x * cy + d.y * sx * sy + d.z * cx * sy,
			d.y * cx + d.z * -sx,
			d.x * -sy + d.y * cy * sx + d.z * cx * cy
		};
	}

	vel *= friction;
	vel += d * dt;
	pos += vel * dt;

	angularPos += angularVel*dt;

	if (angularPos.x > pi())
		angularPos.x -= 2.f * pi();

	if (angularPos.x < -pi())
		angularPos.x += 2.f * pi();

	const float capAngle = pi() / 2.f;

	if (angularPos.y > capAngle)
		angularPos.y = capAngle;

	if (angularPos.y < -capAngle)
		angularPos.y = -capAngle;
}

const Vec2f& Camera::getFov()
{
	return fov;
}

const Vec3f& Camera::getPos()
{
	return pos;
}

Vec3f& Camera::getAcc()
{
	return acc;
}

Vec2f& Camera::getAngVel()
{
	return angularVel;
}

Vec2f Camera::projectPoint(const Vec3f &point, const Vec2f &canvasSize)
{
	Vec3f d = point - pos; // Delta
	Vec3f rotated;
	{
		const float rotX = -angularPos.y;
		const float rotY = -angularPos.x;

		const float sx = sin(rotX), cx = cos(rotX);
		const float sy = sin(rotY), cy = cos(rotY);

		rotated = {
			d.x * cy + d.z * sy,
			d.x * sx * sy + d.y * cx - d.z * sx * cy,
			d.x * -cx * sy + d.y * sx + d.z * cx * cy
		};
	}

	if (rotated.z < 0)
		return Vec2f(std::numeric_limits<float>::quiet_NaN(),
					std::numeric_limits<float>::quiet_NaN());

	return (Vec2f(rotated.x, rotated.y) / (fov * rotated.z) + 0.5f) * canvasSize;
}

