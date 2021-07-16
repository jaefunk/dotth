////////////////////////////////////////////////////////////////////////////////
// Filename: light_ps.hlsl
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
Texture2D positionTexture : register(t0);
Texture2D normalTexture : register(t1);
Texture2D diffuseTexture : register(t2);



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
	float2 tex : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 main(PixelInputType input) : SV_TARGET
{
	float4 positions = positionTexture.Sample(SampleTypePoint, input.tex);
	float4 colors = diffuseTexture.Sample(SampleTypePoint, input.tex);
	float4 normals = normalTexture.Sample(SampleTypePoint, input.tex);
	positions = normalize(positions);
	return colors;
	
	//lightPosition = float3(1, 1, 1);

	//int3 sampleIndices = int3(input.position.xy, 0);

	//float3 normal = normalTexture.Load(sampleIndices).xyz;
	//float3 position = positionTexture.Load(sampleIndices).xyz;
	//float3 diffuse = diffuseTexture.Load(sampleIndices).xyz;

	//float3 L = lightPosition - position;
	//float dist = ;

	//if (dist > 2.0f)
	//{
	//	return float4(0.0f, 0.0f, 0.0f, 0.0f);
	//}

	//L /= dist;

	//float att = max(0.0f, 1.0f - (dist / 2.0f));

	//float lightAmount = saturate(dot(normal, L));
	//float3 color = lightAmount * lightColor * att;

	////Specular calc
	//float3 V = cameraPosition - position;
	//float3 H = normalize(L + V);
	//float specular = pow(saturate(dot(normal, H)), 10) * att;

	//float3 finalDiffuse = color * diffuse;
	//float3 finalSpecular = specular * diffuse * att;

	//float4 totalColor = float4(finalDiffuse + finalSpecular, 1.0f);
	//return totalColor;
}