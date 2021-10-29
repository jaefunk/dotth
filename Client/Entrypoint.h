#pragma once

#include "Scene.h"

class EntryPoint : public Scene
{
public:
	virtual void OnInit(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDrawImGui(void) override;
private:
	std::shared_ptr<Object> o1;

	//template <class Ty, class... Args>
	//std::shared_ptr<Ty> Add(Args... args)
	//{
	//	auto Value = std::make_shared<Ty>(args...);
	//	//Value->SetOwner(o1->weak_from_this());
	//	o1->AddComponent(Value);
	//	return Value;
	//}
};