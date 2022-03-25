cbuffer MatrixBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
};

struct VertexInputType
{
	float3 position : POSITION0;
	float3 color : COLOR0;
};

struct VertexOutputType
{
	float4 position		: SV_POSITION;
	float3 color		: COLOR;
	float3 worldPos		: POSITIONWS;
};

#define IDENTITY_MATRIX float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)

VertexOutputType main(VertexInputType input)
{
	matrix worldViewProj = mul(view, proj);

	VertexOutputType output;	
	output.position = mul(float4(input.position, 1.f), worldViewProj);
	output.worldPos = mul(float4(input.position, 1.0f), world).xyz;
	output.color = input.color;
	return output;
}