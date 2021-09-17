#pragma once

#include "Component.h"
#include "Object.h"

enum class ProjectMode {
	Perspective,
	OrthoGraphic,
};

class CameraComponent : public Component
{
public:
	CameraComponent(void);

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;

private:
	// horizontal field of view in degrees...
	float FieldOfView;
	float OrthoWidth;
	float OrthoNearClipPlane;
	float OrthoFarClipPlane;
	// width / height
	float AspectRatio;

public:
	void SetFieldOfView(float InFieldOfView) {
		FieldOfView = InFieldOfView;
	};
	void SetOrthoWidth(float InOrthoWidth) {
		OrthoWidth = InOrthoWidth;
	};
	void SetOrthoNearClipPlane(float InOrthoNearClipPlane) {
		OrthoNearClipPlane = InOrthoNearClipPlane;
	};
	void SetOrthoFarClipPlane(float InOrthoFarClipPlane) {
		OrthoFarClipPlane = InOrthoFarClipPlane;
	};
	void SetAspectRatio(float InAspectRatio) {
		AspectRatio = InAspectRatio;
	};
};
