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
	std::vector<ID3D11Buffer*> positionBuffers;
	std::vector<ID3D11Buffer*> normalBuffers;
	std::vector<ID3D11Buffer*> textureCoordBuffers;
	std::vector<ID3D11Buffer*> boneIdBuffers;
	std::vector<ID3D11Buffer*> weightBuffers;
	std::vector<ID3D11Buffer*> indexBuffers;


	struct bone {
		XMUINT4 boneID;
		XMFLOAT4 weight;
	};
public:
public:
	std::vector<XMMATRIX*> calcBoneList;
	virtual void Initialize(void) {}
	virtual unsigned int GetSectionSize(void);
	virtual unsigned int GetIndicesSize(int index);
	virtual bool Load(const std::string& key);
	virtual void Draw(unsigned int index);
};

class Renderable
{
public:
	Renderable(dotth::mesh* raw);

private:
	void CreateVertexBuffer(ID3D11Buffer** buffer, void* data, unsigned int byteWidth);
	void CreateIndexBuffer(ID3D11Buffer** buffer, void* data, unsigned int byteWidth);

private:
	ID3D11Buffer* positionBuffer = nullptr;
	ID3D11Buffer* normalBuffer = nullptr;
	ID3D11Buffer* textureCoordBuffer = nullptr;
	ID3D11Buffer* boneIdBuffer = nullptr;
	ID3D11Buffer* weightBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	std::vector<ID3D11Buffer**> VertexBuffers;
	std::vector<unsigned int> BufferStrides;

	unsigned int IndexSize = 0;

public:
	void Draw(void);
};

class StaticMesh2
{
public:
	std::vector<Renderable*> Renderables;
public:
	unsigned int GetSectionSize(void)
	{
		return static_cast<unsigned int>(Renderables.size());
	}
	bool Load(const std::string& key);
	void Draw(unsigned int index);
};

class SkeletalMesh2
{
	virtual bool Load(const std::string& key);
	virtual void Draw(unsigned int index);
};