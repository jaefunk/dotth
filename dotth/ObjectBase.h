#pragma once

#include "Node.h"

class ObjectBase : public Node<ObjectBase>
{
private:
	std::set<std::string> Flags;

public:
	void AddFlag(std::string flag);
	bool HasFlag(std::string flag);
	void RemoveFlag(std::string flag);
	void ClearFlag(void);
};