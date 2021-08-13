#pragma once

#include "Object.h"
#include "Math/Math.h"

class Scene : public Base
{
	friend class Scenario;

private:
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void DrawImGui(void);
	virtual void Destroy(void);

public:
	virtual void OnInit(void);
	virtual void OnUpdate(void);
	virtual void OnDraw(void);
	virtual void OnDestroy(void);

private:
	std::list<std::shared_ptr<Object>> _Objects;

public:
	void SpawnObject(std::shared_ptr<Object> object);
	void RemoveObject(std::shared_ptr<Object> object);
	template <typename CastTy = Object>
	std::shared_ptr<Object> FindObject(std::string name)
	{
		for (std::shared_ptr<Object> Obj : _Objects)
		{
			if (Obj->Name() == name)
			{
				return std::dynamic_pointer_cast<CastTy>(Obj);
			}
		}
		return nullptr;
	}

public:	// about camera...
	void SetCameraPosition(const Float3& value);
	void SetCameraUp(const Float3& value);
	void SetCameraLookAt(const Float3& value);
	void SetCameraViewportSize(const int& width, const int& height);
	void SetCameraFrustumFieldOfView(const float& radian);
	void SetCameraFrustumNearFieldDistance(const float& value);
	void SetCameraFrustumFarFieldDistance(const float& value);

public:
	virtual void OnDrawImGui(void) {};
	void DrawImGuiHierarchy(void);
};
