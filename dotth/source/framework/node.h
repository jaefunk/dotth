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
	std::weak_ptr<target_type> GetWeak(void)
	{
		return std::dynamic_pointer_cast<target_type>(this->shared_from_this());
	}

	template <class parent_type = Ty>
	std::shared_ptr<parent_type> GetParent(void)
	{
		if (std::shared_ptr<Ty> sp = _Parent.lock())
			return std::dynamic_pointer_cast<parent_type>(sp);
		return nullptr;
	}

	template <class target_type = Ty, class predicate>
	void Foreach(predicate func) const
	{
		return const_cast<Node*>(this)->Foreach<target_type>(func);
	}
	template <class target_type = Ty, class predicate>
	void Foreach(predicate func)
	{
		std::for_each(std::begin(_Children), std::end(_Children),
			[func](typename decltype(_Children)::value_type child) {
			if (std::shared_ptr<target_type> casted = std::dynamic_pointer_cast<target_type>(child))
				func(casted);
			child->template Foreach<target_type>(func);
		});
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
		if (auto parent = GetParent())
			parent->Detach(this->shared_from_this());
	}

	template <class predicate>
	std::shared_ptr<Ty> FindByFunction(predicate func) const
	{
		return const_cast<Node*>(this)->FindByFunction(func);
	}

	template <class predicate>
	std::shared_ptr<Ty> FindByFunction(predicate func)
	{
		for (auto& child : _Children)
		{
			if (func(child) == true)
				return child;
			if (auto finded = child->FindByFunction(func))
				return finded;
		}
		return nullptr;
	}

	template <class CastTy = Ty>
	std::shared_ptr<CastTy> FindBySerial(unsigned int serial)
	{
		auto finded = FindByFunction([serial](std::shared_ptr<CastTy> child) {
			return child->Serial() == serial;
		});
		return std::dynamic_pointer_cast<CastTy>(finded);
	}

	template <class CastTy = Ty>
	std::shared_ptr<Ty> FindByName(const std::string& name)
	{
		auto finded = FindByFunction([name](std::shared_ptr<CastTy> child) {
			return child->GetName() == name;
		});
		return std::dynamic_pointer_cast<CastTy>(finded);
	}
};