// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "framework/node.h"
#include "external/sql/query_builder.h"

class T
{
public:
	int value = 0;

	T operator >>(T&& A)
	{
		value += A.value;
		return *this;
	}

	T(int a)
	{
		value = a;
		std::cout << "T 持失切 " << value << '\n';
	}
	T(const T& d)
	{
		value = d.value;
		std::cout << "T& 差紫 持失切" << '\n';
	}
	T(const T&& d)
	{
		value = d.value;
		std::cout << "T&& 差紫 持失切" << '\n';
	}
	~T() {
		std::cout << "T 社瑚切 " << value << '\n';
	}
};

class A : public T
{

public:
	A(int a) :T(a)
	{
		std::cout << "A 持失切" << '\n';
	}
};

class B : public T
{
public:
	B(int a) :T(a)
	{
		std::cout << "B 持失切" << '\n';
	}
};



struct float3
{
	union {
		float f[3] = { 0.f, 0.f, 0.f };
		struct { float _0, _1, _2; };
		struct { float a, b, c; };
		struct { float x, y, z; };
		struct { float r, g, b; };
	};
	
	float3(void) : _0(0.f), _1(0.f), _2(0.f) {}
	float3(const float& v) : _0(v), _1(v), _2(v) {}
	float3(const float& v0, const float& v1, const float& v2) : _0(v0), _1(v1), _2(v2) {}
	float3(const float3& v) : _0(v._0), _1(v._1), _2(v._2) {};
	float3(const float3&& v) : _0(v._0), _1(v._1), _2(v._2) {};
	float3& operator=(const float3& v)
	{
		_0 = v._0;
		_1 = v._1;
		_2 = v._2;
		return *this;
	}
	float3& operator=(const float3&& v)
	{
		_0 = v._0;
		_1 = v._1;
		_2 = v._2;
		return *this;
	}

	// length
	// dot
	// add
	// sub
	// multiply
	// divide
	// negate
	// normalize
	// cross
};

#include <chrono>

#include "framework/object.h"
class objA : public dotth::object
{};
class objB : public dotth::object
{};

#include "graphics/dx11/dx11_device.h"

int main()
{
	//auto device = new dotth::dx11::device;
	
	//device->initialize()
	//std::list<std::shared_ptr<obj>> l;
	auto aa = std::make_shared<objA>();
	auto bb = std::make_shared<objA>();
	auto cc = std::make_shared<objB>();
	auto dd = std::make_shared<objB>();
	auto ee = std::make_shared<objB>();
	aa->set_name("A");
	bb->set_name("B");
	cc->set_name("C");
	dd->set_name("D");
	ee->set_name("E");

	aa->attach(bb);
	aa->attach(cc);
	aa->attach(dd);
	aa->attach(ee);
	bb->attach(ee);
	auto kk = aa->find_by_func([](std::shared_ptr<dotth::object> a) { return true; });
	auto pp = aa->find_by_name("C");

	//aa->foreach<obj>([](auto aa) {
	//	aa->print();
	//});

	//ee->leave();

	//aa->foreach<obj>([](auto aa) {
	//	aa->print();
	//});
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
