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
};

struct VertexOutputType
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMALWS;
	float2 coord		: TEXCOORD;
	float3 worldPos		: POSITIONWS;
};

#define IDENTITY_MATRIX float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)

VertexOutputType main(VertexInputType input)
{
	float4x4 boneTransform = IDENTITY_MATRIX;
	if (input.boneIdx[0] != -1)
	{
		boneTransform = bones[input.boneIdx[0]] * input.weight.x;
	}
	if (input.boneIdx[1] != -1)
	{
		boneTransform += bones[input.boneIdx[1]] * input.weight.y;
	}
	if (input.boneIdx[2] != -1)
	{
		boneTransform += bones[input.boneIdx[2]] * input.weight.z;
	}
	if (input.boneIdx[3] != -1)
	{
		boneTransform += bones[input.boneIdx[3]] * input.weight.w;
	}

	matrix boneWorld = mul(boneTransform, world);
	matrix worldViewProj = mul(mul(boneWorld, view), projection);

	VertexOutputType output;
	
	output.position = mul(float4(input.position, 1.f), worldViewProj);
	output.normal = normalize(mul(input.normal, (float3x3)boneWorld));
	output.coord = input.coord;
	output.worldPos = mul(float4(input.position, 1.0f), world).xyz;
	return output;
}