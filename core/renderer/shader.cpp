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

#include "shader.hpp"
#include "platform/filesystem/path.hpp"

const bool dotth::shader_manager::load(const char* key, const char * file_path) {
	std::string strPath = dotth::path(file_path);
	// 쉐이더 코드를 파일에서 읽기
	std::string ShaderCode;
	std::ifstream ShaderStream(strPath.c_str(), std::ios::in);
	if (ShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << ShaderStream.rdbuf();
		ShaderCode = sstr.str();
		ShaderStream.close();
	}
	else {
		printf("파일 %s 를 읽을 수 없음. 정확한 디렉토리를 사용 중입니까 ? FAQ 를 우선 읽어보는 걸 잊지 마세요!\n", strPath.c_str());
		getchar();
		return false;
	}

	auto vertext_begin = ShaderCode.find("// vertex shader");
	auto fragment_begin = ShaderCode.find("// fragment shader");
	auto blender_begin = ShaderCode.find("// pixel blender");
	if (vertext_begin == std::string::npos || fragment_begin == std::string::npos || blender_begin == std::string::npos)
	{
		printf("파일 %s 를 읽을 수 없음. 정확한 디렉토리를 사용 중입니까 ? FAQ 를 우선 읽어보는 걸 잊지 마세요!\n", strPath.c_str());
		return false;
	}
	std::string vertext_shader = ShaderCode.substr(vertext_begin, fragment_begin - vertext_begin);
	std::string fragment_shader = ShaderCode.substr(fragment_begin, blender_begin - fragment_begin);
	std::string blender_type = ShaderCode.substr(blender_begin, ShaderCode.size() - blender_begin);

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// 버텍스 쉐이더를 컴파일
	printf("Compiling vertex shader : %s\n", strPath.c_str());
	char const * VertexSourcePointer = vertext_shader.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// 버텍스 쉐이더를 검사
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
	
	// 프래그먼트 쉐이더를 컴파일
	printf("Compiling fragment shader : %s\n", strPath.c_str());
	char const * FragmentSourcePointer = fragment_shader.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// 프래그먼트 쉐이더를 검사
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// 프로그램에 링크
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// 프로그램 검사
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	std::shared_ptr<dotth::shader> s = std::make_shared<dotth::shader>();
	s->_program = ProgramID;
	shaders.insert({ key, s });

	{
		GLint count;
		GLint size; // size of the variable
		GLenum type; // type of the variable (float, vec3 or mat4, etc)
		const GLsizei bufSize = 32; // maximum name length
		GLchar name[bufSize]; // variable name in GLSL
		GLsizei length; // name length
		glGetProgramiv(ProgramID, GL_ACTIVE_ATTRIBUTES, &count);
		for (auto i = 0; i < count; ++i)
		{
			glGetActiveAttrib(ProgramID, (GLuint)i, bufSize, &length, &size, &type, name);
			shader::render_parameter rp;
			rp._location = glGetAttribLocation(ProgramID, name);
			rp._type = type;
			s->_parameters.insert({ name, rp });
		}
		glGetProgramiv(ProgramID, GL_ACTIVE_UNIFORMS, &count);
		for (auto i = 0; i < count; i++)
		{
			glGetActiveUniform(ProgramID, (GLuint)i, bufSize, &length, &size, &type, name);
			shader::render_parameter rp;
			rp._location = glGetAttribLocation(ProgramID, name);
			rp._type = type;
			s->_parameters.insert({ name, rp });
		}
	}
    
    auto src = blender_type.find("src:");
    auto dst = blender_type.find("dst:");
    if(src != std::string::npos && dst != std::string::npos)
    {
        std::string strSrc = blender_type.substr(src, blender_type.find('\n'));
        strSrc = strSrc.substr(strSrc.find(":") + 1, strSrc.size());
		s->_blend_src = _blend_type[strSrc.c_str()];
        std::string strDst = blender_type.substr(dst, blender_type.size());
        strDst = strDst.substr(0, strDst.find('\n'));
        strDst = strDst.substr(strDst.find(":") + 1, strDst.size());
		s->_blend_dst = _blend_type[strDst.c_str()];
    }    

	return true;
}
