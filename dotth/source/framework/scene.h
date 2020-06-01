#ifndef __DOTTH_SCENE__
#define __DOTTH_SCENE__

#include "framework/object.h"
#include "utility/utility.h"

namespace dotth 
{
    class scene : public object
    {
    protected:
		bool loadview(const std::string& path);
    };
    
    class scenario
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
            _current->init();
            _scene_data = json();
        }
        
    public:
		void update(void)
		{
			apply_new_scene();
			if (_current == nullptr)
				return;
			_current->update();
		}
    };
};

#endif // __DOTTH_SCENE__
