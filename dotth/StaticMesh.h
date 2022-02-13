#pragma once

#include "AssetBase.h"

class StaticMesh : public Mesh
{
protected:
	std::vector<ID3D11Buffer*> vertexBuffers;
	std::vector<ID3D11Buffer*> indexBuffers;

public:
	virtual void Initialize(void) {}
	virtual unsigned int GetSectionSize(void);
	virtual unsigned int GetIndicesSize(int index);
	virtual bool Load(const std::string& key);
	virtual void Draw(unsigned int index);
};

class SkeletalMesh : public StaticMesh
{
protected:
	struct bone {
		XMUINT4 boneID;
		XMFLOAT4 weight;
	};
	std::vector<ID3D11Buffer*> animationBuffers;
public:
public:
	std::vector<XMMATRIX*> calcBoneList;
	virtual void Initialize(void) {}
	virtual unsigned int GetSectionSize(void);
	virtual unsigned int GetIndicesSize(int index);
	virtual bool Load(const std::string& key);
	virtual void Draw(unsigned int index);
};