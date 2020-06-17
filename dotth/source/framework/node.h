#pragma once

#include "framework/base.h"

template <class ty>
class node : public base, public std::enable_shared_from_this<ty>
{
private:
	std::weak_ptr<ty> _parent;
	std::list<std::shared_ptr<ty>> _children;

public:
	template <class target_type>
	std::weak_ptr<target_type> get_weak(void)
	{
		return std::dynamic_pointer_cast<target_type>(this->shared_from_this());
	}

	template <class parent_type = ty>
	std::shared_ptr<parent_type> get_parent(void)
	{
		if (std::shared_ptr<ty> sp = _parent.lock())
			return std::dynamic_pointer_cast<parent_type>(sp);
		return nullptr;
	}

	template <class predicate>
	std::shared_ptr<ty> find_by_func(predicate func) const
	{
		return const_cast<node*>(this)->find_by_func(func);
	}

	template <class predicate>
	std::shared_ptr<ty> find_by_func(predicate func)
	{
		for (auto& child : _children)
		{
			if (func(child) == true)
				return child;
			if (auto finded = child->find_by_func(func))
				return finded;
		}
		return nullptr;
	}

	template <class target_type = ty, class predicate>
	void foreach(predicate func) const
	{
		return const_cast<node*>(this)->foreach<target_type>(func);
	}
	template <class target_type = ty, class predicate>
	void foreach(predicate func)
	{
		std::for_each(std::begin(_children), std::end(_children), [func](typename decltype(_children)::value_type child) {
			if (std::shared_ptr<target_type> casted = std::dynamic_pointer_cast<target_type>(child))
				func(casted);
			child->foreach<target_type>(func);
		});
	}

	bool detach(std::shared_ptr<ty> target)
	{
		if (std::find(std::begin(_children), std::end(_children), target) != std::end(_children))
		{
			_children.remove(target);
			target->_parent.reset();
			return true;
		}

		for (std::shared_ptr<ty>& child : _children)
		{
			if (child->detach(target) == true)
				return true;
		}
		return false;
	}

	void attach(std::shared_ptr<ty> target)
	{
		target->leave();
		_children.push_back(target);
		target->_parent = this->shared_from_this();
	}

	void leave(void)
	{
		if (auto parent = get_parent())
			parent->detach(this->shared_from_this());
	}
};