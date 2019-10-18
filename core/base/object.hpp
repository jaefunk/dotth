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

#ifndef __DOTTH_OBJECT_HPP__
#define __DOTTH_OBJECT_HPP__

#include "utility.hpp"
#include "node.hpp"
namespace dotth {
    class object : public node<object>
    {
    private:
        std::string _name;
        float _timescale = 1.f;
        
    public:
        object(void) = default;
        object(std::string name) : _name(name) { };
        
    public:
		void set_timescale(const float & scale);
		const float& local_timescale(void);
		const float world_timescale(void);
        
    public:
		virtual bool init(void);
		virtual void update(void) final;
		virtual void draw(void) final;
        
    protected:
        virtual void update(float delta) {};
        virtual void draw(/*Renderer *renderer, const Mat4& transform, */int flags) {};
    };
};

#endif // __DOTTH_OBJECT_HPP__