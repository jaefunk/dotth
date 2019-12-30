#ifndef __DOTTH_MATERIAL_HPP__
#define __DOTTH_MATERIAL_HPP__

#include "resource.hpp"

namespace dotth {
	class material : public resource
	{
	private:
		vector3 _direction;
		float4 _diffuse;
		float4 _ambient;
		float4 _specular;
		float _shininess = 0.f;

	public:
		virtual ~material(void)
		{
			clear();
		}
		virtual void clear(void) override
		{
		}
		virtual bool load(const char* path) override
		{

		}
	};
};

#endif // __DOTTH_MATERIAL_HPP__
