#include "TestScene.h"

void TestScene::OnInit(void)
{
	AssetManager::Instance()->LoadAsset(ASSET_TYPE::TEXTURE, "cat0", "test.png");
	AssetManager::Instance()->LoadAsset(ASSET_TYPE::MODEL, "robot0", "Resource/model/robot/RobotKyle.fbx");
	AssetManager::Instance()->LoadAsset(ASSET_TYPE::MODEL, "robot1", "Resource/model/robot/xbot.fbx");
	AssetManager::Instance()->LoadAsset(ASSET_TYPE::TEXTURE, "robot_t", "Resource/model/robot/Robot_Color.png");

	Camera::Instance()->SetAt(DirectX::XMFLOAT3(0.f, 90.f, 0.f));
	Camera::Instance()->SetUp(DirectX::XMFLOAT3(0.f, 1.f, 0.f));
	Camera::Instance()->SetEye(DirectX::XMFLOAT3(0.f, 90.f, -250.f));
	Camera::Instance()->SetFieldOfView(DirectX::XM_PI * 0.25f);
	Camera::Instance()->SetNear(0.1f);
	Camera::Instance()->SetFar(1000.f);

	auto p = std::make_shared<sample_object>();
	p->SetName("triangle");
	Root()->Attach(p);
}

void TestScene::OnUpdate(void)
{
}

void TestScene::OnDraw(void)
{
}
