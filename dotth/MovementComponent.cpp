
#include "MovementComponent.h"
#include "Object.h"

MovementComponent::MovementComponent(void)
{
}

void MovementComponent::OnInit(void)
{
}

void MovementComponent::OnUpdate(void)
{
	if (isReached == true)
		return;

	Object* owner = GetOwner<Object>();	
	if (dotth::vector3::equal(moveGoal, owner->GetLocalPosition()))
	{
		isReached = true;
		if (OnReached)
			OnReached();
		return;
	}

	dotth::vector3 diff = moveGoal - owner->GetLocalPosition();
	dotth::vector3 direction = diff.normalize();
	float diffLength = diff.length();
	float translateLength = diffLength >= movementInfo.walkSpeed ? movementInfo.walkSpeed : diffLength;
	owner->Translate(direction * translateLength);
	
	float distance = diff.length();
	float time = distance / movementInfo.walkSpeed;
	if (OnMove)
		OnMove(time, distance);
}

void MovementComponent::OnDraw(void)
{
}

void MovementComponent::OnDestroy(void)
{
}

void MovementComponent::MoveTo(const dotth::vector3& location, bool teleport)
{
	printf("%d move to %s\n", GetSerial(), location.to_string().c_str());
	isReached = false;
	moveGoal = location;
	LookAt(location);
}

void MovementComponent::LookAt(const dotth::vector3& location, bool pitchHold)
{
	Object* owner = GetOwner<Object>();
	dotth::vector3 diff = location - owner->GetLocalPosition();
	dotth::vector3 direction = diff.normalize();
	dotth::vector3 cross = dotth::vector3::cross(dotth::vector3::forward(), direction);
	float yawGoal = dotth::vector3::angle(dotth::vector3::forward(), direction);
	yawGoal = (cross.y >= 0.f ? yawGoal : -yawGoal);
	yawGoal += 3.141592f;
	owner->SetRotation(dotth::vector3(0.f, yawGoal, 0.f));
}

