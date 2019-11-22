/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2019 jaefunk <https://github.com/jaefunk/dotth>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
namespace dotth {
    class shader
    {
	private:
		friend class shader_manager;	
		unsigned int _program = 0;
		std::map<const char*, int> _uniforms;
		std::map<const char*, int> _attributes;
    public:
		const bool set_uniform(const char* name, const float& value)
		{
			auto iter = _uniforms.find(name);
			if (iter == _uniforms.end())
				return false;
			auto location = glGetAttribLocation(_program, name);
			glEnableVertexAttribArray(location);
			//glEnableVertexAttrib
			glVertexAttrib1f(location, value);
			return true;
		}
		const bool set_attribute(const char* name, const float& value)
		{
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
		}
		const unsigned int program() 
		{ 
			return _program; 
		}
    };

	class shader_manager : public dotth::utility::singleton<shader_manager>
	{
	private:
		std::map<std::string, dotth::shader> shaders;
	public:
		const bool load(std::string key, const char* file_path);
		const dotth::shader find(std::string key) {
			auto iter = shaders.find(key);
			if (iter != shaders.end())
				return iter->second;
			return dotth::shader();
		}
	};
};

#endif // __DOTTH_SHADER_HPP__
