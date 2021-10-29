#pragma once

#include "Base.h"

template <class Ty>
class Node : public Base, public std::enable_shared_from_this<Ty>
{
protected:
	std::weak_ptr<Ty> Parent;
	std::list<std::shared_ptr<Ty>> Children;

public:
	bool IsRoot(void)
	{
		return Parent.expired();
	}

	template <class CastTy = Ty>
	std::shared_ptr<CastTy> GetRoot(void)
	{
		return IsRoot() ? 
			std::dynamic_pointer_cast<CastTy>(this->shared_from_this()) : 
			GetParent<CastTy>();
	}

	template <class CastTy = Ty>
	std::shared_ptr<CastTy> GetParent(void)
	{
		if (std::shared_ptr<CastTy> sp = std::dynamic_pointer_cast<CastTy>(Parent.lock()))
			return std::dynamic_pointer_cast<CastTy>(sp);
		return nullptr;
	}

	unsigned int GetChildrenCount(void)
	{
		return static_cast<unsigned int>(Children.size());
	}

	std::list<std::shared_ptr<Ty>>& GetChildren(void)
	{
		return Children;
	}

	void Attach(std::shared_ptr<Ty> target)
	{
		target->Leave();
		Children.push_back(target);
		target->Parent = this->shared_from_this();
	}	

	void Leave(void)
	{
		if (std::shared_ptr<Ty> parent = GetParent())
		{
			parent->GetChildren().remove(this->shared_from_this());
		}
		Parent.reset();
	}

	template <class CastTy>
	std::weak_ptr<CastTy> GetWeak(void)
	{
		return std::dynamic_pointer_cast<CastTy>(this->shared_from_this());
	}

	template <class CastTy = Ty, class Pred>
	void Foreach(Pred pred, bool recursive = true)
	{
		for (std::shared_ptr<Ty> Child : Children)
		{
			if (std::shared_ptr<CastTy> Cast = std::dynamic_pointer_cast<CastTy>(Child))
				pred(Cast);
			if (recursive == true)
			{
				Child->Foreach<CastTy>(pred, recursive);
			}
		}
	}
};