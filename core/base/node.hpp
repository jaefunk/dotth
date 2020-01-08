#ifndef __DOTTH_NODE_HPP__
#define __DOTTH_NODE_HPP__

#include "base.hpp"

namespace dotth {
	template <
		typename ty,
		typename weaked_type = std::weak_ptr<ty>,
		typename shared_type = std::shared_ptr<ty>,
		typename shared_container = std::list<shared_type>
	>
		class node : public base, public std::enable_shared_from_this<ty>
	{
	public:
		node(void)
		{
			static_assert(std::is_base_of<node, ty>::value,
				"type parameter of this class must derive from <node>");
		}

	protected:
		weaked_type _parent;
		shared_container _children;

	public:
		template <class dst, class pred>
		void foreach(pred func)
		{
			for (auto child : _children)
			{
				if (auto target = std::dynamic_pointer_cast<dst>(child))
				{
					func(target);
				}
			}
		}
		const bool is_root(void)
		{
			return _parent.expired();
		}
		const shared_type root(void)
		{
			if (is_root())
			{
				return this->shared_from_this();
			}
			return parent()->root();
		}
		const bool family(const shared_type& target)
		{
			if (is_root())
			{
				return false;
			}
			return std::find_if(std::begin(_children), std::end(_children), [target](const shared_type& child) {
				return child->family(target);
			}) != std::end(_children);
		}

		template <class dst = ty>
		std::shared_ptr<dst> parent(void)
		{
			return std::dynamic_pointer_cast<dst>(_parent.lock());
		}
		const bool equal(const shared_type& target)
		{
			return serial() == target->serial();
		}

	public:
		void attach(const shared_type& target)
		{
			assert(target->parent() == nullptr);
			assert(family(target) == false);
			assert(equal(target) == false);
			target->_parent = this->shared_from_this();
			_children.push_back(target);
		}
		void independence(void)
		{
			if (is_root())
			{
				return;
			}
			parent()->detach(this->shared_from_this());
		}

		template <class func>
		void detach(func pred)
		{
			auto iter = std::begin(_children);
			auto end = std::end(_children);
			while (end != iter)
			{
				const shared_type& child = *iter;
				if (pred(child) == true)
				{
					child->_parent.reset();
					iter = _children.erase(iter);
				}
				else
				{
					child->detach(pred);
					++iter;
				}
			}
		}
		void detach(const shared_type& target)
		{
			detach([target](const shared_type& child) {
				return child->equal(target);
			});
		}

		template <class dst = ty, class func>
		std::shared_ptr<dst> find(func pred)
		{
			auto iter = std::begin(_children);
			auto end = std::end(_children);
			while (end != iter)
			{
				const shared_type& child = *iter;
				if (pred(child) == true)
				{
					return std::dynamic_pointer_cast<dst>(child);
				}
				else
				{
					child->find(pred), ++iter;
				}
			}
			return nullptr;
		}
	};
};

#endif // __DOTTH_NODE_HPP__
