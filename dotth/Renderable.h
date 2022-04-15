#pragma once

#include "AssetBase.h"

class Renderable
{
public:
	Renderable(dotth::mesh* raw);

public:
	void Draw(void);

private:
	void CreateVertexBuffer(ID3D11Buffer** buffer, void* data, unsigned int byteWidth);
	void CreateIndexBuffer(ID3D11Buffer** buffer, void* data, unsigned int byteWidth);

private:
	std::vector<ID3D11Buffer**> VertexBuffers;
	ID3D11Buffer* PositionBuffer = nullptr;
	ID3D11Buffer* ColorBuffer = nullptr;
	ID3D11Buffer* NormalBuffer = nullptr;
	ID3D11Buffer* TextureCoordBuffer = nullptr;
	ID3D11Buffer* BoneIdBuffer = nullptr;
	ID3D11Buffer* WeightBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;
	std::vector<unsigned int> BufferStrides;
	unsigned int IndexSize = 0;
};