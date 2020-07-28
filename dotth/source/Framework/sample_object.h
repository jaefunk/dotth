
#pragma once

#include "Framework/Object.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "graphics/shader.h"

class sample_object : public Object
{
private:
	std::shared_ptr<model> _model;
	std::shared_ptr<sdr2222> _shader;

public:
	virtual void OnInit(void)
	{
		_model = std::make_shared<model>();
		AttachComponent(_model);
		_shader = std::make_shared<sdr2222>();
		//AttachComponent(_shader);
		_model->Initialize();
		_shader->Initialize(renderer::device());
	};

	virtual void OnUpdate(void)
	{
	};

	virtual void OnDraw(void)
	{
		XMMATRIX worldMatrix = XMMatrixIdentity();
		_model->Render();
		_shader->Render(renderer::context(), _model->GetIndexCount(), &worldMatrix, Camera::Instance()->View(), Camera::Instance()->Perspective());
	};
};