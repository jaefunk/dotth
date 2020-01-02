#ifndef __DOTTH_MESH_HPP__
#define __DOTTH_MESH_HPP__

#include "resource.hpp"

namespace dotth {
	class mesh : public dotth::resource {
		virtual void clear(void) override;
		
		virtual bool load(const char* path) override;
	};
};

#endif // __DOTTH_MESH_HPP__
