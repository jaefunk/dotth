#ifndef __DOTTH_SHADER_HPP__
#define __DOTTH_SHADER_HPP__

#include "dotth.hpp"

/*
GL_FLOAT = 5126
GL_FLOAT_VEC2
GL_FLOAT_VEC3
GL_FLOAT_VEC4
GL_INT = 5124
GL_INT_VEC2 = 35667
GL_INT_VEC3 = 35668
GL_INT_VEC4 = 35669
GL_BOOL = 35670
GL_BOOL_VEC2 = 35671
GL_BOOL_VEC3 = 35672
GL_BOOL_VEC4 = 35673
GL_FLOAT_MAT2 = 35674
GL_FLOAT_MAT3 = 35675
GL_FLOAT_MAT4 = 35676
GL_SAMPLER_2D = 35678
GL_SAMPLER_CUBE = 35680
*/

//#define GL_SRC_COLOR 0x0300
//#define GL_ONE_MINUS_SRC_COLOR 0x0301
//#define GL_SRC_ALPHA 0x0302
//#define GL_ONE_MINUS_SRC_ALPHA 0x0303
//#define GL_DST_ALPHA 0x0304
//#define GL_ONE_MINUS_DST_ALPHA 0x0305
//#define GL_DST_COLOR 0x0306
//#define GL_ONE_MINUS_DST_COLOR 0x0307
//#define GL_SRC_ALPHA_SATURATE 0x0308
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

namespace dotth {
	
    class shader
    {
	private:
		friend class shader_manager;	
		struct render_parameter {
			int _location = 0;
			unsigned int _type = 0;
		};
		unsigned int _program = 0;
		std::map<std::string, render_parameter> _parameters;
        unsigned int _blend_src = 0;
		unsigned int _blend_dst = 0;
    public:
		const bool set_parameter(const char* name, const float& value)
		{
			auto iter = _parameters.find(name);
			if (iter == _parameters.end())
				return false;
			return true;
		}
		const unsigned int program() 
		{ 
			return _program; 
		}
		void bind(void) {
			glUseProgram(_program);
			glBlendFunc(_blend_src, _blend_dst);
		}
		void unbind(void) {
			glUseProgram(0);
		}
    };

	class shader_manager : public dotth::utility::singleton<shader_manager>
	{
	private:
		std::map<std::string, std::shared_ptr<dotth::shader>> shaders;
        std::map<std::string, GLenum> _blend_type = {
            { "GL_SRC_COLOR", GL_SRC_COLOR },
            { "GL_SRC_ALPHA", GL_SRC_ALPHA },
            { "GL_DST_ALPHA", GL_DST_ALPHA },
            { "GL_DST_COLOR", GL_DST_COLOR },
			{ "GL_SRC_ALPHA_SATURATE", GL_SRC_ALPHA_SATURATE },
			{ "GL_ONE_MINUS_SRC_COLOR", GL_ONE_MINUS_SRC_COLOR },
			{ "GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA },
			{ "GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA },
            { "GL_ONE_MINUS_DST_COLOR", GL_ONE_MINUS_DST_COLOR },
        };
	public:
		const bool load(const char* key, const char* file_path);
		const std::shared_ptr<dotth::shader> find(const char* key) {
			auto iter = shaders.find(key);
			if (iter != shaders.end())
				return iter->second;
			return nullptr;
		}
	};
};

#endif // __DOTTH_SHADER_HPP__
