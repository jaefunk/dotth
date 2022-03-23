#pragma once

#include "Object.h"
#include "CameraComponent.h"

using namespace dotth;
class Camera : public Object
{
public:
	Camera(unsigned int width, unsigned int height);

public:
	virtual void OnInit(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;

private:
	std::shared_ptr<CameraComponent> Comp;
public:
	std::shared_ptr<CameraComponent> GetCameraComponent(void);
	const matrix& GetView(void);
	const matrix& GetProjection(void);
};