cbuffer MatrixBuffer : register(b0)
{
    matrix world;
	matrix view;
	matrix projection;
};

struct VertexInputType
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float2 coord : TEXCOORD0;
    float3 tangent : TANGENT0;
    float4 color : COLOR0;
};

struct VertexOutputType
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMALWS;
	float3 tangent		: TANGENTWS;
	float3 worldPos		: POSITIONWS;
	float2 coord		: TEXCOORD;
};


VertexOutputType main(VertexInputType input)
{
	VertexOutputType output;
	matrix worldViewProj = mul(mul(world, view), projection);
	output.position = mul(float4(input.position, 1.0f), worldViewProj);
	output.normal = normalize(mul(input.normal, (float3x3)world));
	output.tangent = mul(input.tangent, (float3x3)world);
	output.worldPos = mul(float4(input.position, 1.0f), world).xyz;
	output.coord = input.coord;
	return output;
}