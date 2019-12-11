#ifndef __DOTTH_OBJECT_HPP__
#define __DOTTH_OBJECT_HPP__

#include "node.hpp"
#include "math/transform.hpp"

namespace dotth {
    class object : public node<object>
    {
    private:
		struct {
			bool visible = true;
			bool active = true;
			bool alive = true;
		} flags;
        std::string _name;
        float _timescale = 1.f;
        
    public:
        object(void) = default;
        object(std::string name) : _name(name) { };
		transform2d trans2d;
		transform3d trans3d;
        
    public:
		void set_timescale(const float & scale);
		const float& local_timescale(void);
		const float world_timescale(void);
        
    public:
		virtual void init(void) {};
		virtual void update(void) final;
		virtual void push_render_queue(void) final;
        
    protected:
		virtual void on_update(const float& delta) {};
		virtual void on_push_render_queue(void) {};
    };
};

#endif // __DOTTH_OBJECT_HPP__
