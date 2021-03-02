#pragma once

#include "Framework/Base.h"

template <class Ty>
class Node : public Base, public std::enable_shared_from_this<Ty>
{
private:
	std::weak_ptr<Ty> _Parent;
	std::list<std::shared_ptr<Ty>> _Children;

public:
	template <class target_type>
	std::weak_ptr<target_type> Weak(void)
	{
		return std::dynamic_pointer_cast<target_type>(this->shared_from_this());
	}

	template <class parent_type = Ty>
	std::shared_ptr<parent_type> Parent(void)
	{
		if (std::shared_ptr<Ty> sp = _Parent.lock())
			return std::dynamic_pointer_cast<parent_type>(sp);
		return nullptr;
	}

	template <class target_type = Ty, class predicate>
	void Foreach(predicate func)
	{
		for (std::shared_ptr<Ty> elm : _Children)
		{
			if (std::shared_ptr<target_type> casted = std::dynamic_pointer_cast<target_type>(elm))
			{
				func(casted);
			}
			elm->Foreach<target_type>(func);
		}
	}

	bool Detach(std::shared_ptr<Ty> target)
	{
		if (std::find(std::begin(_Children), std::end(_Children), target) != std::end(_Children))
		{
			_Children.remove(target);
			target->_Parent.reset();
			return true;
		}

		for (std::shared_ptr<Ty>& child : _Children)
		{
			if (child->Detach(target) == true)
				return true;
		}
		return false;
	}

	void Attach(std::shared_ptr<Ty> target)
	{
		target->Leave();
		_Children.push_back(target);
		target->_Parent = this->shared_from_this();
	}

	void Leave(void)
	{
		if (auto parent = Parent())
			parent->Detach(this->shared_from_this());
	}
};