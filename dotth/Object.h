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
	template <class Ty, class... Args>
	std::shared_ptr<Ty> AddComponent(Args... args)
	{
		std::shared_ptr<Ty> Comp = std::make_shared<Ty>(args...);
		Comp->SetOwner(this->weak_from_this());
		Components.push_back(Comp);
		return Comp;
	}

	bool AddComponent(std::shared_ptr<Component> component)
	{
		if (auto Owner = component->GetOwner())
			return false;

		Components.push_back(component);
		return true;
	}

	void RemoveComponent(std::shared_ptr<Component> component)
	{
		Components.remove(component);
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
