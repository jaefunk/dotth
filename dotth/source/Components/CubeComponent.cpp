
#include "CubeComponent.h"

void CubeComponent::GetInputDesc(D3D11_INPUT_ELEMENT_DESC ** desc, unsigned int & size)
{

	(*desc) = new D3D11_INPUT_ELEMENT_DESC[2];
	(*desc)[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	(*desc)[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	size = 2;
}

unsigned int CubeComponent::GetVertexStructureSize(void)
{
	return sizeof(VertexType);
}

unsigned int CubeComponent::GetVertexCount(void)
{
	return 24;
}

unsigned int CubeComponent::GetIndexCount(void)
{
	return 36;
}

void * CubeComponent::GetVertexArray(void)
{
	VertexType* vertices = new VertexType[GetVertexCount()];

	vertices[0] = { XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.f, 1.f) };
	vertices[1] = { XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.f, 1.f) };
	vertices[2] = { XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(1.0f, 0.0f, 0.f, 1.f) };
	vertices[3] = { XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(1.0f, 0.0f, 0.f, 1.f) };
	vertices[4] = { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.f, 1.f) };
	vertices[5] = { XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.f, 1.f) };
	vertices[6] = { XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(0.0f, 1.0f, 0.f, 1.f) };
	vertices[7] = { XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(0.0f, 1.0f, 0.f, 1.f) };
	vertices[8] = { XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(0.0f, 0.0f, 1.f, 1.f) };
	vertices[9] = { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.f, 1.f) };
	vertices[10] = { XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.f, 1.f) };
	vertices[11] = { XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(0.0f, 0.0f, 1.f, 1.f) };
	vertices[12] = { XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(1.0f, 0.0f, 1.f, 1.f) };
	vertices[13] = { XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.f, 1.f) };
	vertices[14] = { XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.f, 1.f) };
	vertices[15] = { XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(1.0f, 0.0f, 1.f, 1.f) };
	vertices[16] = { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 1.f, 1.f) };
	vertices[17] = { XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 1.f, 1.f) };
	vertices[18] = { XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 1.f, 1.f) };
	vertices[19] = { XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 1.f, 1.f) };
	vertices[20] = { XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(1.0f, 1.0f, 0.f, 1.f) };
	vertices[21] = { XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(1.0f, 1.0f, 0.f, 1.f) };
	vertices[22] = { XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(1.0f, 1.0f, 0.f, 1.f) };
	vertices[23] = { XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(1.0f, 1.0f, 0.f, 1.f) };

	return vertices;
}

unsigned long * CubeComponent::GetIndexArray(void)
{
	unsigned long* indices = new unsigned long[GetIndexCount()];

	indices[0] = 3;
	indices[1] = 1;
	indices[2] = 0;
	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;

	indices[6] = 6;
	indices[7] = 4;
	indices[8] = 5;
	indices[9] = 7;
	indices[10] = 4;
	indices[11] = 6;

	indices[12] = 11;
	indices[13] = 9;
	indices[14] = 8;
	indices[15] = 10;
	indices[16] = 9;
	indices[17] = 11;

	indices[18] = 14;
	indices[19] = 12;
	indices[20] = 13;
	indices[21] = 15;
	indices[22] = 12;
	indices[23] = 14;

	indices[24] = 19;
	indices[25] = 17;
	indices[26] = 16;
	indices[27] = 18;
	indices[28] = 17;
	indices[29] = 19;

	indices[30] = 22;
	indices[31] = 20;
	indices[32] = 21;
	indices[33] = 23;
	indices[34] = 20;
	indices[35] = 22;

	return indices;
}

std::string CubeComponent::GetShaderName(void)
{
	return "Resource/Primitive.fx";
}
