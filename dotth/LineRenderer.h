#pragma once

#include "SingleInstance.h"
#include "Renderable.h"
#include "D3D11RHI.h"
#include "Material.h"

struct Line {
	dotth::vector3 from;
	dotth::vector3 to;
	dotth::vector4 color;
	float duration;
};

class LineRenderer : SingleInstance<LineRenderer>
{
	friend class Application;
private:
	std::list<Line> lines;
	std::vector<ID3D11Buffer**> VertexBuffers;
	ID3D11Buffer* PositionBuffer = nullptr;
	ID3D11Buffer* ColorBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;
	std::vector<unsigned int> BufferStrides;
	unsigned int IndexSize = 0;

	Material* material = nullptr;

private:

	void CreateVertexBuffer(ID3D11Buffer** buffer, void* data, unsigned int byteWidth)
	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = byteWidth;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA res;
		memset(&res, 0, sizeof(decltype(res)));
		res.pSysMem = data;
		res.SysMemPitch = 0;
		res.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&desc, &res, buffer);
	}

	void CreateIndexBuffer(ID3D11Buffer** buffer, void* data, unsigned int byteWidth)
	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = byteWidth;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA res;
		memset(&res, 0, sizeof(decltype(res)));
		res.pSysMem = data;
		res.SysMemPitch = 0;
		res.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&desc, &res, buffer);
	}


public:
	void Init(void)
	{
		material = new Material;
		material->Load("tex0", "../Output/Client/x64/Debug/line_vs.cso", "../Output/Client/x64/Debug/line_ps.cso");
	}
	static void Push(Line line)
	{
		LineRenderer* inst = LineRenderer::Instance();
		inst->lines.push_back(line);
	}
	static void Push(const dotth::vector3& from, const dotth::vector3& to, const dotth::vector4& color, float duration)
	{
		LineRenderer* inst = LineRenderer::Instance();
		Line line;
		line.from = from;
		line.to = to;
		line.color = color;
		line.duration = duration;
		inst->lines.push_back(line);
	}

	static void Update(void);
	static void Draw(void);
};