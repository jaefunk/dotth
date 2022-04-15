cbuffer MatrixBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
};

struct VertexInputType
{
	float3 position : POSITION0;
	float4 color : COLOR0;
};

struct VertexOutputType
{
	float4 position		: SV_POSITION;
	float4 color		: COLOR;
};

VertexOutputType main(VertexInputType input)
{
	VertexOutputType output;
	matrix worldViewProj = mul(mul(world, view), proj);
	output.position = mul(float4(input.position, 1.0f), worldViewProj);
	output.color = input.color;
	return output;
}