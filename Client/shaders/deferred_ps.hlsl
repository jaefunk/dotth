// External texture-related data
SamplerState Sampler	: register(s0);
Texture2D Texture		: register(t0);

struct VertexOutputType
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMALWS;
	float2 coord		: TEXCOORD;
	float3 worldPos		: POSITIONWS;
	//float3 tangent		: TANGENTWS;
};

struct PixelOutputType
{
	float4 Position				: SV_Target0;
	float4 Diffuse				: SV_Target1;
	float4 Normal				: SV_Target2;
};

PixelOutputType main(VertexOutputType input)
{
	PixelOutputType output;	

	output.Position = float4(input.worldPos, 1.0f);
	output.Diffuse = Texture.Sample(Sampler, input.coord);;
	//output.Normal = float4(input.normal, 1.0f);

	//output.Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
	output.Normal = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return output;
}