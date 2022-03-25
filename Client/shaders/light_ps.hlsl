////////////////////////////////////////////////////////////////////////////////
// Filename: light_ps.hlsl
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
Texture2D positionTexture : register(t0);
Texture2D diffuseTexture : register(t1);
Texture2D normalTexture : register(t2);



///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleTypePoint : register(s0);


//////////////////////
// CONSTANT BUFFERS //
//////////////////////
cbuffer LightBuffer
{
	float3 lightDirection;
	float padding;
};


//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 coord : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 main(PixelInputType input) : SV_TARGET
{
	float3 position = positionTexture.Sample(SampleTypePoint, input.coord).xyz;
	//return float4(normalize(position), 1.0f);
	float3 color = diffuseTexture.Sample(SampleTypePoint, input.coord).xyz;
	//return float4(color, 1.0f);
	float3 normal = normalTexture.Sample(SampleTypePoint, input.coord).xyz;
	//return float4(normal, 1.0f);

	float3 inverse_light_direction = -1.0f * lightDirection;
	float sat = max(0.3f, dot(normal, normalize(inverse_light_direction)));
	float3 final = color * sat;
	return float4(position, 1.0f);
}