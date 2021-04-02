#pragma once

#include "Base.h"

class Object;
class Component : public Base
{
private:
	mutable std::weak_ptr<Object> _Owner;

public:
	void SetOwner(const std::shared_ptr<Object> Owner)
	{
		_Owner = Owner;
	}
	
	template <typename CastTy = Object>
	const std::shared_ptr<CastTy> GetOwner(void) const
	{
		if (_Owner.expired())
			return nullptr;
		return std::dynamic_pointer_cast<CastTy>(_Owner.lock());
	}

public:
	virtual void OnInit(void);
	virtual void OnUpdate(void);
	virtual void OnDraw(void);
	virtual void OnDestroy(void);
};
