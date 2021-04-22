////////////////////////////////////////////////////////////////////////////////
// Filename: color.vs
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////

Texture2D txDiffuse : register( t0 );
SamplerState Sampler : register( s0 );

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};


//////////////
// TYPEDEFS //
//////////////
struct VS_INPUT
{
    float3 pos : POSITION0;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PS_INPUT vs_main(VS_INPUT input)
{
    PS_INPUT result = (PS_INPUT)0;
    
    float4 pos = float4(input.pos, 1.0f);

    result.pos = mul(pos, worldMatrix);

    result.pos = mul(result.pos, viewMatrix);

    result.pos = mul(result.pos, projectionMatrix);

float4 n1 = float4(input.normal, 1.0f);
float4 n2 = mul(n1, worldMatrix);
float3 n3 = float3(n2.x, n2.y, n2.z);

    result.normal = n3;
    
    result.uv = input.uv;
    
    return result;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ps_main(PS_INPUT input) : SV_Target
{
float3 light_color = float3(1.0f, 1.0f, 1.0f);
float3 light_dir = float3(1.0f, -1.0f, -1.0f);
float diff = max(dot(input.normal, light_dir), 0.0f);
float3 diffuse = diff * light_color;
float4 result = txDiffuse.Sample(Sampler, input.uv) * float4(diffuse, 1.0f) ;
    return result;
}