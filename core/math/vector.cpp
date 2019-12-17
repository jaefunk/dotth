
#include "vector.hpp"
#include "base/utility.hpp"

dotth::vector2::vector2(void) { x = y = 0.f; }

dotth::vector2::vector2(const float & v) : x(v), y(v) {}

dotth::vector2::vector2(const float & x, const float & y) : x(x), y(y) {}

dotth::vector2::vector2(const vector2 & v) : x(v.x), y(v.y) {}

dotth::vector2::vector2(const vector2 && v) : x(v.x), y(v.y) {}

const float dotth::vector2::length(void) const {
	return std::sqrt((x * x) + (y * y));
}

const float dotth::vector2::dot(const vector2 & v) const {
	return (x * v.x) + (y * v.y);
}

const dotth::vector2 dotth::vector2::add(const vector2 & v) const {
	return vector2(x + v.x, y + v.y);
}

const dotth::vector2 dotth::vector2::subtract(const vector2 & v) const {
	return vector2(x - v.x, y - v.y);
}

const dotth::vector2 dotth::vector2::multiply(const float & v) const {
	return vector2(x * v, y * v);
}

const dotth::vector2 dotth::vector2::divide(const float & v) const {
	return vector2(x / v, y / v);
}

const dotth::vector2 dotth::vector2::negate(void) const {
	return multiply(-1.f);
}

const dotth::vector2 dotth::vector2::normalize(void) const {
	float l = length();
	if (l < 0.00001f)
		return vector2(0.f);
	return multiply(1.f / l);
}

const char * dotth::vector2::c_str(void) const {
	return utility::string::format("x:%f y:%f", x, y).c_str();
}


dotth::vector3::vector3(void) { x = y = z = 0.f; }

dotth::vector3::vector3(const float & v) : x(v), y(v), z(v) {}

dotth::vector3::vector3(const float & x, const float & y, const float & z) : x(x), y(y), z(z) {}

dotth::vector3::vector3(const vector2 & v) : x(v.x), y(v.y), z(0.f) {}

dotth::vector3::vector3(const vector2 && v) : x(v.x), y(v.y), z(0.f) {}

dotth::vector3::vector3(const vector3 & v) : x(v.x), y(v.y), z(v.z) {}

dotth::vector3::vector3(const vector3 && v) : x(v.x), y(v.y), z(v.z) {}

const float dotth::vector3::length(void) const {
	return std::sqrt((x * x) + (y * y) + (z * z));
}

const float dotth::vector3::dot(const vector3 & v) const {
	return (x * v.x) + (y * v.y) + (z * v.z);
}

const dotth::vector3 dotth::vector3::add(const vector3 & v) const {
	return vector3(x + v.x, y + v.y, z + v.z);
}

const dotth::vector3 dotth::vector3::subtract(const vector3 & v) const {
	return vector3(x - v.x, y - v.y, z - v.z);
}

const dotth::vector3 dotth::vector3::multiply(const float & v) const {
	return vector3(x * v, y * v, z * v);
}

const dotth::vector3 dotth::vector3::multiply(const vector3 v) const {
	return vector3(x * v.x, y * v.y, z * v.z);
}

const dotth::vector3 dotth::vector3::divide(const float & v) const {
	return vector3(x / v, y / v, z / v);
}

const dotth::vector3 dotth::vector3::negate(void) const {
	return multiply(-1.f);
}

const dotth::vector3 dotth::vector3::normalize(void) const {
	float l = length();
	if (l < 0.00001f)
		return vector3(0.f);
	return multiply(1.f / l);
}

const dotth::vector3 dotth::vector3::cross(const vector3 & v) const
{
	return vector3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}

const char * dotth::vector3::c_str(void) const {
	return utility::string::format("x:%f y:%f z:%f", x, y, z).c_str();
}
