#include "TestScene.h"
#include "framework/SampleObject.h"
#include "Components/CubeComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/ModelComponent.h"

void TestScene::OnInit(void)
{
	AssetManager::Instance()->LoadAsset(ASSET_TYPE::TEXTURE, "cat0", "test.png");
	AssetManager::Instance()->LoadAsset(ASSET_TYPE::TEXTURE, "robot_t", "Resource/model/robot/Robot_Color.png");
	AssetManager::Instance()->LoadAsset(ASSET_TYPE::MODEL, "robot0", "Resource/model/robot/RobotKyle.fbx");
	AssetManager::Instance()->LoadAsset(ASSET_TYPE::MODEL, "robot1", "Resource/model/robot/xbot.fbx");
	

	Camera::Instance()->SetAt(DirectX::XMFLOAT3(0.f, 90.f, 0.f));
	Camera::Instance()->SetUp(DirectX::XMFLOAT3(0.f, 1.f, 0.f));
	Camera::Instance()->SetEye(DirectX::XMFLOAT3(0.f, 90.f, -250.f));
	Camera::Instance()->SetFieldOfView(DirectX::XM_PI * 0.25f);
	Camera::Instance()->SetNear(0.1f);
	Camera::Instance()->SetFar(1000.f);

	auto obj = std::make_shared<SampleObject>();
	obj->AttachComponent(std::make_shared<ModelComponent>("robot1"));
	Root()->Attach(obj);
}

void TestScene::OnUpdate(void)
{
}

void TestScene::OnDraw(void)
{
}
