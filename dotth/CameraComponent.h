#pragma once

#include "Component.h"

enum class ProjectMode {
	Perspective,
};

enum CAMERA_TRANFSFORM_DIRTY_FLAG {
	NONE = 0x0000,
	VIEW = 0x0001,
	PROJECTION = 0x0010,
	ALL = VIEW | PROJECTION
};

using namespace dotth;
class CameraComponent : public Component
{
public:
	CameraComponent(unsigned int ViewportWidth, unsigned int ViewportHeight);

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;

private:
	int DirtyFlags = CAMERA_TRANFSFORM_DIRTY_FLAG::NONE;
	matrix View;
	matrix Projection;
	vector3 Eye;
	vector3 Up;
	vector3 At;
	float Near;
	float Far;
	float Fov;
	int Width;
	int Height;

public:
	void GetViewInfo(ViewInfo& viewInfo);

	const matrix& GetView(void);
	const matrix& GetProjection(void);
	void SetEye(const vector3& value);
	void SetUp(const vector3& value);
	void SetAt(const vector3& value);
	void SetFieldOfView(float value);
	void SetViewportSize(int width, int height);
	void SetNear(float value);
	void SetFar(float value);

public:
	void Sync(void);
};
