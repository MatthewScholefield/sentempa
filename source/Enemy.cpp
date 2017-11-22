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

#include "Enemy.hpp"
#include "Polygon.hpp"
#include "Camera.hpp"

Enemy::Enemy(cint r, cint g, cint b, const Vec3f pos, cfloat rotSpeed, cfloat speed) :
poly(createShape(r, g, b)), pos(pos), rotSpeed(rotSpeed), speed(speed) { }

void Enemy::render(Renderer& renderer, const Camera& camera)
{
	poly.render(renderer, camera);
}

void Enemy::update(cfloat dt, const Camera &camera)
{
	Vec3f d = camera.getPos() - pos; // Delta
	pos += (d * speed * dt) / d.mag();
	Vec3f rotated;
	{
		const float rotX = rot.pos.y;
		const float rotY = rot.pos.x;

		const float sx = sin(rotX), cx = cos(rotX);
		const float sy = sin(rotY), cy = cos(rotY);

		rotated = {
			d.x * cy + d.y * sx * sy + d.z * cx * sy,
			d.y * cx + d.z * -sx,
			d.x * -sy + d.y * cy * sx + d.z * cx * cy
		};
	}
	
	rot.acc.x = rotated.x > 0 ? rotSpeed : -rotSpeed;
	rot.acc.y = rotated.y > 0 ? rotSpeed : -rotSpeed;
	
	rot.vel *= pow(0.3f, dt); // TODO: Implement shared set of physics constants
	rot.vel += rot.acc * dt;
	rot.pos += rot.vel * dt;
	
	poly.pos = pos;
	poly.rot = rot.pos;
}

Polygon Enemy::createShape(cint r, cint g, cint b)
{
	Polygon poly;
	poly.definePoint(0,{0, 0, 0});
	poly.definePoint(1,{-15, 0, 70});
	poly.definePoint(2,{15, 0, 70});
	poly.definePoint(3,{0, -10, 15});
	poly.centerPoints();

	poly.addFace({
		{(unsigned char) (95 + r * 5 / 255), (unsigned char) (95 + g * 5 / 255), (unsigned char) (95 + b * 5 / 255)},
		{
			{0, 1, 2}
		}
	});
	poly.addFace({
		{(unsigned char) (190 * r / 255), (unsigned char) (200 * g / 255), (unsigned char) (200 * b / 255)},
		{
			{0, 1, 3}
		}
	});
	poly.addFace({
		{(unsigned char) (220 * r / 255), (unsigned char) (220 * g / 255), (unsigned char) (220 * b / 255)},
		{
			{0, 2, 3}
		}
	});
	poly.addFace({
		{(unsigned char) (140 * r / 255), (unsigned char) (160 * g / 255), (unsigned char) (160 * b / 255)},
		{
			{1, 2, 3}
		}
	});
	return poly;
}


