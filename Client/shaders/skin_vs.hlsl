cbuffer MatrixBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer BoneBuffer : register(b1)
{
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


VertexOutputType main(VertexInputType input)
{
	VertexOutputType output;


	matrix worldViewProj = mul(mul(world, view), projection);

	//float finalWeight = 1.0f - (input.weight[0] + input.weight[1] + input.weight[2]);
	//float4x4 boneTransform = bones[input.boneIdx[0]] * input.weight[0];
	//boneTransform += bones[input.boneIdx[1]] * input.weight[1];
	//boneTransform += bones[input.boneIdx[2]] * input.weight[2];
	//boneTransform += bones[input.boneIdx[3]] * finalWeight;
	//output.position = mul(float4(input.position, 1.0f), boneTransform);
	output.position = float4(input.position, 1.0f);


	output.position = mul(output.position, worldViewProj);
	output.normal = normalize(mul(input.normal, (float3x3)world));
	output.coord = input.coord;
	output.worldPos = mul(float4(input.position, 1.0f), world).xyz;
	//output.tangent = mul(input.tangent, (float3x3)world);
	return output;
}