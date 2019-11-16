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

#ifndef __DOTTH_TEXTURE_HPP__
#define __DOTTH_TEXTURE_HPP__

#include "dotth.hpp"
#include "base/resource.hpp"

namespace dotth {
	class texture : public dotth::resource {
    private:
        int _width = 0;
        int _height = 0;
        int _comp = 0;
        unsigned int _texture_id = 0;
        unsigned char* _data = nullptr;
        std::string _res_name;
    public:
        virtual ~texture(void) {
            clear();
        }
        virtual void clear(void) {
            if (_data != nullptr)
                stbi_image_free(_data);
            _res_name = "";
            _width = _height = _comp = _texture_id = 0;
        }
        virtual void load(const char* path) {
            _res_name = path;
            stbi_set_flip_vertically_on_load(true);
            _data = stbi_load(dotth::path(path).c_str(), &_width, &_height, &_comp, 0);
            _texture_id = initGL(_width, _height, GL_RGB, GL_RGBA, GL_UNSIGNED_BYTE, _data);
        }
    public:
        const int& width(void) {
            return _width;
        }
        const int& height(void) {
            return _height;
        }
        const int& comp(void) {
            return _comp;
        }
        const unsigned int& texture_id(void) {
            return _texture_id;
        }
        const unsigned char* data(void) {
            return _data;
        }
        void bind(void) {
            glBindTexture(GL_TEXTURE_2D, _texture_id);
        }
        void unbind(void) {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
    private:
        const unsigned int initGL(int width, int height, GLenum internal_format, GLenum format, GLenum type, unsigned char* data)
        {
            unsigned int texture = 0;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, type, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            return texture;
        }
	};

};

#endif // __DOTTH_TEXTURE_HPP__
