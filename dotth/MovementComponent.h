#pragma once

#include "Component.h"

struct MovementInfo {
	float angularSpeed = 0.1f;
	float moveSpeed = 10.f;
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
	void MoveTo(const dotth::vector3& location, bool teleport = false)
	{
		printf("%d move to %s\n", GetSerial(), location.to_string().c_str());
		isReached = false;
		moveGoal = location;
	}
};
