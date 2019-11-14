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
#ifndef __DOTTH_SCENE_HPP__
#define __DOTTH_SCENE_HPP__

#include "dotth.hpp"
#include "base/object.hpp"

namespace dotth {
    class scene : public object
    {
    public:
        virtual void init(json data = json()) {};
    protected:
		bool loadview(std::string path);
    };
    
    class scene_manager : public utility::singleton<scene_manager>
    {
    private:
        bool _scene_changed = false;
        json _scene_data;
        std::stack<std::string> _stack;
        std::unordered_map<std::string, std::function<std::shared_ptr<scene>(void)>> _signed_scene;
        std::shared_ptr<scene> _current;
        
    public:
        template <
        typename ty,
        typename = typename std::enable_if<std::is_base_of<scene, ty>::value, ty>::type
        >
        void assign_scene(const std::string& key)
        {
            //static_assert(std::is_base_of<ty, scene>::value, "ty must be inherited by <scene>");
            _signed_scene.insert({ key, []() { return std::make_shared<ty>(); } });
        }
        
        void push(std::string key, json data = json())
        {
            _stack.push(key);
            _scene_changed = true;
            _scene_data = data;
        }
        
        void pop(json data = json())
        {
            if (_stack.size() <= 1)
                return;
            _stack.pop();
            _scene_changed = true;
            _scene_data = data;
        }
        
        void apply_new_scene(void)
        {
            if (_stack.empty() == true)
                return;
            if (_scene_changed == false)
                return;
            _scene_changed = false;
            auto iterator = _signed_scene.find(_stack.top());
            if (iterator == std::end(_signed_scene))
                return;
            _current = iterator->second();
            _current->init(_scene_data);
            _scene_data = json();
        }
        
    public:
        void update(void) {
            apply_new_scene();
            if (_current == nullptr)
                return;
            _current->update();
        }
        void draw(void) {
            if (_current == nullptr)
                return;
            _current->draw();
        }
    };
};




#endif // __DOTTH_SCENE_HPP__
