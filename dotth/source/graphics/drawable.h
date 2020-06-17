
#pragma once

#include "framework/object.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "graphics/shader.h"

class drawable : public object
{
private:
	std::shared_ptr<model> _model;
	std::shared_ptr<shader> _shader;

public:
	virtual void on_init(void)
	{
		_model = std::make_shared<model>();
		_shader = std::make_shared<shader>();
		_model->Initialize();
		_shader->Initialize(renderer::device());
	};

	virtual void on_update(void)
	{
	};

	virtual void on_render(void)
	{
		XMMATRIX worldMatrix = XMMatrixIdentity();
		_model->Render();
		_shader->Render(renderer::context(), _model->GetIndexCount(), &worldMatrix, camera::get()->get_view(), camera::get()->get_pers());
	};
};