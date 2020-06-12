
#pragma once

#include "framework/object.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "graphics/shader.h"

class drawable : public object
{
private:
	camera* _camera;
	model* _model;
	shader* _shader;

public:
	virtual void on_init(void)
	{
		_camera = new camera;
		_model = new model;
		_shader = new shader;


		_camera->SetPosition(0.f, 0.f, -5.f);
		_model->Initialize(renderer::get()->dx11()->device());
		_shader->Initialize(renderer::get()->dx11()->device());
	};
	virtual void on_update(void)
	{
		printf("b");
	};
	virtual void on_render(void)
	{
		_camera->Render();
		XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
		worldMatrix = XMMatrixIdentity();
		_camera->GetViewMatrix(viewMatrix);
		renderer::get()->dx11()->GetProjectionMatrix(projectionMatrix);
		_model->Render(renderer::get()->dx11()->context());
		_shader->Render(renderer::get()->dx11()->context(), _model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	};
};