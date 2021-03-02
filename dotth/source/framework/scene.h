#pragma once

#include "Framework/Base.h"
#include "Framework/Object.h"

class Scene : public Base
{
	friend class Scenario;
private:
	std::shared_ptr<Object> _Root{ new Object };
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Destroy(void);

public:
	const std::shared_ptr<Object>& Root(void);

public:
	virtual void OnInit(void);
	virtual void OnUpdate(void);
	virtual void OnDraw(void);
	virtual void OnDestroy(void);
};