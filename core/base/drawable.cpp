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

#include "drawable.hpp"

#include "../external/stb/image/stb_image.h"

void dotth::rectangle::init1(void)
{
	_command._triangle.v.resize(4);
	_command._triangle.v[0] = xyz(-0.5f, 0.5f, 0.f);
	_command._triangle.v[1] = xyz(0.5f, 0.5f, 0.f);
	_command._triangle.v[2] = xyz(-0.5f, -0.5f, 0.f);
	_command._triangle.v[3] = xyz(0.5f, -0.5f, 0.f);

	_command._triangle.c.resize(4);
	_command._triangle.c[0] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[1] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[2] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[3] = rgba(1.f, 1.f, 1.f, 1.f);
    
    _command._triangle.u.resize(4);
    _command._triangle.u[0] = uv(0.f, 1.f);
    _command._triangle.u[1] = uv(1.f, 1.f);
    _command._triangle.u[2] = uv(0.f, 0.f);
    _command._triangle.u[3] = uv(1.f, 0.f);

	_command._triangle.i.resize(6);
	_command._triangle.i[0] = 0;
	_command._triangle.i[1] = 1;
	_command._triangle.i[2] = 2;
	_command._triangle.i[3] = 1;
	_command._triangle.i[4] = 3;
	_command._triangle.i[5] = 2;
}

void dotth::rectangle::init2(void)
{
	_command._triangle.v.resize(8);
	_command._triangle.v[0] = xyz(-0.5f, 0.5f, -0.5f);
	_command._triangle.v[1] = xyz(0.5f, 0.5f, -0.5f);
	_command._triangle.v[2] = xyz(-0.5f, -0.5f, -0.5f);
	_command._triangle.v[3] = xyz(0.5f, -0.5f, -0.5f);
	_command._triangle.v[4] = xyz(-0.5f, 0.5f, 0.5f);
	_command._triangle.v[5] = xyz(0.5f, 0.5f, 0.5f);
	_command._triangle.v[6] = xyz(-0.5f, -0.5f, 0.5f);
	_command._triangle.v[7] = xyz(0.5f, -0.5f, 0.5f);

	_command._triangle.u.resize(4);
	_command._triangle.u[0] = uv(0.f, 1.f);
	_command._triangle.u[1] = uv(1.f, 1.f);
	_command._triangle.u[2] = uv(0.f, 0.f);
	_command._triangle.u[3] = uv(1.f, 0.f);

	_command._triangle.c.resize(8);
	_command._triangle.c[0] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[1] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[2] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[3] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[4] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[5] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[6] = rgba(1.f, 1.f, 1.f, 1.f);
	_command._triangle.c[7] = rgba(1.f, 1.f, 1.f, 1.f);

	_command._triangle.i.resize(6);
	// f
	_command._triangle.i[0] = 0;
	_command._triangle.i[1] = 1;
	_command._triangle.i[2] = 2;
	_command._triangle.i[3] = 1;
	_command._triangle.i[4] = 3;
	_command._triangle.i[5] = 2;
	//// b
	//_command._triangle.i[6]  = 4;
	//_command._triangle.i[7]  = 5;
	//_command._triangle.i[8]  = 6;
	//_command._triangle.i[9]  = 5;
	//_command._triangle.i[10] = 7;
	//_command._triangle.i[11] = 6;
	//// t
	//_command._triangle.i[12] = 4;
	//_command._triangle.i[13] = 5;
	//_command._triangle.i[14] = 0;
	//_command._triangle.i[15] = 5;
	//_command._triangle.i[16] = 1;
	//_command._triangle.i[17] = 0;
	//// d
	//_command._triangle.i[18] = 6;
	//_command._triangle.i[19] = 7;
	//_command._triangle.i[20] = 2;
	//_command._triangle.i[21] = 7;
	//_command._triangle.i[22] = 3;
	//_command._triangle.i[23] = 2;
	//// l
	//_command._triangle.i[24] = 4;
	//_command._triangle.i[25] = 0;
	//_command._triangle.i[26] = 6;
	//_command._triangle.i[27] = 0;
	//_command._triangle.i[28] = 2;
	//_command._triangle.i[29] = 6;
	//// r
	//_command._triangle.i[30] = 1;
	//_command._triangle.i[31] = 5;
	//_command._triangle.i[32] = 3;
	//_command._triangle.i[33] = 5;
	//_command._triangle.i[34] = 7;
	//_command._triangle.i[35] = 3;
}

void dotth::rectangle::draw(const matrix4 & transform, int flags) {
	if (_command._triangle.v.empty())
		return;
	renderer::instance()->push(&_command);
}
