#pragma once

#include "SystemDefine.h"
#include "Object.h"

class Scene : public Base
{
	friend class Scenario;

public:
	Scene(void);

public:
	void Init(void);
	void Update(void);
	void Draw(void);
	void Destroy(void);

public:
	virtual void OnInit(void) {}
	virtual void OnUpdate(void) {}
	virtual void OnDraw(void) {}
	virtual void OnDestroy(void) {}

private:
	std::list<std::shared_ptr<Object>> Objects;

public:
	template <class Ty, class... Args>
	std::shared_ptr<Ty> SpawnObject(Args... args);
	template <typename CastTy = Object>
	std::shared_ptr<Object> FindObject(std::string name);
	void SpawnObject(std::shared_ptr<Object> object);
	void RemoveObject(std::shared_ptr<Object> object);


private:
	std::shared_ptr<class Camera> ActiveCamera;
public:
	std::shared_ptr<class Camera> GetActiveCamera(void);

private:
	float DeltaSeconds = 0.f;
public:
	float GetDeltaSeconds(void);

public:
	virtual void DrawImGui(void);
	virtual void OnDrawImGui(void) {};
	void DrawImGuiHierarchy(void);
};

template<class Ty, class ...Args>
std::shared_ptr<Ty> Scene::SpawnObject(Args ...args)
{
	std::shared_ptr<Ty> object = std::make_shared<Ty>(args...);
	SpawnObject(object);
	return object;
}

template<typename CastTy>
std::shared_ptr<Object> Scene::FindObject(std::string name)
{
	for (std::shared_ptr<Object> Obj : Objects)
	{
		if (Obj->GetName() == name)
		{
			return std::dynamic_pointer_cast<CastTy>(Obj);
		}
	}
	return nullptr;
}
