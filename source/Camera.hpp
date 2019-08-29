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
	static constexpr float viewDist = 1000;
	
	class ProjectedPoint
	{
	public:
		Vec2f pt;
		bool onScreen;
	};
	
	Camera(const Vec2i &size);
	void recalcFov(cint sx, cint sy);
	void update(cfloat dt, const InputManager &inputManager);
	cVec2f &getFov() const;
	cVec3f &getPos() const;
	ProjectedPoint projectPoint(cVec3f &p, cVec2f &canvasSize) const;

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
