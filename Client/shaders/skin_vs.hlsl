cbuffer MatrixBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
	matrix bones[128];
};

struct VertexInputType
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
	float2 coord : TEXCOORD0;
	uint4 boneIdx : BLENDINDICES0;
	float4 weight : BLENDWEIGHT0;
	//float3 tangent : TANGENT0;
	//float4 color : COLOR0;
};

struct VertexOutputType
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMALWS;
	float2 coord		: TEXCOORD;
	float3 worldPos		: POSITIONWS;
	//float3 tangent		: TANGENTWS;
};

#define IDENTITY_MATRIX float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)

VertexOutputType main(VertexInputType input)
{
	VertexOutputType output;
	output.position = float4(input.position, 1.f);

	float4x4 boneTransform = float4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 1; ++i)
	{
		if (input.boneIdx[i] == -1)
		{
			break;
		}
		if (input.boneIdx[i] >= 128)
		{
			break;
		}
		boneTransform += bones[input.boneIdx[i]] * input.weight[i];
	}

	output.position = mul(output.position, boneTransform);
	matrix worldViewProj = mul(mul(world, view), projection);
	output.position = mul(output.position, worldViewProj);
	output.normal = normalize(mul(input.normal, (float3x3)world));
	output.coord = input.coord;
	output.worldPos = mul(float4(input.position, 1.0f), world).xyz;
	//output.tangent = mul(input.tangent, (float3x3)world);
	return output;
}