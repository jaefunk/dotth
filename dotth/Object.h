#pragma once

#include "Node.h"
#include "Component.h"
#include "Math/Transform.h"

class Object : public Node<Object>
{
public:
	void Init(void);
	void Update(void);
	void LateUpdate(void);
	void Draw(void);
	void Destroy(void);

protected:
	virtual void OnInit(void);
	virtual void OnDestroy(void);
	virtual void OnUpdate(void);
	virtual void OnLateUpdate(void) {}
	virtual void OnDraw(void);

private:
	Transform _Transform;
	std::list<std::shared_ptr<Component>> _Components;

public:
	void UpdateTransform(void)
	{
		Transform* ParentTransform = nullptr;
		std::shared_ptr<Object> Prt = Parent<Object>();
		if (Prt != nullptr)
			ParentTransform = &Prt->_Transform;
		_Transform.Update(ParentTransform);

		Foreach([](std::shared_ptr<Object> child) {
			child->UpdateTransform();
			});
	}
	const Transform& GetTransform(void) { return _Transform; }

public:
	template <typename ty>
	std::shared_ptr<ty> AddComponent(void)
	{
		std::shared_ptr<ty> value = std::make_shared<ty>();
		value->SetOwner(this->shared_from_this());
		_Components.push_back(value);
		return value;
	}

	void AddComponent(std::shared_ptr<Component> component)
	{
		for (std::shared_ptr<Component> Comp : _Components)
		{
			if (Comp->Serial() == component->Serial())
			{
				return;
			}
		}
		_Components.push_back(component);
	}

	void RemoveComponent(std::shared_ptr<Component> component)
	{
		_Components.remove(component);
	}

	template <typename CastTy = Component>
	std::shared_ptr<CastTy> FindComponent(std::string name)
	{
		for (std::shared_ptr<Component> Comp : _Components)
		{
			if (Comp->Name() == name)
			{
				return std::dynamic_pointer_cast<CastTy>(Comp);
			}
		}
		return nullptr;
	}


public:
	void SetScale(const Vector3F& value) { _Transform.SetScale(value); }
	void Scaling(const Vector3F& value) { _Transform.Scaling(value); }
	void Scaling(const float& value) { _Transform.Scaling(value); }
	void ScalingX(const float& value) { _Transform.ScalingX(value); }
	void ScalingY(const float& value) { _Transform.ScalingY(value); }
	void ScalingZ(const float& value) { _Transform.ScalingZ(value); }
	const Vector3F& GetLocalScale(void) { return _Transform.GetScale(); }

	void SetRotation(const Vector3F& value) { _Transform.SetRotation(value); }
	void Rotate(const Vector3F& value) { _Transform.Rotate(value); }
	void RotatePitch(const float& value) { _Transform.RotatePitch(value); }
	void RotateYaw(const float& value) { _Transform.RotateYaw(value); }
	void RotateRoll(const float& value) { _Transform.RotateRoll(value); }
	const Vector3F& GetLocalRotation(void) { return _Transform.GetRotation(); }

	void SetPosition(const Vector3F& value) { _Transform.SetPosition(value); }
	void Translate(const Vector3F& value) { _Transform.Translate(value); }
	void TranslateX(const float& value) { _Transform.TranslateX(value); }
	void TranslateY(const float& value) { _Transform.TranslateY(value); }
	void TranslateZ(const float& value) { _Transform.TranslateZ(value); }
	const Vector3F& GetLocalPosition(void) { return _Transform.GetPosition(); }

public:
	void DrawImGuiHierarchy(void);
};
