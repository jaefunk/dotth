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

	static void Update(void)
	{
		LineRenderer* inst = LineRenderer::Instance();
		
		std::vector<dotth::vector3> positions;
		std::vector<dotth::vector4> colors;
		std::vector<unsigned int> indices;
		
		unsigned int index = 0;
		for (const auto& line : inst->lines)
		{
			positions.push_back(line.from);
			colors.push_back(line.color);
			indices.push_back(index++);

			positions.push_back(line.to);
			colors.push_back(line.color);
			indices.push_back(index++);
		}

		inst->VertexBuffers.clear();

		inst->CreateVertexBuffer(&inst->PositionBuffer, positions.data(), static_cast<unsigned int>(sizeof(dotth::vector3) * positions.size()));
		inst->VertexBuffers.push_back(&(inst->PositionBuffer));
		inst->BufferStrides.push_back(sizeof(dotth::vector3));

		inst->CreateVertexBuffer(&inst->ColorBuffer, positions.data(), static_cast<unsigned int>(sizeof(dotth::vector4) * colors.size()));
		inst->VertexBuffers.push_back(&(inst->ColorBuffer));
		inst->BufferStrides.push_back(sizeof(dotth::vector4));

		inst->CreateIndexBuffer(&inst->IndexBuffer, indices.data(), static_cast<unsigned int>(sizeof(unsigned int) * indices.size()));
		inst->IndexSize = static_cast<unsigned int>(indices.size());

		inst->lines.clear();
	}

	static void Draw(void)
	{
		LineRenderer* inst = LineRenderer::Instance();

		MeshRenderParameter rp;
		std::vector<MeshRenderParameter> rps;
		inst->material->Bind(rps);

		unsigned int offset = 0;
		for (unsigned int i = 0; i < inst->VertexBuffers.size(); ++i)
		{
			D3D11RHI::Context()->IASetVertexBuffers(i, 1, inst->VertexBuffers[i], &inst->BufferStrides[i], &offset);
		}
		D3D11RHI::Context()->IASetIndexBuffer(inst->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		D3D11RHI::Context()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		D3D11RHI::Context()->DrawIndexed(inst->IndexSize, 0, 0);
	}
};