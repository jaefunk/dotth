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

#include "dotth.hpp"
#include "vector.hpp"
#include "matrix.hpp"

namespace dotth {
    class transform {
    private:
        vector4 _position;
        vector4 _scale;
        vector4 _rotation;
        matrix4 _localmatrix;
        matrix4 _worldmatrix;
        matrix4 _inversematrix;
        
    private:
        void calculate_local(void) {
            
        }
        
    public:
        void update(const matrix4& parentworld) {
            calculate_local();
            //_worldmatrix = _worldmatrix * parentworld;
        }
    
    public: // set
        void set_position(const vector4& v) {
            set_position(v.x, v.y, v.z);
        }
        void set_position(const float& x, const float& y, const float& z) {
            _position.x = x; _position.y = y; _position.z = z;
        }
        void set_scale(const vector4& v) {
            set_scale(v.x, v.y, v.z);
        }
        void set_scale(const float& x, const float& y, const float& z) {
            _scale.x = x; _scale.y = y; _scale.z = z;
        }
        void set_rotation(const vector4& v) {
            set_rotation(v.x, v.y, v.z);
        }
        void set_rotation(const float& x, const float& y, const float& z) {
            _rotation.x = x; _rotation.y = y; _rotation.z = z;
        }
    public: // get
        const vector4& position(void) { return _position; }
        const vector4& scale(void) { return _scale; }
        const vector4& rotation(void) { return _rotation; }
        const matrix4& localmatrix(void) { return _localmatrix; }
        const matrix4& worldmatrix(void) { return _worldmatrix; }
    };
};

#endif // __DOTTH_TRANSFORM_HPP__
