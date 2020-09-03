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
    float3 pos : POSITION;
    //float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    //float3 normal : NORMAL;
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

    //result.normal = float3input.normal;
    
    result.uv = input.uv;
    
    return result;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ps_main(PS_INPUT input) : SV_Target
{
    return txDiffuse.Sample(Sampler, input.uv);
}