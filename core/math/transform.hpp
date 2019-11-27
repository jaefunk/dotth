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

#ifndef __DOTTH_TRANSFORM_HPP__
#define __DOTTH_TRANSFORM_HPP__

#include "vector.hpp"
#include "matrix.hpp"

namespace dotth {
    class transform {
    private:
		vector3 _pos = { 0.f, 0.f, 0.f };
		vector3 _scl = { 1.f, 1.f, 1.f };
        vector3 _rot = { 0.f, 0.f, 0.f };
        matrix4 _matrix;
    
    public: // set
		void position(const float& x, const float& y, const float& z) { _pos.x = x; _pos.y = y; _pos.z = z; }
        void position(const vector3& v) { position(v.x, v.y, v.z); }
		void position_x(const float& v) { _pos.x = v; }
		void position_y(const float& v) { _pos.y = v; }
		void position_z(const float& v) { _pos.z = v; }
		
		void scale(const float& x, const float& y, const float& z) { _scl.x = x; _scl.y = y; _scl.z = z; }
		void scale(const vector3& v) { scale(v.x, v.y, v.z); }
		void scale_x(const float& v) { _scl.x = v; }
		void scale_y(const float& v) { _scl.y = v; }
		void scale_z(const float& v) { _scl.z = v; }

		void rotate(const float& x, const float& y, const float& z) { _rot.x = x; _rot.y = y; _rot.z = z; }
		void rotate(const vector3& v) { rotate(v.x, v.y, v.z); }
		void rotate_x(const float& v) { _rot.x = v; }
		void rotate_y(const float& v) { _rot.y = v; }
		void rotate_z(const float& v) { _rot.z = v; }
        
        
    public: // get
        const vector3& position(void) { return _pos; }
        const vector3& scale(void) { return _scl; }
        const vector3& rotation(void) { return _rot; }
        const matrix4& matrix(void) { return _matrix; }
    };
};

#endif // __DOTTH_TRANSFORM_HPP__
