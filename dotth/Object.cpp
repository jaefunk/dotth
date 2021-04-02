
#include "Object.h"

void Object::Init(void)
{
	OnInit();
	for (std::shared_ptr<Component> Comp : _Components)
	{
		Comp->OnInit();
	}
	Foreach([](std::shared_ptr<Object> child) {
		child->Init();
	});
}

void Object::Destroy(void)
{
	OnDestroy();
	for (std::shared_ptr<Component> Comp : _Components)
	{
		Comp->OnDestroy();
	}
	Foreach([](std::shared_ptr<Object> child) {
		child->Destroy();
	});
}

void Object::Update(void)
{
	OnUpdate();
	for (std::shared_ptr<Component> Comp : _Components)
	{
		Comp->OnUpdate();
	}
	Foreach([](std::shared_ptr<Object> child) {
		child->Update();
	});
}

void Object::Draw(void)
{
	OnDraw();
	for (std::shared_ptr<Component> Comp : _Components)
	{
		Comp->OnDraw();
	}
	Foreach([](std::shared_ptr<Object> child) {
		child->Draw();
	});
}

void Object::OnInit(void)
{
}

void Object::OnUpdate(void)
{
}

void Object::OnDraw(void)
{
}

void Object::OnDestroy(void) 
{
}
