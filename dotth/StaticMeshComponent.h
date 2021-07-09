#pragma once

#include "MeshComponent.h"
#include "D3D11Shader.h"
#include "D3D11Camera.h"
#include "StaticMesh.h"
#include "Texture2D.h"

class StaticMeshComponent : public MeshComponent
{
private:
	std::shared_ptr<StaticMesh> _StaticMesh;
	std::shared_ptr<Texture2D> _Texture2D;
	std::shared_ptr<Shader> _Shader;

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};
