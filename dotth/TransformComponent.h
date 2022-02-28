#pragma once

#include "Component.h"
#include "Math/Transform.h"

class TransformComponent : public Component
{
public:
	TransformComponent(void);

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;

public:
	void UpdateTransform(std::shared_ptr<TransformComponent> InParent)
	{
		Transform NewTransform(WorldTransform);
		if (InParent != nullptr)
		{
			vector3::multiply(NewTransform.Scale, InParent->WorldTransform.WorldScale, WorldTransform.Scale);
			vector3::multiply(NewTransform.Position, InParent->WorldTransform.WorldScale, WorldTransform.Position);
		}

		matrix scl = matrix::scaling(NewTransform.Scale);
		matrix pitch = matrix::rotate_pitch(NewTransform.Rotation.x);
		matrix yaw = matrix::rotate_yaw(NewTransform.Rotation.y);
		matrix roll = matrix::rotate_roll(NewTransform.Rotation.z);
		matrix pos = matrix::translate(NewTransform.Position);

		if (InParent != nullptr)
			NewTransform.WorldMatrixNoScale = pitch * yaw * roll * pos * InParent->WorldTransform.WorldMatrixNoScale;
		else
			NewTransform.WorldMatrixNoScale = pitch * yaw * roll * pos;
		
		NewTransform.WorldMatrix = scl * NewTransform.WorldMatrixNoScale;
	}

private:
	std::shared_ptr<TransformComponent> Parent;
	std::vector<std::shared_ptr<TransformComponent>> Children;

private:
	Transform WorldTransform;

public:
	std::shared_ptr<TransformComponent> GetRoot(void);
	std::shared_ptr<TransformComponent> GetParent(void);
	const std::vector<TransformComponent>& GetChildren();
	void SetParent(std::shared_ptr<TransformComponent> InComponent);
	void AddChild(std::shared_ptr<TransformComponent> InComponent);
	void DetachFromParent(void);

	Transform GetTransform(void)
	{
		return WorldTransform;
	}
	vector3 GetScale(void);
	vector3 GetRotation(void);
	vector3 GetPosition(void);
	void SetTransform(const Transform& InTransform);
	void SetScale(const vector3& InVector);
	void SetRotation(const vector3& InVector);
	void SetPosition(const vector3& InVector);
};
