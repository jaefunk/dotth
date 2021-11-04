#pragma once

#include "Component.h"

enum class ProjectMode {
	Perspective,
	OrthoGraphic,
};

enum CAMERA_TRANFSFORM_DIRTY_FLAG {
	NONE = 0x0000,
	VIEW = 0x0001,
	PERSPECTIVE = 0x0010,
	ORTHO = 0x0100,
	ALL = VIEW | PERSPECTIVE | ORTHO
};

class CameraComponent : public Component
{
public:
	CameraComponent(int ViewportWidth, int ViewportHeight);

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;

private:
	int DirtyFlags = CAMERA_TRANFSFORM_DIRTY_FLAG::NONE;
	Matrix View;
	Matrix Perspective;
	Matrix Ortho;
	Vector3 Eye;
	Vector3 Up;
	Vector3 At;
	float Near;
	float Far;
	float Fov;
	int Width;
	int Height;

public:
	const Matrix& GetView(void);
	const Matrix& GetPerspective(void);
	const Matrix& GetOrtho(void);
	void SetEye(const Vector3& value);
	void SetUp(const Vector3& value);
	void SetAt(const Vector3& value);
	void SetFieldOfView(float value);
	void SetViewportSize(int width, int height);
	void SetNear(float value);
	void SetFar(float value);

public:
	void Sync(void);
};
