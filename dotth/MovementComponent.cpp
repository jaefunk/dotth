
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
		return;
	}

	dotth::vector3 diff = moveGoal - owner->GetLocalPosition();
	dotth::vector3 direction = diff.normalize();
	float diffLength = diff.length();
	float translateLength = diffLength >= movementInfo.moveSpeed ? movementInfo.moveSpeed : diffLength;
	owner->Translate(direction * translateLength);
		
	dotth::vector3 cross = dotth::vector3::cross(dotth::vector3::forward(), direction);
	float yawGoal = dotth::vector3::angle(dotth::vector3::forward(), direction);
	yawGoal = (cross.y >= 0.f ? yawGoal : -yawGoal);
	yawGoal += 3.141592f;
	owner->SetRotation(dotth::vector3(0.f, yawGoal, 0.f));
	
}

void MovementComponent::OnDraw(void)
{
}

void MovementComponent::OnDestroy(void)
{
}

