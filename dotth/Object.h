#pragma once

#include "Node.h"
#include "Component.h"
#include "Math/Transform.h"

using namespace dotth;
class Object : public Node<Object>
{
public:
	virtual ~Object(void) {}

public:
	void Init(void);
	void Update(float InDeltaSeconds);
	void Draw(void);
	void Destroy(void);

public:
	virtual void OnInit(void) {}
	virtual void OnDestroy(void) {}
	virtual void OnUpdate(void) {}
	virtual void OnDraw(void) {}
	virtual void OnDrawImGui(void) {}

private:
	std::shared_ptr<class Camera> ActiveCamera;
public:
	void SetActiveCamera(std::shared_ptr<class Camera> camera);
	std::shared_ptr<class Camera> GetActiveCamera(void);

private:
	std::list<std::shared_ptr<Component>> Components;

public:
	template <class Ty, class... Args>
	std::shared_ptr<Ty> AddComponent(Args... args);
	template <typename CastTy = Component>
	std::shared_ptr<CastTy> FindComponent(void);
	template <typename CastTy = Component>
	std::shared_ptr<CastTy> FindComponent(std::string name);
	template <class Ty>
	bool RemoveComponent(void);
	bool AddComponent(std::shared_ptr<Component> component);
	void RemoveComponent(std::shared_ptr<Component> component);

private:
	float DeltaSeconds = 0.f;
public:
	float GetDeltaSeconds(void);

private:
	Transform _Transform;

public:
	void UpdateTransform(void);
	const Transform& GetTransform(void) { return _Transform; }
	const matrix& GetWorldMatrix(void) { return _Transform.WorldMatrix; }

public:
	void SetScale(const vector3& value) { _Transform.SetScale(value); }
	void Scaling(const vector3& value) { _Transform.Scaling(value); }
	void Scaling(float value) { _Transform.Scaling(value); }
	const vector3& GetLocalScale(void) { return _Transform.GetScale(); }

	void SetRotation(const vector3& value) { _Transform.SetRotation(value); }
	void Rotate(const vector3& value) { _Transform.Rotate(value); }
	void RotatePitch(float value) { _Transform.RotatePitch(value); }
	void RotateYaw(float value) { _Transform.RotateYaw(value); }
	void RotateRoll(float value) { _Transform.RotateRoll(value); }
	const vector3& GetLocalRotation(void) { return _Transform.GetRotation(); }

	void SetPosition(const vector3& value) { _Transform.SetPosition(value); }
	void Translate(const vector3& value) { _Transform.Translate(value); }
	const vector3& GetLocalPosition(void) { return _Transform.GetPosition(); }

public:
	void DrawImGui(void);
	void DrawImGuiHierarchy(void);
};

template<class Ty, class ...Args>
std::shared_ptr<Ty> Object::AddComponent(Args ...args)
{
	std::shared_ptr<Ty> Comp = std::make_shared<Ty>(args...);
	AddComponent(Comp);
	return Comp;
}

template<class Ty>
bool Object::RemoveComponent(void)
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

template<typename CastTy>
std::shared_ptr<CastTy> Object::FindComponent(void)
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

template<typename CastTy>
std::shared_ptr<CastTy> Object::FindComponent(std::string name)
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
