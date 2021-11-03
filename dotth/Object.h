#pragma once

#include "ObjectBase.h"
#include "Component.h"
#include "Math/Transform.h"

class Object : public ObjectBase
{
public:
	void Init(void);
	void Update(void);
	void Draw(void);
	void Destroy(void);

public:
	virtual void OnInit(void) {}
	virtual void OnDestroy(void) {}
	virtual void OnUpdate(void) {}
	virtual void OnDraw(void) {}

private:
	std::list<std::shared_ptr<Component>> Components;

public:
	bool AddComponent(std::shared_ptr<Component> component)
	{
		if (auto Owner = component->GetOwner())
			return false;
		component->SetOwner(this->weak_from_this());
		Components.push_back(component);
		return true;
	}

	template <class Ty, class... Args>
	std::shared_ptr<Ty> AddComponent(Args... args)
	{
		std::shared_ptr<Ty> Comp = std::make_shared<Ty>(args...);
		AddComponent(Comp);
		return Comp;
	}

	void RemoveComponent(std::shared_ptr<Component> component)
	{
		Components.remove(component);
	}
	
	template <class Ty>
	bool RemoveComponent(void)
	{
		for (auto Component : Components)
		{
			if (auto Cast = std::dynamic_pointer_cast<Ty>(Component))
			{
				RemoveComponent(Cast);
				return true;
			}
		}
		return false;
	}

	template <typename CastTy = Component>
	std::shared_ptr<CastTy> FindComponent(void)
	{
		for (std::shared_ptr<Component> Component : Components)
		{
			if (auto Cast = std::dynamic_pointer_cast<CastTy>(Component))
			{
				return Cast;
			}
		}
		return nullptr;
	}

	template <typename CastTy = Component>
	std::shared_ptr<CastTy> FindComponent(std::string name)
	{
		for (std::shared_ptr<Component> Comp : Components)
		{
			if (Comp->GetName() == name)
			{
				return std::dynamic_pointer_cast<CastTy>(Comp);
			}
		}
		return nullptr;
	}

private:
	Transform _Transform;

public:
	void UpdateTransform(void)
	{
		Transform* ParentTransform = nullptr;
		std::shared_ptr<Object> Prt = GetParent<Object>();
		if (Prt != nullptr)
			ParentTransform = &Prt->_Transform;
		_Transform.Update(ParentTransform);
		Foreach<Object>([](std::shared_ptr<Object> child) {
			child->UpdateTransform();
		});
	}
	const Transform& GetTransform(void) { return _Transform; }

public:
	void SetScale(const Vector3& value) { _Transform.SetScale(value); }
	void Scaling(const Vector3& value) { _Transform.Scaling(value); }
	void Scaling(float value) { _Transform.Scaling(value); }
	const Vector3& GetLocalScale(void) { return _Transform.GetScale(); }

	void SetRotation(const Vector3& value) { _Transform.SetRotation(value); }
	void Rotate(const Vector3& value) { _Transform.Rotate(value); }
	void RotatePitch(float value) { _Transform.RotatePitch(value); }
	void RotateYaw(float value) { _Transform.RotateYaw(value); }
	void RotateRoll(float value) { _Transform.RotateRoll(value); }
	const Vector3& GetLocalRotation(void) { return _Transform.GetRotation(); }

	void SetPosition(const Vector3& value) { _Transform.SetPosition(value); }
	void Translate(const Vector3& value) { _Transform.Translate(value); }
	const Vector3& GetLocalPosition(void) { return _Transform.GetPosition(); }

public:
	void DrawImGuiHierarchy(void);
};
