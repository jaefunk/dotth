#ifndef __DOTTH_SHARED_NODE__
#define __DOTTH_SHARED_NODE__

#include "base.h"
#include "node.h"
namespace dotth {
	template <typename ty = base>
	class shared_node : public base, public std::enable_shared_from_this<ty>
	{
	private:
		std::weak_ptr<ty> _parent;
		std::list<std::shared_ptr<ty>> _children;

	public:
		const bool is_root(void) const
		{
			return _parent.expired();
		}

		const std::shared_ptr<ty>& get_root(void) const
		{
			if (is_root())
			{
				return this->shared_from_this();
			}
			return get_parent()->get_root();
		}

		template <class dst = ty>
		const std::shared_ptr<dst> get_parent(void) const
		{
			return std::dynamic_pointer_cast<dst>(_parent.lock());
		}

		template <class pred>
		void loop_for_children(pred func)
		{
			std::for_each(std::begin(_children), std::end(_children), [func](auto& child) {
				func(child);
				child->loop_for_children(func);
			});
		}

		const bool attach(const std::shared_ptr<ty>& target)
		{
			if (target->get_parent() != nullptr)
			{
				return false;
			}
			if (is_hierarchy(target) == true)
			{
				return false;
			}
			if (this->shared_from_this() == target)
			{
				return false;
			}
			target->_parent = this->shared_from_this();
			_children.push_back(target);
			return true;
		}

		const bool is_hierarchy(const std::shared_ptr<ty>& target) const
		{
			return get_root() == target->get_root();
		}

		template <class dst = ty, class pred>
		std::shared_ptr<dst> find_child_depth(pred func)
		{
			auto iter = std::find_if(std::begin(_children), std::end(_children), func);
			if (iter == std::end(_children))
			{
				return find_child_depth(func);
			}
			return std::dynamic_pointer_cast<dst>(*iter);
		}

		//template <class dst = ty, class pred>
		//std::shared_ptr<dst> find_child_breadth(pred func)
		//{
		//	return nullptr;
		//}

		const bool leave(void)
		{
			if (is_root())
			{
				return false;
			}
			get_parent()->detach(this->shared_from_this());
			return true;
		}

		void detach(std::function<bool(const std::shared_ptr<ty>&)> pred)
		{
			auto iter = std::begin(_children);
			auto end = std::end(_children);
			while (end != iter)
			{
				const std::shared_ptr<ty>& child = *iter;
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
		
		void detach(const std::shared_ptr<ty>& target)
		{
			detach([target](const std::shared_ptr<ty>& child) {
				return target == child;
			});
		}
	};
};

#endif // __DOTTH_NODE__
