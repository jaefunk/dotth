
#include "Object.h"

void Object::Init(void)
{
	OnInit();
	std::for_each(_Components.begin(), _Components.end(), [](std::shared_ptr<Component> Component) {
		Component->OnInit();
	});
	Foreach([](std::shared_ptr<Object> child) {
		child->Init();
	});
}

void Object::Update(void)
{
	OnUpdate();
	std::for_each(_Components.begin(), _Components.end(), [](std::shared_ptr<Component> Component) {
		Component->OnUpdate();
	});
	Foreach([](std::shared_ptr<Object> child) {
		child->Update();
	});
}

void Object::Draw(void)
{
	OnDraw();
	std::for_each(_Components.begin(), _Components.end(), [](std::shared_ptr<Component> Component) {
		Component->OnDraw();
	});
	Foreach([](std::shared_ptr<Object> child) {
		child->Draw();
	});
}

void Object::Destroy(void)
{
	OnDestroy();
	std::for_each(_Components.begin(), _Components.end(), [](std::shared_ptr<Component> Component) {
		Component->OnDestroy();
	});
	Foreach([](std::shared_ptr<Object> child) {
		child->Destroy();
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

void Object::AttachComponent(std::shared_ptr<Component> target, std::string name)
{
	if (_Components.end() != std::find(_Components.begin(), _Components.end(), target))
		return;
	target->_Owner = this;
	_Components.push_back(target);
}

void Object::DetachComponent(std::shared_ptr<Component> target)
{
	target->_Owner = nullptr;
	_Components.remove(target);
}
