
#include "vector.hpp"

dotth::vector3::vector3(void) { x = y = z = 0.f; }

dotth::vector3::vector3(const float & v) : x(v), y(v), z(v) {}

dotth::vector3::vector3(const float & x, const float & y, const float & z) : x(x), y(y), z(z) {}

dotth::vector3::vector3(const vector3 & v) : x(v.x), y(v.y), z(v.z) {}

dotth::vector3::vector3(const vector3 && v) : x(v.x), y(v.y), z(v.z) {}

inline const char * dotth::vector3::c_str(void) const {
	return utility::string::format("x:%f y:%f z:%f", x, y, z).c_str();
}
