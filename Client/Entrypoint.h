#pragma once

#include "Scene.h"

class EntryPoint : public Scene
{
public:
	virtual void OnInit(void) override;
	//virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	//virtual void OnDraw(void) override;
	//virtual void OnDrawImGui(void) override;

private:
	std::shared_ptr<Object> so1;

	//template <class Ty, class... Args>
	//std::shared_ptr<Ty> Add(Args... args)
	//{
	//	auto Value = std::make_shared<Ty>(args...);
	//	//Value->SetOwner(o1->weak_from_this());
	//	o1->AddComponent(Value);
	//	return Value;
	//}
	Vector4 v4f;
	void test0(Vector4 v)
	{
		v4f.x += v.x;
		v4f.y += v.y;
		v4f.z += v.z;
		v4f.w += v.w;
	}

	void test1(const Vector4& v)
	{
		v4f.x += v.x;
		v4f.y += v.y;
		v4f.z += v.z;
		v4f.w += v.w;
	}

	float f;
	void test2(float _)
	{
		f += _;
	}
	void test3(const float& _)
	{
		f += _;
	}
};