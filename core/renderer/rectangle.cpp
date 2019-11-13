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

#include "rectangle.hpp"
#include "renderer.hpp"

void dotth::rectangle::init1(void)
{

	_command._triangle.v.resize(4);
	_command._triangle.v[0] = xyz(-10.f, -0.5f, 10.f);
	_command._triangle.v[1] = xyz(10.f, -0.5f, 10.f);
	_command._triangle.v[2] = xyz(-10.f, -0.5f, -10.f);
	_command._triangle.v[3] = xyz(10.f, -0.5f, -10.f);

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
	_command._triangle.v.clear();


	// right
	_command._triangle.v.push_back(xyz(0.5f, 0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(0.5f, 0.5f, 0.5f));
	_command._triangle.v.push_back(xyz(0.5f, -0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(0.5f, -0.5f, 0.5f));
	// back
	_command._triangle.v.push_back(xyz(-0.5f, 0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(0.5f, 0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(-0.5f, -0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(0.5f, -0.5f, -0.5f));
	// top
	_command._triangle.v.push_back(xyz(-0.5f, 0.5f, 0.5f));
	_command._triangle.v.push_back(xyz(0.5f, 0.5f, 0.5f));
	_command._triangle.v.push_back(xyz(-0.5f, 0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(0.5f, 0.5f, -0.5f));
	// down
	_command._triangle.v.push_back(xyz(-0.5f, -0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(0.5f, -0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(-0.5f, -0.5f, 0.5f));
	_command._triangle.v.push_back(xyz(0.5f, -0.5f, 0.5f));
	// left
	_command._triangle.v.push_back(xyz(-0.5f, 0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(-0.5f, 0.5f, 0.5f));
	_command._triangle.v.push_back(xyz(-0.5f, -0.5f, -0.5f));
	_command._triangle.v.push_back(xyz(-0.5f, -0.5f, 0.5f));
	// front
	_command._triangle.v.push_back(xyz(-0.5f, 0.5f, 0.5f));
	_command._triangle.v.push_back(xyz(0.5f, 0.5f, 0.5f));
	_command._triangle.v.push_back(xyz(-0.5f, -0.5f, 0.5f));
	_command._triangle.v.push_back(xyz(0.5f, -0.5f, 0.5f));

	_command._triangle.u.clear();
	for (auto i = 0; i < 6; ++i)
	{
		_command._triangle.u.push_back(uv(0.f, 0.f));
		_command._triangle.u.push_back(uv(1.f, 0.f));
		_command._triangle.u.push_back(uv(0.f, 1.f));
		_command._triangle.u.push_back(uv(1.f, 1.f));
	}

	_command._triangle.i.clear();
	for (auto i = 0; i < 6; ++i)
	{
		_command._triangle.i.push_back(0 + 4 * i);
		_command._triangle.i.push_back(1 + 4 * i);
		_command._triangle.i.push_back(2 + 4 * i);
		_command._triangle.i.push_back(1 + 4 * i);
		_command._triangle.i.push_back(3 + 4 * i);
		_command._triangle.i.push_back(2 + 4 * i);
	}

	_command._triangle.c.clear();
	for (std::size_t i = 0; i < _command._triangle.v.size(); ++i)
		_command._triangle.c.push_back(rgba());
}

void dotth::rectangle::draw(int flags) {
	if (_command._triangle.v.empty())
		return;
	renderer::instance()->push(&_command);
}
