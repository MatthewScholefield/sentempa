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

#include "Utility.hpp"
#include "Camera.hpp"
#include "SdlManager.hpp"
#include "InputManager.hpp"

Camera::Camera(const Vec2i &size)
{
	recalcFov(size.x, size.y);
	SdlManager::onResize([this](int sx, int sy)
	{
		resize(sx, sy);
	});
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

void Camera::updateControls(const InputManager& inputManager)
{
	acc = 0.f;
	rot.acc = 0.f;

	auto check = [&inputManager](const Key key, float &data, const float val)
	{
		if (inputManager.isKeyPressed(key))
			data = val;
	};

	check(Key::lookLeft, rot.acc.x, -turnSpeed);
	check(Key::lookRight, rot.acc.x, +turnSpeed);
	check(Key::lookDown, rot.acc.y, -turnSpeed);
	check(Key::lookUp, rot.acc.y, +turnSpeed);

	check(Key::moveLeft, acc.x, -moveSpeed);
	check(Key::moveRight, acc.x, +moveSpeed);
	check(Key::moveUp, acc.y, -moveSpeed);
	check(Key::moveDown, acc.y, +moveSpeed);
	check(Key::moveBackwards, acc.z, -moveSpeed);
	check(Key::moveForwards, acc.z, +moveSpeed);

	const float newVx = +mouseSpeed * inputManager.getMouseDx();
	const float newVy = -mouseSpeed * inputManager.getMouseDy();

	if (std::abs(rot.vel.x) < std::abs(newVx))
		rot.vel.x = newVx;
	if (std::abs(rot.vel.y) < std::abs(newVy))
		rot.vel.y = newVy;
}

void Camera::update(float dt, const InputManager &inputManager)
{
	updateControls(inputManager);
	Vec3f a = acc;
	if (a.mag() >= epsilon)
	{
		const float rotX = rot.pos.y;
		const float rotY = rot.pos.x;

		const float sx = sin(rotX), cx = cos(rotX);
		const float sy = sin(rotY), cy = cos(rotY);

		a = {
			a.x * cy + a.y * sx * sy + a.z * cx * sy,
			a.y * cx + a.z * -sx,
			a.x * -sy + a.y * cy * sx + a.z * cx * cy
		};
	}

	vel *= pow(friction, dt);
	vel += a * dt;
	pos += vel * dt;

	rot.vel *= pow(friction, dt);
	rot.vel += rot.acc * dt;
	rot.pos += rot.vel * dt;

	if (rot.pos.x > pi)
		rot.pos.x -= 2.f * pi;

	if (rot.pos.x < -pi)
		rot.pos.x += 2.f * pi;

	const float capAngle = pi / 2.f;

	if (rot.pos.y > capAngle)
		rot.pos.y = capAngle;

	if (rot.pos.y < -capAngle)
		rot.pos.y = -capAngle;
}

const Vec2f& Camera::getFov()
{
	return fov;
}

const Vec3f& Camera::getPos()
{
	return pos;
}

Vec2f Camera::projectPoint(const Vec3f &point, const Vec2f &canvasSize)
{
	Vec3f d = point - pos; // Delta
	Vec3f rotated;
	{
		const float rotX = -rot.pos.y;
		const float rotY = -rot.pos.x;

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

