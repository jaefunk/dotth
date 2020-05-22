#pragma once

#include "node.h"

namespace dotth {
	
	class object : public node<object>
	{
	private:
		std::string _name;
	public:
		void set_name(const char* name) 
		{
			_name = name;
		}
	public:
		template <class ty = object>
		std::shared_ptr<ty> find_by_name(const char* name)
		{
			auto finded = find_by_func([name](std::shared_ptr<object> child) {
				return child->_name.c_str() == name;
			});
			return std::dynamic_pointer_cast<ty>(finded);
		}

	public:
		virtual void init(void) final;
		virtual void update(void) final;

	protected:
		virtual void on_init(void) {};
		virtual void on_update(const float& delta) {};
	};
};