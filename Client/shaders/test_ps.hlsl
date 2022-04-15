// External texture-related data
SamplerState Sampler	: register(s0);
Texture2D Texture		: register(t0);

struct VertexOutputType
{
	float4 position		: SV_POSITION;
	float4 color		: COLOR;
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

	output.Position = input.position;
	output.Diffuse = input.color;
	output.Normal = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return output;
}