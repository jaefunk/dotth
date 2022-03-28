
#include "LineRenderer.h"
#include "Scenario.h"
#include "Camera.h"

void LineRenderer::Update(void)
{
	LineRenderer* inst = LineRenderer::Instance();

	std::vector<dotth::vector3> positions;
	std::vector<dotth::vector4> colors;
	std::vector<unsigned int> indices;

	unsigned int index = 0;
	for (auto& line : inst->lines)
	{
		positions.push_back(line.from);
		colors.push_back(line.color);
		indices.push_back(index++);

		positions.push_back(line.to);
		colors.push_back(line.color);
		indices.push_back(index++);

		line.duration -= Scenario::Instance()->CurrentScene()->GetDeltaSeconds();
	}

	inst->VertexBuffers.clear();
	inst->BufferStrides.clear();

	inst->CreateVertexBuffer(&inst->PositionBuffer, positions.data(), static_cast<unsigned int>(sizeof(dotth::vector3) * positions.size()));
	inst->VertexBuffers.push_back(&(inst->PositionBuffer));
	inst->BufferStrides.push_back(sizeof(dotth::vector3));
	inst->CreateVertexBuffer(&inst->ColorBuffer, colors.data(), static_cast<unsigned int>(sizeof(dotth::vector4) * colors.size()));
	inst->VertexBuffers.push_back(&(inst->ColorBuffer));
	inst->BufferStrides.push_back(sizeof(dotth::vector4));
	inst->CreateIndexBuffer(&inst->IndexBuffer, indices.data(), static_cast<unsigned int>(sizeof(unsigned int) * indices.size()));
	inst->IndexSize = static_cast<unsigned int>(indices.size());

	std::list<Line> NewLine;
	for (auto& line : inst->lines)
	{
		if (line.duration > 0.f)
			NewLine.push_back(line);
	}
	inst->lines = NewLine;
}

void LineRenderer::Draw(void)
{
	LineRenderer* inst = LineRenderer::Instance();

	dotth::matrix world;
	world.set_identity();
	auto camera = Scenario::Instance()->CurrentScene()->GetActiveCamera();
	dotth::matrix view = camera->GetView();
	dotth::matrix proj = camera->GetProjection();

	std::vector<MeshRenderParameter> parameters;
	parameters.push_back(MeshRenderParameter({ "world", &world, sizeof(world) }));
	parameters.push_back(MeshRenderParameter({ "view", &view, sizeof(view) }));
	parameters.push_back(MeshRenderParameter({ "proj", &proj, sizeof(proj) }));
	inst->material->Bind(parameters);

	unsigned int offset = 0;
	for (unsigned int i = 0; i < inst->VertexBuffers.size(); ++i)
	{
		D3D11RHI::Context()->IASetVertexBuffers(i, 1, inst->VertexBuffers[i], &inst->BufferStrides[i], &offset);
	}
	D3D11RHI::Context()->IASetIndexBuffer(inst->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D11RHI::Context()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
	D3D11RHI::Context()->DrawIndexed(inst->IndexSize, 0, 0);
}
