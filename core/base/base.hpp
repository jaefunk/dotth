#ifndef __DOTTH_BASE_HPP__
#define __DOTTH_BASE_HPP__

#include "dotth.hpp"

namespace dotth {
    class base
    {
    private:
        int _serial;
        std::time_t _birth;
    public:
		base(void);
		const int& serial(void) const;
		const std::time_t& birth(void) const;
    };
};

#endif // __DOTTH_BASE_HPP__
