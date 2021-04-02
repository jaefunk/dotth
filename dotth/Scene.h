#pragma once

#include "Base.h"
#include "Object.h"

class Scene : public Base
{
	friend class Scenario;

private:
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Destroy(void);

public:
	virtual void OnInit(void);
	virtual void OnUpdate(void);
	virtual void OnDraw(void);
	virtual void OnDestroy(void);

private:
	std::list<std::shared_ptr<Object>> _Objects;

public:
	void AddObject(std::shared_ptr<Object> object)
	{
		for (std::shared_ptr<Object> Obj : _Objects)
		{
			if (object->Serial() == Obj->Serial())
			{
				return;
			}
		}
		_Objects.push_back(object);
	}
	void RemoveObject(std::shared_ptr<Object> object)
	{
		_Objects.remove(object);
	}
	
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
};
