#pragma once

#include "MeshComponent.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Material.h"

class StaticMeshComponent : public MeshComponent
{
public:
	std::shared_ptr<Material> material{ new Material };
	std::shared_ptr<StaticMesh> staticMesh{ new StaticMesh };

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

class SkeletalMeshComponent : public MeshComponent
{
public:
	std::shared_ptr<Material> material{ new Material };
	std::shared_ptr<SkeletalMesh> skeletalMesh{ new SkeletalMesh };

public:
	void Load(void);

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};