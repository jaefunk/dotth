#pragma once

#include "Component.h"

struct MovementInfo {
	float angularSpeed = 0.1f;
	float walkSpeed = 3.f;
	bool lookAtGoal = false;

};

class MovementComponent : public Component
{
public:
	MovementComponent(void);

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;

private:
	MovementInfo movementInfo;
	bool isReached = true;
	dotth::vector3 moveGoal;

public:
	//					remain time, remain distance
	std::function<void(float, float)> OnMove;
	std::function<void(void)> OnReached;
	void MoveTo(const dotth::vector3& location, bool teleport = false);
	void LookAt(const dotth::vector3& location, bool pitchHold = true);
};
