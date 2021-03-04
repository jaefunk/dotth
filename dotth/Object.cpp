
#include "Object.h"

void Object::Init(void)
{
	OnInit();
	Foreach([](std::shared_ptr<Object> child) {
		child->Init();
	});
}

void Object::Destroy(void)
{
	OnDestroy();
	Foreach([](std::shared_ptr<Object> child) {
		child->Destroy();
	});
}

void Object::Update(void)
{
	OnUpdate();
	Foreach([](std::shared_ptr<Object> child) {
		child->Update();
	});
}

void Object::Draw(void)
{
	OnDraw();
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
