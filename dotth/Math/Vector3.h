
#pragma once

struct Vector3 {
	union {
		struct { float f[3]; };
		struct { float x, y, z; };
	};

	Vector3(void) = default;
	Vector3(float f) : x(f), y(f), z(f) {}
	Vector3(float* pf) : x(pf[0]), y(pf[1]), z(pf[2]) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3(const Vector3& value) : x(value.x), y(value.y), z(value.z) {}

	static void Add(const Vector3& left, const Vector3& right, Vector3& result)
	{
		result.x = left.x + right.x;
		result.y = left.y + right.y;
		result.z = left.z + right.z;
	}
	static void Subtract(const Vector3& left, const Vector3& right, Vector3& result)
	{
		result.x = left.x - right.x;
		result.y = left.y - right.y;
		result.z = left.z - right.z;
	}
	static void Multiply(const Vector3& left, const Vector3& right, Vector3& result)
	{
		result.x = left.x * right.x;
		result.y = left.y * right.y;
		result.z = left.z * right.z;
	}
	static void Multiply(const Vector3& left, float right, Vector3& result)
	{
		result.x = left.x * right;
		result.y = left.y * right;
		result.z = left.z * right;
	}
	static void Devide(const Vector3& left, float right, Vector3& result)
	{
		result.x = left.x / right;
		result.y = left.y / right;
		result.z = left.z / right;
	}
	static Vector3 Add(const Vector3& left, const Vector3& right)
	{
		Vector3 result;
		Add(left, right, result);
		return result;
	}
	static Vector3 Subtract(const Vector3& left, const Vector3& right)
	{
		Vector3 result;
		Subtract(left, right, result);
		return result;
	}
	static Vector3 Multiply(const Vector3& left, float right)
	{
		Vector3 result;
		Multiply(left, right, result);
		return result;
	}
	static Vector3 Devide(const Vector3& left, float right)
	{
		Vector3 result;
		Devide(left, right, result);
		return result;
	}
	static Vector3 Negate(const Vector3& target)
	{
		return Vector3::Multiply(target, -1.f);
	}
	static bool IsEqual(const Vector3& left, const Vector3& right, float tolerance = std::numeric_limits<float>::epsilon())
	{
		return abs(left.x - right.x) <= tolerance && abs(left.y - right.y) <= tolerance && abs(left.z - right.z) <= tolerance;
	}
	float& operator[](int index) 
	{ 
		return f[index]; 
	}
	float operator[](int index) const 
	{ 
		return f[index]; 
	}
	operator DirectX::XMFLOAT3()
	{
		return DirectX::XMFLOAT3(f);
	}
	operator DirectX::XMFLOAT3() const
	{
		return DirectX::XMFLOAT3(f);
	}

	static Vector3 Zero(void) {
		return Vector3(0.f, 0.f, 0.f);
	}
	static Vector3 One(void) {
		return Vector3(1.f, 1.f, 1.f);
	}
	static Vector3 Forward(void) {
		return Vector3(0.f, 0.f, 1.f);
	}
	static Vector3 Backward(void) {
		return Vector3(0.f, 0.f, -1.f);
	}
	static Vector3 Up(void) {
		return Vector3(0.f, 1.f, 0.f);
	}
	static Vector3 Down(void) {
		return Vector3(0.f, -1.f, 0.f);
	}
	static Vector3 Left(void) {
		return Vector3(-1.f, 0.f, 0.f);
	}
	static Vector3 Right(void) {
		return Vector3(1.f, 0.f, 0.f);
	}
	static Vector3 AxisX(void) {
		return Vector3(1.f, 0.f, 0.f);
	}
	static Vector3 AxisY(void) {
		return Vector3(0.f, 1.f, 0.f);
	}
	static Vector3 AxisZ(void) {
		return Vector3(0.f, 0.f, 1.f);
	}
};