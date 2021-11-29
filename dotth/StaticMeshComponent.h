#pragma once

#include "MeshComponent.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture2D.h"

class StaticMeshComponent : public MeshComponent
{
public:
	std::shared_ptr<StaticMesh> staticMesh;
	std::shared_ptr<Texture2D> texture2D;
	std::shared_ptr<VertexShader> deferredVertexShader;
	std::shared_ptr<PixelShader> deferredPixelShader;

public:
	bool SetStaticMesh(std::shared_ptr<StaticMesh> NewMesh);
	void Load1(void);
	void Load2(void);
	void Load3(void);

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};
