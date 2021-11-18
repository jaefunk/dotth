#pragma once

#include "MeshComponent.h"
#include "ResourceManager.h"
#include "D3D11Shader.h"
#include "Texture2D.h"

class StaticMeshComponent : public MeshComponent
{
public:
	std::shared_ptr<StaticMesh> _StaticMesh;
	std::shared_ptr<Texture2D> _Texture2D;
	std::shared_ptr<Shader> _Shader;

	std::shared_ptr<SimpleVertexShader> _DeferredVertexShader;
	std::shared_ptr<SimplePixelShader> _DeferredPixelShader;

public:
	void Load1(void);
	void Load2(void);
	void Load3(void);

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};
