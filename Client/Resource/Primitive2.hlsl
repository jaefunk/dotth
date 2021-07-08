Texture2D txDiffuse : register(t0);
SamplerState Sampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix wvp;
};

struct VertexInputType
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float2 coord : TEXCOORD0;
    float3 tangent : TANGENT0;
    float3 binormal : BINORMAL0;
    float4 color : COLOR0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL0;
    float2 coord : TEXCOORD0;
};

PixelInputType vs_main(VertexInputType input)
{
    PixelInputType output;
    float4 input_position;
    input_position.xyz = input.position;
    input_position.w = 1.0f;
    output.position = mul(input_position, wvp);

    float4 input_normal;
    input_normal.xyz = input.normal;
    input_normal.w = 1.0f;
    output.normal = mul(input_normal, wvp).xyz;

    output.coord = input.coord;
    return output;
}

float4 ps_main(PixelInputType input) : SV_Target
{
    float4 result = txDiffuse.Sample(Sampler, input.coord);
    return result;
}