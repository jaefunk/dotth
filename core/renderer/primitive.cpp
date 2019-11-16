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

#include "primitive.hpp"
#include "renderer.hpp"

void dotth::rectangle::init(void)
{
    _command._triangle.v.clear();
	_command._triangle.v.push_back(xyz(-0.5f, 0.5f, 0.f));
    _command._triangle.v.push_back(xyz(0.5f, 0.5f, 0.f));
    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, 0.f));
    _command._triangle.v.push_back(xyz(0.5f, -0.5f, 0.f));

    _command._triangle.c.clear();
	_command._triangle.c.push_back(rgba(1.f, 1.f, 1.f, 1.f));
	_command._triangle.c.push_back(rgba(1.f, 1.f, 1.f, 1.f));
    _command._triangle.c.push_back(rgba(1.f, 1.f, 1.f, 1.f));
    _command._triangle.c.push_back(rgba(1.f, 1.f, 1.f, 1.f));

    _command._triangle.u.clear();
	_command._triangle.u.push_back(uv(0.f, 1.f));
    _command._triangle.u.push_back(uv(1.f, 1.f));
    _command._triangle.u.push_back(uv(0.f, 0.f));
    _command._triangle.u.push_back(uv(1.f, 0.f));

    _command._triangle.i.clear();
    _command._triangle.i = { 0, 1, 2, 1, 3, 2 };
}

void dotth::rectangle::draw(int flags) {
	if (_command._triangle.v.empty())
		return;
	renderer::instance()->push(&_command);
}

void dotth::cube::init(void)
{
    _command._triangle.v.clear();
    _command._triangle.v.push_back(xyz(0.5f, 0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(0.5f, 0.5f, 0.5f));
    _command._triangle.v.push_back(xyz(0.5f, -0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(0.5f, -0.5f, 0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(0.5f, 0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(0.5f, -0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, 0.5f));
    _command._triangle.v.push_back(xyz(0.5f, 0.5f, 0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(0.5f, 0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(0.5f, -0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, 0.5f));
    _command._triangle.v.push_back(xyz(0.5f, -0.5f, 0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, 0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, -0.5f));
    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, 0.5f));
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

void dotth::cube::draw(int flags) {
    if (_command._triangle.v.empty())
        return;
    renderer::instance()->push(&_command);
}
