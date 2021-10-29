
#include "Object.h"

void Object::Init(void)
{
	OnInit();
	for (std::shared_ptr<Component> Comp : Components)
	{
		Comp->OnInit();
	}
	Foreach<Object>([](std::shared_ptr<Object> child) {
		child->Init();
		});
}

void Object::Destroy(void)
{
	OnDestroy();
	for (std::shared_ptr<Component> Comp : Components)
	{
		Comp->OnDestroy();
	}
	Foreach<Object>([](std::shared_ptr<Object> child) {
		child->Destroy();
		});
}

void Object::Update(void)
{
	OnUpdate();
	for (std::shared_ptr<Component> Comp : Components)
	{
		Comp->OnUpdate();
	}
	Foreach<Object>([](std::shared_ptr<Object> child) {
		child->Update();
		});
}

void Object::Draw(void)
{
	OnDraw();
	for (std::shared_ptr<Component> Comp : Components)
	{
		Comp->OnDraw();
	}
	Foreach<Object>([](std::shared_ptr<Object> child) {
		child->Draw();
		});
}



void Object::DrawImGuiHierarchy(void) 
{
	if (ImGui::TreeNode(std::to_string(GetSerial()).c_str(), "%d, %s", GetSerial(), GetName().c_str()))
	{
		Foreach<Object>(
			[](std::shared_ptr<Object> child) {
				child->DrawImGuiHierarchy();
			}
		);
		ImGui::TreePop();
	}
	//static float value = 0.5f;
	//if (ImGui::BeginPopupContextItem("item context menu"))
	//{
	//	if (ImGui::Selectable("Set to zero")) value = 0.0f;
	//	if (ImGui::Selectable("Set to PI")) value = 3.1415f;
	//	ImGui::SetNextItemWidth(-FLT_MIN);
	//	ImGui::DragFloat("##Value", &value, 0.1f, 0.0f, 0.0f);
	//	ImGui::EndPopup();
	//}
	//return;
	//if (GetChildrenCount() != 0)
	//{
	//	if (ImGui::TreeNode(std::to_string(Serial()).c_str(), "%d, %s", Serial(), Name().c_str()))
	//	{
	//		Foreach<Object>(
	//			[](std::shared_ptr<Object> child) {
	//				child->DrawImGuiHierarchy();
	//			}
	//		);
	//		ImGui::TreePop();
	//	}
	//}
	//else
	//{
	//	ImGui::Indent();
	//	ImGui::Text(std::to_string(Serial()).c_str(), "%d, %s", Serial(), Name().c_str());
	//	ImGui::Unindent();
	//}
}