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
			Vector3::Multiply(NewTransform.Scale, InParent->WorldTransform.WorldScale, WorldTransform.Scale);
			Vector3::Multiply(NewTransform.Position, InParent->WorldTransform.WorldScale, WorldTransform.Position);
		}

		Matrix scl = Matrix::Scaling(NewTransform.Scale);
		Matrix pitch = Matrix::RotatePitch(NewTransform.Rotation.x);
		Matrix yaw = Matrix::RotateYaw(NewTransform.Rotation.y);
		Matrix roll = Matrix::RotateRoll(NewTransform.Rotation.z);
		Matrix pos = Matrix::Translate(NewTransform.Position);

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
	Vector3 GetScale(void);
	Vector3 GetRotation(void);
	Vector3 GetPosition(void);
	void SetTransform(const Transform& InTransform);
	void SetScale(const Vector3& InVector);
	void SetRotation(const Vector3& InVector);
	void SetPosition(const Vector3& InVector);
};
